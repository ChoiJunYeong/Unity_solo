using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using SimpleJSON;
public class LoadUserInfo : MonoBehaviour {
    public TextAsset jsonData = null;
    public string strJsonData = null;
	// Use this for initialization
	void Start () {
        jsonData = Resources.Load<TextAsset>("user_info");
        strJsonData = jsonData.text;
        var N = JSON.Parse(strJsonData);
        string user_name = N["Name"].ToString();
        int level = N["Status"]["Level"].AsInt;
        Debug.Log(user_name);
        Debug.Log(level.ToString());
        for (int i = 0; i < N["Skill"].Count; i++) {
            Debug.Log(N["Skill"][i].ToString());
        }
	}
}
