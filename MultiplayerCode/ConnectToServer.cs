using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using UnityEngine.SceneManagement;

public class ConnectToServer : MonoBehaviourPunCallbacks
{
    // Start is called before the first frame update
    void Start()
    {
        PhotonNetwork.ConnectUsingSettings();
    }

    //Callback to handle the event of connecting to the photon server
    public override void OnConnectedToMaster()
    {

        SceneManager.LoadScene("LobbyScene");
    }
}
