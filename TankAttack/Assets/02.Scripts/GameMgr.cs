using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameMgr : MonoBehaviour {


    public Text txtConnect;

    public Text txtLogMsg;
    private PhotonView pv;
	// Use this for initialization
	void Awake () {
        pv = GetComponent<PhotonView>();
        CreateTank();
        PhotonNetwork.isMessageQueueRunning = true;
        GetConnectPlayerCount();
	}
    IEnumerator Start() {
        string msg = "\n<color=#00ff00>[" + PhotonNetwork.player.NickName + "] Connected</color>";
        pv.RPC("LogMsg", PhotonTargets.AllBuffered, msg);
        yield return new WaitForSeconds(1.0f);
        SetConnectPlayerScore();
    }
    void SetConnectPlayerScore() {
        PhotonPlayer[] players = PhotonNetwork.playerList;
        foreach (PhotonPlayer _player in players) {
            Debug.Log("[" + _player.ID + "]" + _player.NickName + " " + _player.GetScore() + " kill");
        }
        GameObject[] tanks = GameObject.FindGameObjectsWithTag("TANK");
        foreach (GameObject tank in tanks) {
            int currrKillCount = tank.GetComponent<PhotonView>().owner.GetScore();
            tank.GetComponent<TankDamage>().txtKillCount.text = currrKillCount.ToString();
        }
    }
    void CreateTank() {
        float pos = Random.Range(-100.0f, 100.0f);
        PhotonNetwork.Instantiate("Tank", new Vector3(pos, 20.0f, pos), Quaternion.identity, 0);
    }
	// Update is called once per frame
	void GetConnectPlayerCount() {
        Room currRoom = PhotonNetwork.room;
        txtConnect.text = currRoom.PlayerCount.ToString() + "/" + currRoom.MaxPlayers.ToString();
    }
    void OnPhotonPlayerConnected(PhotonPlayer newPlayer) {
        GetConnectPlayerCount();
    }
    void OnPhotonPlayerDisconnected(PhotonPlayer outPlayer) {
        GetConnectPlayerCount();
    }

    [PunRPC]
    void LogMsg(string msg) {
        txtLogMsg.text = txtLogMsg.text + msg;
    }

    public void OnClickExitRoom() {
        PhotonNetwork.LeaveRoom();
        string msg = "\n<color = #ff0000[" + PhotonNetwork.player.NickName + "] Disconnected</color>";
        pv.RPC("LogMsg", PhotonTargets.AllBuffered, msg);
    }
    void OnLeftRoom() {
        SceneManager.LoadScene("scLobby");
    }
}
