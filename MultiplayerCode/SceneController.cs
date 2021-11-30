using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using Photon.Realtime;
using UnityEngine.SceneManagement;


public class SceneController : MonoBehaviourPunCallbacks
{
   
    private bool cursorToggle;

    // Start is called before the first frame update
    void Start()
    {
        cursorToggle = false;
        Cursor.lockState = CursorLockMode.Confined;
        Cursor.visible = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey("c"))
        {
            if (cursorToggle)
            {
                Cursor.lockState = CursorLockMode.None;
                Cursor.visible = true;
                cursorToggle = !cursorToggle;
            }
            else
            {
                Cursor.lockState = CursorLockMode.Confined;
                Cursor.visible = false;
                cursorToggle = !cursorToggle;
            }
        }
    }

    public override void OnLeftRoom()
    {
        base.OnLeftRoom();
        SceneManager.LoadScene("LobbyScene");
    }

    public override void OnPlayerLeftRoom(Player otherPlayer)
    {
        base.OnPlayerLeftRoom(otherPlayer);
        if(PhotonNetwork.CurrentRoom.PlayerCount <= 1)
        {
            PhotonNetwork.LeaveRoom();
        }
    }
}
