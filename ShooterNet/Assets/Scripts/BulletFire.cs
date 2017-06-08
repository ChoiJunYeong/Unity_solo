using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletFire : MonoBehaviour {
    public float lifeTime = 5.0f;
	// Use this for initialization
	void Start () {
        GetComponent<Rigidbody>().velocity = transform.forward * 10.0f;
        Destroy(gameObject, lifeTime);
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
