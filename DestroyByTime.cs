using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyByTime : MonoBehaviour
{
    public float lifetime;
     void Start()
    {
        //destroys game objects at a sertain point of time.
        Destroy(gameObject, lifetime);
    }
}
