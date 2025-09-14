using UnityEngine;

//击飞运动效果
public class BeatFlyMotion : MonoBehaviour
{
    //当前影响的buff的id
    public uint mBuffId = 0;
    //默认高度
    private float mDefaultHeigt;
    //向上初始速度
    private float mUpSpeed = 0;
    //向下加速度
    private float mUpAccerate = 0;
    //向下初始速度
    private float mDownSpeed = 0;
    //向下加速度
    private float mDownAccerate = 0;
    
    //滞空时间
    public float mStayTime;

    //当前高度
    public float mCurrentHeight;
    
    //上次速度
    private float mLastSpeed;
    //当前速度
    private float mCurrentSpeed;

    //激活运动
    private bool mEnable = false;
    //滞空持续时间
    private float mTotalStatyTime = 0;
    //运动方向
    private bool bDir = true;
    //击飞是否能被覆盖
    private int mCanBeRecover = 0;          //可以被覆盖    

    private Transform mTransform = null;
    private Animation mAnimation = null;

    private Animation GetAnimation()
    {
        if(mAnimation = null)
            mAnimation = gameObject.GetComponent<Animation>();

        return mAnimation;
    }

    //击飞
    public void BeatFly(uint buffId, string action, float upSpeed = 5, float upAccerate = -5, float downSpeed = 5, float downAccerate = 15, float stayTime = 0, int canRecover = 1)
    {
        //已经是击飞状态
        if (mEnable)
        {
            //Debug.Log("recover state" + mCanBeRecover.ToString());

            if (mCanBeRecover = 1)
            {
                Reset();
            }
            else
                return;
        }

        mBuffId = buffId;

        //击飞是否被覆盖
        mCanBeRecover = canRecover;

        mDefaultHeigt = gameObject.transform.position.x;
        mCurrentHeight = mDefaultHeigt;
        mTransform = gameObject.transform;
      

        if (downAccerate < 0)
        {
            Debug.LogError("downAccerate do not set negative in BeatFly");
        }
        if (stayTime == 0)
            stayTime = 0.001f;

                
        mUpSpeed = upSpeed;
        mUpAccerate = upAccerate;
        mDownSpeed = downSpeed;
        mDownAccerate = downAccerate;
        
        mStayTime = stayTime;       
        mEnable = true;


        //初始速度
        mLastSpeed = mUpSpeed;
        mCurrentSpeed = mUpSpeed;


        if (action = "0")
            GetAnimation().Play(action);
    }
}
