using Photon.Pun;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class PlayerController : MonoBehaviour
{
    public TMP_Text name;
    public float speed;
    public float rotationSpeed;
    public GameObject FPSCamera;
    public GameObject UpperBody;

    private PhotonView view;
    private float CurrentCameraRotation;

    // Start is called before the first frame update
    void Start()
    {
        CurrentCameraRotation = 0.0f;
        view = GetComponent<PhotonView>();
        name.text = view.Owner.NickName;
        if (!view.IsMine)
        {
            FPSCamera.GetComponent<Camera>().enabled = false;
            FPSCamera.GetComponent<AudioListener>().enabled = false;
        }
        else
        {
            //rotate your character's name
            name.rectTransform.Rotate(Vector3.up, 180.0f);
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (view.IsMine)
        {
            if (Input.GetKey("w"))
            {
                //Vector3 movement = new Vector3(0.0f, 0.0f, speed * Time.deltaTime);
                transform.position += transform.forward * speed * Time.deltaTime;
            }
            if (Input.GetKey("s"))
            {
                //Vector3 movement = new Vector3(0.0f, 0.0f, -speed * Time.deltaTime);
                transform.position -= transform.forward * speed * Time.deltaTime;
            }
            if (Input.GetKey("a"))
            {
                //Vector3 movement = new Vector3(-speed * Time.deltaTime, 0.0f, 0.0f);
                transform.position -= transform.right * speed * Time.deltaTime;
            }
            if (Input.GetKey("d"))
            {
                // Vector3 movement = new Vector3(speed * Time.deltaTime, 0.0f, 0.0f);
                transform.position += transform.right * speed * Time.deltaTime;
            }
            
            //Horizontal rotation of character
            float rotation_Y = Input.GetAxis("Mouse X");
            Vector3 rotationVectorY = new Vector3(0.0f, rotation_Y, 0.0f) * rotationSpeed;

            Vector3 currRotation = transform.rotation.eulerAngles;
            Vector3 finalRotation = currRotation + rotationVectorY;
            transform.rotation = Quaternion.Euler(finalRotation);

            ////vertical rotation of camera and body parts
            float verticalRotation = Input.GetAxis("Mouse Y") * rotationSpeed;

            CurrentCameraRotation -= verticalRotation;
            CurrentCameraRotation = Mathf.Clamp(CurrentCameraRotation, -85, 85);
            UpperBody.transform.localEulerAngles = new Vector3(CurrentCameraRotation, 0.0f, 0.0f);
        }
    }
}

