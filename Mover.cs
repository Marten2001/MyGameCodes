using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Mover : MonoBehaviour
{
    private Rigidbody rb;
    public float speed;
     void Start()
    {
        rb = this.GetComponent<Rigidbody>();
        //adds speed for the laser bolt.
        rb.velocity = transform.forward * speed;
    }
}
