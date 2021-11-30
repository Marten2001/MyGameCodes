using Photon.Pun;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour
{
    PlayerController[] players;
    PlayerController nearestPlayer;

    public float speed;


    // Start is called before the first frame update
    void Start()
    {
        players = FindObjectsOfType<PlayerController>();
    }

    // Update is called once per frame
    void Update()
    {
        float minDistance = float.MaxValue;
        foreach(PlayerController player in players)
        {
            float distance = Vector3.Distance(transform.position, player.transform.position);
            if(distance < minDistance)
            {
                minDistance = distance;
                nearestPlayer = player;
            }
        }

        if(nearestPlayer != null)
        {
            transform.position = Vector3.MoveTowards(transform.position, nearestPlayer.transform.position, speed * Time.deltaTime);
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.CompareTag("Player"))
        {
            collision.gameObject.GetComponent<PhotonView>().RPC("TakeDamage", RpcTarget.AllBuffered, 5.0f);
        }
    }

    [PunRPC]
    public void Die()
    {
        if (PhotonNetwork.IsMasterClient)
        {
            SpawnEnemies.numOfEnemies--;
            PhotonNetwork.Destroy(this.gameObject);
        }
    }
}
