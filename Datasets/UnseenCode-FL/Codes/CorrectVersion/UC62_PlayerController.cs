using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    Rigidbody2D rb;
    Animator anim;

    public float speed;
    float xVelocity;

    public float checkRadius;
    public LayerMask platform;
    public GameObject groundCheck;
    public bool isOnGround;

    bool playerDead;

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
    }

    void Update()
    {
        isOnGround = Physics2D.OverlapCircle(groundCheck.transform.position, checkRadius, platform);

        anim.SetBool("isOnGround", isOnGround);

        Movement();
    }

    void Movement()
    {
        xVelocity = Input.GetAxisRaw("Horizontal");

        rb.velocity = new Vector2(xVelocity * speed, rb.velocity.y);

        anim.SetFloat("speed", Mathf.Abs(rb.velocity.x));//跑动的动画

        if (xVelocity != 0)//翻转方向
        {
            transform.localScale = new Vector3(xVelocity, 1, 1);
        }
    }

    void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject.CompareTag("Fan"))
        {
            rb.velocity = new Vector2(rb.velocity.x, 10f);
        }
    }
    private void OnTriggerEnter2D(Collider2D other)
    {
        if (other.CompareTag("Spike"))
        {
            anim.SetTrigger("dead");
        }
    }

    public void PlayerDead()
    {
        playerDead = true;
        GameManager.GameOver(playerDead);
    }

    private void OnDrawGizmosSelected()
    {
        Gizmos.color = Color.blue;

        Gizmos.DrawWireSphere(groundCheck.transform.position, checkRadius);
    }

}
