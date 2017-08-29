using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PhotonInit : MonoBehaviour {
    public string version = "v1.0";
    public InputField userId;
    public InputField roomName;

    public GameObject scrollContents;
    public GameObject roomItem;
    // Use this for initialization
    private void Awake() {
        if(!PhotonNetwork.connected)
            PhotonNetwork.ConnectUsingSettings(version);
        userId.text = GetUserId();
        roomName.text = "ROOM_" + Random.Range(0, 999).ToString("000");
    }
    private void OnGUI() {
        GUILayout.Label(PhotonNetwork.connectionStateDetailed.ToString());
    }

    void OnJoinedLobby() {
        Debug.Log("Entered Lobby !");
        userId.text = GetUserId();
    }
    string GetUserId() {
        string userId = PlayerPrefs.GetString("USER_ID");
        if (string.IsNullOrEmpty(userId)) {
            userId = "USER_" + Random.Range(0, 999).ToString("000");
        }
        return userId;
    }
    void OnPhotonRandomJoinFailed() {
        Debug.Log("No rooms!");
        PhotonNetwork.CreateRoom("MyRoom");
    }
    void OnJoinedRoom() {
        Debug.Log("Enter Room");
        StartCoroutine(this.LoadBattleField());
    }
    IEnumerator LoadBattleField() {
        PhotonNetwork.isMessageQueueRunning = false;
        AsyncOperation ao = SceneManager.LoadSceneAsync("scBattleField");
        yield return ao;
    }

    // Update is called once per frame
    public void OnClickJoinRandomRoom() {
        PhotonNetwork.player.NickName = userId.text;
        PlayerPrefs.SetString("USER_ID", userId.text);
        PhotonNetwork.JoinRandomRoom();
    }
    public void OnClickCreateRoom() {
        string _roomName = roomName.text;
        if (string.IsNullOrEmpty(roomName.text)) {
            _roomName = "ROOM_" + Random.Range(0, 999).ToString("000");
        }
        PhotonNetwork.player.NickName = userId.text;
        PlayerPrefs.SetString("USER_ID", userId.text);
        RoomOptions roomOptions = new RoomOptions();
        roomOptions.IsOpen = true;
        roomOptions.IsVisible = true;
        roomOptions.MaxPlayers = 20;
        PhotonNetwork.CreateRoom(_roomName, roomOptions, TypedLobby.Default);
    }
    void OnPhotonCreateRoomFailed(object[] codeAndMsg) {
        Debug.Log("Create Room Failed = " + codeAndMsg[1]);
    }
    void OnReceivedRoomListUpdate() {
        foreach (GameObject obj in GameObject.FindGameObjectsWithTag("ROOM_ITEM")) {
            Destroy(obj);
        }
        int rowCount = 0;
        scrollContents.GetComponent<RectTransform>().sizeDelta = Vector2.zero;
        foreach (RoomInfo _room in PhotonNetwork.GetRoomList()) {
            Debug.Log(_room.Name);
            GameObject room = (GameObject)Instantiate(roomItem);
            room.transform.SetParent(scrollContents.transform, false);
            RoomData roomData = room.GetComponent<RoomData>();
            roomData.roomName = _room.Name;
            roomData.connectPlayer = _room.PlayerCount;
            roomData.maxPlayers = _room.MaxPlayers;
            roomData.DispRoomData();
            roomData.GetComponent<UnityEngine.UI.Button>().onClick.AddListener(delegate { OnClickRoomItem(roomData.roomName); });
            scrollContents.GetComponent<GridLayoutGroup>().constraintCount = ++rowCount;
            scrollContents.GetComponent<RectTransform>().sizeDelta += new Vector2(0, 20);
        }
    }
    void OnClickRoomItem(string roomName) {
        PhotonNetwork.player.NickName = userId.text;
        PlayerPrefs.SetString("USER_ID", userId.text);
        PhotonNetwork.JoinRoom(roomName);
    }
}
