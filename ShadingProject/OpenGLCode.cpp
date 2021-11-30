#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
bool toggleBool(bool toggle);
int toggleInt(int toggle, int low, int high);
unsigned int loadTexture(const char* path, bool flipVertically);
unsigned int loadCubeMap(std::vector<std::string> facePaths);

// settings
 unsigned int SCR_WIDTH = 1280;
 unsigned int SCR_HEIGHT = 1024;

//mouse globals
float lastPosX = 0.0f;
float lastPosY = 0.0f;
bool firstFrame = true;

//time globals
float deltaTime = 0.0f;
float lastFrameTime = 0.0f;
int frameCounter = 0;
float startTime = 0.0;
float endTime = 0.0;

//Camera
Camera myCamera1(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
Camera myCamera2(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
bool useCamera1 = true;

//Toogle grab cursor
bool grabCursor = true;
//Toggle blinn-phong
bool useBlinnPhong = false;
//Toggle model
int modelIndex = 0;

//Model rotation angle
float rotAngle = 0.0f;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GPR5300 2021 Lab 1", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window, scroll_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader simpleShader("simpleShader.vs", "simpleShader.fs");
	Shader reflectiveShader("reflectiveShader.vs", "reflectiveShader.fs");
	Shader refractiveShader("refractiveShader.vs", "refractiveShader.fs");
	Shader lightShader("lightShader.vs", "lightShader.fs");
	Shader skyboxShader("skyboxShader.vs", "skyboxShader.fs");
	//Shader reflectShader("simpleShader.vs", "environmentMapping.fs");


	std::string modelPaths[] = {
		"models/Bitcoin/Bitcoin_metal_coin.obj",
		"models/Mandalorian/Mandalorian.obj",
		"models/aircraft/E 45 Aircraft_obj.obj"
	};

	std::vector<Model>loadedModels;

	for (int i = 0; i < 3; i++)
	{
		Model model(modelPaths[i]);
		loadedModels.push_back(model);
	}

	float vertices[] = {
		// positions         // normals           // texture
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};




	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};



	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO); // Bind with the vao you want to manipulate. Everything that happens under this command will change this VAO.


	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); //vertex coordinates

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1); //normal coordinates

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2); //texture coordinates

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Skybox VAO and VBO
	unsigned int skyVAO, skyVBO;
	glGenVertexArrays(1, &skyVAO);
	glGenBuffers(1, &skyVBO);

	glBindVertexArray(skyVAO); //No need to unbind from previous VAO, if we bind a new one.
	glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); //vertex coordinates



	std::vector<std::string> cubeMapFaces
	{
		"skybox/right.jpg",
		"skybox/left.jpg",
		"skybox/top.jpg",
		"skybox/bottom.jpg",
		"skybox/front.jpg",
		"skybox/back.jpg"
	};

	unsigned int cubeMap = loadCubeMap(cubeMapFaces);

	simpleShader.use();
	simpleShader.setFloat("objectMat.ambient", 0.2);
	simpleShader.setFloat("objectMat.shininess", 0.6 * 128.0f);

	glm::vec3 lightPosition = glm::vec3(-12.0f, 10.0f, -50.0f);
	glm::vec3 lightColor = glm::vec3(1.0f);
	glm::vec3 tint = glm::vec3(0.0, 0.0, 1.0);

	simpleShader.setVec3("lightColor", lightColor);
	simpleShader.setVec3("lightPosition", lightPosition);
	//simpleShader.setVec3("tint", tint);
	simpleShader.setInt("skybox", 0);
	simpleShader.setFloat("refrIndexA", 1.000293);
	//Uniform for the skybox shader
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);
	reflectiveShader.use();
	reflectiveShader.setInt("skybox", 0);
	refractiveShader.use();
	refractiveShader.setInt("skybox", 0);


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{

		if (frameCounter < INT_MAX)
		{
			frameCounter++;
			endTime = glfwGetTime();
		}
		//std::cout << "FPS: " << frameCounter / (endTime - startTime) << std::endl;

		if (grabCursor)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		//calculate deltaTime and frameCounter
		float currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;

		

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// "camera matrix"
		glm::mat4 view = glm::mat4(1.0f);
		if (useCamera1)
			view = myCamera1.GetViewMatrix();
		else
			view = myCamera2.GetViewMatrix();


		// "Projection matrix"
		glm::mat4 projection = glm::mat4(1.0f);
		if (useCamera1)
			projection = glm::perspective(glm::radians(myCamera1.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		else
			projection = glm::perspective(glm::radians(myCamera2.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	
		simpleShader.use();
		simpleShader.setMat4("view", view);
		simpleShader.setMat4("projection", projection);
		simpleShader.setFloat("refrIndexB", 1.575);

	
		//Send camera position to shader
		if (useCamera1)
			simpleShader.setVec3("viewPosition", myCamera1.Position);
		else
			simpleShader.setVec3("viewPosition", myCamera2.Position);
	

		simpleShader.setBool("useBlinnPhong", useBlinnPhong);
		simpleShader.setFloat("time", glfwGetTime()/2.0f);
		
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

		// Spaceship with phong illumination shader
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		simpleShader.setMat4("model", model);

		loadedModels[2].Draw(simpleShader);

		//Mandalorian helmet with reflective shaders
		reflectiveShader.use();
		reflectiveShader.setMat4("view", view);
		reflectiveShader.setMat4("projection", projection);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		reflectiveShader.setMat4("model", model);

		if (useCamera1)
			reflectiveShader.setVec3("viewPosition", myCamera1.Position);
		else
			reflectiveShader.setVec3("viewPosition", myCamera2.Position);

		loadedModels[1].Draw(reflectiveShader); 

		//Bitcoin model with refractive shaders for transparency
		refractiveShader.use();
		refractiveShader.setMat4("view", view);
		refractiveShader.setMat4("projection", projection);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		refractiveShader.setMat4("model", model);
		refractiveShader.setFloat("refrIndexB", 1.575);
		refractiveShader.setFloat("refrIndexA", 1.0);
		if (useCamera1)
			refractiveShader.setVec3("viewPosition", myCamera1.Position);
		else
			refractiveShader.setVec3("viewPosition", myCamera2.Position);

		loadedModels[0].Draw(refractiveShader);
		
		//WE NEED TO CALL A DIFFERENT SHADER

		lightShader.use();
		glBindVertexArray(VAO);
		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPosition);
		model = glm::scale(model, glm::vec3(0.2));
		lightShader.setMat4("model", model);
		lightShader.setVec3("lightColor", lightColor);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		// CRAZY SKYBOX STUFF - OPTIMAL METHOD
		glDepthFunc(GL_LEQUAL);


		skyboxShader.use();
		skyboxShader.setMat4("projection", projection);
		skyboxShader.setMat4("view", glm::mat4(glm::mat3(view)));
		glBindVertexArray(skyVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDepthFunc(GL_LESS);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

bool toggleBool(bool toggle)
{
	if (frameCounter > 1 / deltaTime)
	{
		frameCounter = 0;
		startTime = glfwGetTime();
		return !toggle;
	}
	else
		return toggle;
}

int toggleInt(int toggle, int low, int high)
{
	if (frameCounter > 1 / deltaTime)
	{
		frameCounter = 0;
		startTime = glfwGetTime();
		toggle++;
		if (toggle == high)
			toggle = low;
		
	}

	return toggle;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		if (useCamera1)
			myCamera1.ProcessKeyboard(LEFT, deltaTime); // Move to the left
		else
			myCamera2.ProcessKeyboard(LEFT, deltaTime); // Move to the left

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		if (useCamera1)
			myCamera1.ProcessKeyboard(RIGHT, deltaTime); // Move to the right
		else
			myCamera2.ProcessKeyboard(RIGHT, deltaTime); // Move to the right

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		if (useCamera1)
			myCamera1.ProcessKeyboard(FORWARD, deltaTime); // Move forward
		else
			myCamera2.ProcessKeyboard(FORWARD, deltaTime); // Move forward

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		if (useCamera1)
			myCamera1.ProcessKeyboard(BACKWARD, deltaTime); //Move backwards
		else
			myCamera2.ProcessKeyboard(BACKWARD, deltaTime); //Move backwards


	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		useCamera1 = toggleBool(useCamera1);
	}

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	{
		grabCursor = toggleBool(grabCursor);
	}

	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		useBlinnPhong = toggleBool(useBlinnPhong);
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) 
	{
		modelIndex = toggleInt(modelIndex, 0, 3);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		rotAngle -= 5.0 * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		rotAngle += 5.0 * deltaTime;
	}
}

//SCROLLING CALLBACK FUNCTION
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if(useCamera1)
		myCamera1.ProcessMouseScroll(yoffset);
	else
		myCamera2.ProcessMouseScroll(yoffset);

}

//MOUSE CALLBACK FUNCTION
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstFrame)
	{
		lastPosX = xpos;
		lastPosY = ypos;
		firstFrame = false;
	}
	float x_offset = xpos - lastPosX;
	float y_offset = ypos - lastPosY;

	lastPosX = xpos;
	lastPosY = ypos;

	if(useCamera1)
		myCamera1.ProcessMouseMovement(x_offset, y_offset, deltaTime);
	else
		myCamera2.ProcessMouseMovement(x_offset, y_offset, deltaTime);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);

	//Update screen width and height in order to update the aspect ration in the projection matrix
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

