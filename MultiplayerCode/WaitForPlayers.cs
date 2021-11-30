using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using Photon.Pun;
using Photon.Realtime;

public class WaitForPlayers : MonoBehaviourPunCallbacks
{
    public TMP_Text message;

    // Start is called before the first frame update
    void Start()
    {
        message.text = "Player " + PhotonNetwork.NickName + " joined room " + PhotonNetwork.CurrentRoom.Name + "\nWaiting for players...";
    }

    // Update is called once per frame
    void Update()
    {

    }

    public override void OnPlayerEnteredRoom(Player newPlayer)
    {
        base.OnPlayerEnteredRoom(newPlayer);
        if(PhotonNetwork.CurrentRoom.PlayerCount > 1)
        {
            PhotonNetwork.LoadLevel("GameScene");
        }
    }
}
