using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using UnityEngine.UI;

public class DamageController : MonoBehaviour
{
    public float startingHealth;
    public Image healthBar;

    private float health;
    private PhotonView view;

    // Start is called before the first frame update
    void Start()
    {
        health = startingHealth;
        healthBar.fillAmount = health / startingHealth;
        view = GetComponent<PhotonView>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    [PunRPC]
    public void TakeDamage(float damage)
    {
        health -= damage;
        healthBar.fillAmount = health / startingHealth;
        Debug.Log("DAMAGE TAKEN! HEALTH: " + health);
        if(health <= 0.0f)
        {
            Debug.Log("WASTED");
            Die();
        }
    }

    public void Die()
    {
        if (view.IsMine)
        {
            PhotonNetwork.LeaveRoom();
        }
    }
}
