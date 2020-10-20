using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyByBoundary : MonoBehaviour
{
    void OnTriggerExit(Collider other)
    {
        //this destroys enemies and asteroids, when out of bounds.
        Destroy(other.gameObject);
    }
}
