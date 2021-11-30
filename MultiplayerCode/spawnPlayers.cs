using Photon.Pun;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnPlayers : MonoBehaviour
{
    public GameObject player;
    public float minX, minZ, maxX, maxZ;
    // Start is called before the first frame update
    void Start()
    {
        Vector3 randomSpawnPos = new Vector3(Random.Range(minX, maxX), 1.0f, Random.Range(minZ, maxZ));
        PhotonNetwork.Instantiate(player.name, randomSpawnPos, Quaternion.identity);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
