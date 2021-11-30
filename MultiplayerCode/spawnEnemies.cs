using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;

public class SpawnEnemies : MonoBehaviour
{
    public GameObject enemy;
    float timeBetweenSpawns;
    public Transform[] spawningPoints;
    public int maxEnemies;

    public float maxSpawnInterval;
    public static int numOfEnemies;
    // Start is called before the first frame update
    void Start()
    {
        numOfEnemies = 0;
        timeBetweenSpawns = maxSpawnInterval;
    }

    // Update is called once per frame
    void Update()
    {
        if ((PhotonNetwork.IsMasterClient) && (PhotonNetwork.CurrentRoom.PlayerCount > 1))
        {
            if (timeBetweenSpawns <= 0.0f)
            {
                if (numOfEnemies < maxEnemies)
                {
                    int randIndx = Random.Range(0, spawningPoints.Length);
                    Vector3 randomSpawnPos = spawningPoints[randIndx].position;
                    PhotonNetwork.Instantiate(enemy.name, randomSpawnPos, Quaternion.identity);
                    numOfEnemies++;
                    timeBetweenSpawns = maxSpawnInterval;
                }
            }
            else
            {
                timeBetweenSpawns -= Time.deltaTime;
            }
        }
    }
}
