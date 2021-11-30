#version 330 core

out vec4 fragColor;

//material using mapps
struct Material
{
    float ambient;
    float shininess;
};

//Material properties from model loading
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

//Input from vertex shader
in vec2 TexCoord;
in vec3 fragCoord;
in vec3 Normal;

//material uniforms
uniform Material objectMat;

//light uniforms
uniform vec3 lightColor;
uniform vec3 lightPosition;

//viewing uniform
uniform vec3 viewPosition;

uniform bool useBlinnPhong;

void main()
{
    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    //ambient component 
    ambient = objectMat.ambient * texture(texture_diffuse1, TexCoord).rgb * lightColor;

    //diffuse component with maps
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - fragCoord);

    //using maps:
    diffuse =  texture(texture_diffuse1, TexCoord).rgb * max(dot(norm, lightDir), 0.0) * lightColor;
   
    //specular component
    vec3 viewDir = normalize(viewPosition - fragCoord);

    float dotProduct = 0.0;

    if(useBlinnPhong)
    {
        vec3 halfway = normalize(lightDir + viewDir);
        dotProduct = dot(norm, halfway);
    }
    else
    {
        vec3 reflDir = reflect(-lightDir, norm);
        dotProduct = max(dot(viewDir, reflDir), 0.0);
    }

    //using maps:
    specular =  texture(texture_specular1, TexCoord).rgb * pow(dotProduct, objectMat.shininess) * lightColor;
  
    vec3 illumination = ambient + diffuse + specular + (objectMat.ambient * texture(texture_specular1, TexCoord).rgb);

    fragColor = vec4 (illumination, 1.0);
}