unsigned int loadTexture(const char* path, bool flipVertically)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, numOfChannels;

	stbi_set_flip_vertically_on_load(flipVertically);

	unsigned char* data = stbi_load(path, &width, &height, &numOfChannels, 0);
	if (data)
	{
		GLenum format;
		if (numOfChannels == 1)
			format = GL_RED;
		else if (numOfChannels == 3)
			format = GL_RGB;
		else if (numOfChannels == 4)
			format = GL_RGBA;
		else
		{
			std::cout << "TEXTURE ERROR! Invalid number of channels at path " << path << std::endl;
			stbi_image_free(data);
			return textureID;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	}
	else
	{
		std::cout << "TEXTURE ERROR! Failed to load texture at path " << path << std::endl;
	}

	stbi_image_free(data);

	return textureID;
}

unsigned int loadCubeMap(std::vector<std::string> facePaths)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, numOfChannels;
	for (unsigned int i = 0; i < facePaths.size(); i++) 
	{
		unsigned char* data = stbi_load(facePaths[i].c_str(), &width, &height, &numOfChannels, 0);
		if (data)
		{
			GLenum format;
			if (numOfChannels == 1)
				format = GL_RED;
			else if (numOfChannels == 3)
				format = GL_RGB;
			else if (numOfChannels == 4)
				format = GL_RGBA;
			else
			{
				std::cout << "CUBEMAP ERROR! Invalid number of channels at path " << facePaths[i] << std::endl;
				stbi_image_free(data);
				return textureID;
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "CUBEMAP ERROR! Failed to load texture at path " << facePaths[i] << std::endl;
			
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return textureID;
}
