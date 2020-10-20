using System.Collections;
using UnityEngine;

public class EvasiveManeuver : MonoBehaviour
{
    public float xMin;
    public float xMax;
    public float zMin;
    public float zMax;
    public float dodge;
    public float smoothing;
    public float tilt;
    public Vector2 startWait;
    public Vector2 maneuverTime;
    public Vector2 maneuverWait;
    

    private float currentSpeed;
    private float targetManeuver;
    private Rigidbody rb;
    
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        currentSpeed = rb.velocity.z;
        StartCoroutine(Evade());
    }

    IEnumerator Evade()
    {
        yield return new WaitForSeconds(Random.Range(startWait.x, startWait.y));

        while (true)
        {   //adds the function for the enemy to dodge.
            targetManeuver = Random.Range(1, dodge) * -Mathf.Sign(transform.position.x);
            yield return new WaitForSeconds(Random.Range(maneuverTime.x, maneuverTime.y));
            targetManeuver = 0;
            yield return new WaitForSeconds(Random.Range(maneuverWait.x, maneuverWait.y));
        }
    }

    
    void FixedUpdate()
    {
        //sets the boundary and how it'll move in sertain ways.
        float newManeuver = Mathf.MoveTowards(rb.velocity.x, targetManeuver, Time.deltaTime * smoothing);
        rb.velocity = new Vector3(newManeuver, 0.0f, currentSpeed);
        rb.position = new Vector3
            (
            Mathf.Clamp(rb.position.x, xMin, xMax), 
            0.0f,
            Mathf.Clamp(rb.position.z, zMin, zMax)
            );
        //adds the enemy tilt function.
        rb.rotation = Quaternion.Euler(0.0f, 0.0f, rb.velocity.x * -tilt);
    }
}
