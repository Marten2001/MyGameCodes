using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyByContact : MonoBehaviour
{
    public GameObject explosion;
    public GameObject playerExplosion;
    public int scoreValue;
    private GameController gameController;

    void Start()
    {
        GameObject gameControllerObject = GameObject.FindWithTag("GameController");
        if (gameControllerObject != null)
        {
            gameController = gameControllerObject.GetComponent<GameController>();
        }
        if (gameController == null)
        {
            Debug.Log("Cannot find 'GameController' script");
        }
    }
    void OnTriggerEnter(Collider other)
    {
        //adds enemy destruction.
        if (other.CompareTag ("Boundary") || other.CompareTag ("Enemy"))
        {
            return;
        }

        if (explosion != null)
        {
            Instantiate(explosion, transform.position, transform.rotation);
        }
        //if the player gets hit, then this destroys the player component.
        if (other.tag == "Player")
        {
            Instantiate(playerExplosion, other.transform.position, other.transform.rotation);
            gameController.GameOver();    
        }
        //adds the value of score.
        gameController.AddScore(scoreValue);
        Destroy(other.gameObject);
        Destroy(gameObject);
    }
}
