using System.Collections;
using System.Collections.Generic;
using UnityEngine;
[RequireComponent(typeof(AudioSource))]
public class FireCtrl : MonoBehaviour {
    public GameObject bullet;
    public Transform firePos;
    public AudioClip fireSfx;
    public AudioSource source = null;
    public MeshRenderer muzzleFlash;
    // Update is called once per frame
    void Start()
    {
        source = GetComponent<AudioSource>();
        muzzleFlash.enabled = false;
    }
    void Update () {
        Debug.DrawRay(firePos.position, firePos.forward * 10.0f, Color.green);
        if (Input.GetMouseButtonDown(0)) {
            //Fire();
            RaycastHit hit;
            if (Physics.Raycast(firePos.position, firePos.forward, out hit, 10.0f)) {
                if (hit.collider.tag == "MONSTER") {
                    object[] _params = new object[2];
                    _params[0] = hit.point;
                    _params[1] = 20;
                    hit.collider.gameObject.SendMessage("OnDamage", _params, SendMessageOptions.DontRequireReceiver);
                }
                if (hit.collider.tag == "BARREL") {
                    object[] _params = new object[2];
                    _params[0] = firePos.position;
                    _params[1] = hit.point;
                    hit.collider.gameObject.SendMessage("OnDamage", _params, SendMessageOptions.DontRequireReceiver);
                }
            }
        }
	}
    void Fire()
    {
        CreatBullet();
        GameMgr.instance.PlaySfx(firePos.position, fireSfx);
        StartCoroutine(this.ShowMuzzleFlash());
    }
    void CreatBullet() {
        Instantiate(bullet, firePos.position, firePos.rotation);
    }
    IEnumerator ShowMuzzleFlash() {
        float scale = Random.Range(0.5f, 1.0f);
        muzzleFlash.transform.localScale = Vector3.one * scale;
        Quaternion rot = Quaternion.Euler(0, 0, Random.Range(0, 360));
        muzzleFlash.transform.localRotation = rot;
        muzzleFlash.enabled = true;
        yield return new WaitForSeconds(Random.Range(0.05f, 0.1f));
        muzzleFlash.enabled = false;
    }
}
