using System.Collections;
using System.Collections.Generic;
using Photon.Pun;
using Photon.Realtime;
using UnityEngine;

public class RoomListManagment : MonoBehaviourPunCallbacks
{

    private Dictionary<string, RoomInfo> availableRoomList;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public override void OnRoomListUpdate(List<RoomInfo> roomList)
    {
        base.OnRoomListUpdate(roomList);

        foreach(RoomInfo room in roomList)
        {
            if (availableRoomList.ContainsKey(room.Name))
            {
                availableRoomList[room.Name] = room;
            }
            else
            {
                availableRoomList.Add(room.Name, room);
            }
        }

        foreach(RoomInfo room in availableRoomList.Values)
        {
            Debug.Log("Room Name: " + room.Name + ", Max Players: " + room.MaxPlayers);
        }
    }
}
