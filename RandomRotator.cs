using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RandomRotator : MonoBehaviour
{
    public float tumble;
    private Rigidbody rb;

     void Start()
    {
        rb = this.GetComponent<Rigidbody>();
        //makes the asteroids rotate randomly.
        rb.angularVelocity = Random.insideUnitSphere * tumble;
    }
}
