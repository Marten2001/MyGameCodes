using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;

public class ShootingController : MonoBehaviour
{
    public Camera FPSCamera;

    public float timeBetweenShots;

    private PhotonView view;
    private float timeFromLastShot;
    // Start is called before the first frame update
    void Start()
    {
        view = GetComponent<PhotonView>();
        timeFromLastShot = timeBetweenShots;
    }

    // Update is called once per frame
    void Update()
    {
        if(timeFromLastShot < timeBetweenShots)
        {
            timeFromLastShot += Time.deltaTime;
        }

        if (view.IsMine)
        {
            if (Input.GetButton("Fire1"))
            {
                if (timeFromLastShot >= timeBetweenShots)
                {
                    RaycastHit hit;
                    Ray ray = FPSCamera.ViewportPointToRay(new Vector3(0.5f, 0.5f));
                    if (Physics.Raycast(ray, out hit, 100))
                    {
                        if (hit.collider.gameObject.CompareTag("Player"))
                        {
                            hit.collider.gameObject.GetComponent<PhotonView>().RPC("TakeDamage", RpcTarget.AllBuffered, 10.0f);
                        }
                        if (hit.collider.gameObject.CompareTag("Enemy"))
                        {
                            hit.collider.gameObject.GetComponent<PhotonView>().RPC("Die", RpcTarget.AllBuffered);
                        }
                    }
                }
                timeFromLastShot = 0.0f;
            }
        }
    }
}
