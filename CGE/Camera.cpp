#include "Camera.h"
#include "Tools.h"

using namespace std;

namespace CGE
{
    Camera::Camera() : mDistance(0.0f), mRotation(0.0f), mAngle(0.0f),
        mFollow(NULL), mShakeCurrentPosition(0.0f), mShakeCurrentDegrees(0.0f)
    {
    }

    Camera::~Camera()
    {
    }

    void Camera::update()
    {
        mAngleMatrix.loadIdentity();
        if (mDistance > 0.0f) mAngleMatrix.translate(0.0f, 0.0f, -mDistance);
        mAngleMatrix.rotateX(mAngle);
        mAngleMatrix.rotateZ(mRotation);

        mTranslateMatrix.loadIdentity();

        calculateShakePosition();

        if (mFollow)
        {
            mTranslateMatrix.translate(-mFollow[0] + mShakeCurrentPosition, -mFollow[1],
                -mFollow[2]);
        }
        else
        {
            mTranslateMatrix.translate(-mPosition[0] + mShakeCurrentPosition, -mPosition[1],
                -mPosition[2]);
        }

    }

    void Camera::shakeCamera(float inMagnitude, float inSpeed, float inRateOfDecay)
    {
        mShakeMagnitudes.push_back(inMagnitude);
        mShakeSpeeds.push_back(inSpeed);
        mShakeRatesOfDecay.push_back(inRateOfDecay);
    }

    void Camera::calculateShakePosition()
    {
        if (mShakeMagnitudes.size() > 0)
        {
            float currentMagnitude = 0.0f;

            //using iterators to run through the lists makes it easier to remove elements
            vector<float>::iterator magnitude = mShakeMagnitudes.begin();
            vector<float>::iterator speed = mShakeSpeeds.begin();
            vector<float>::iterator rateOfDecay = mShakeRatesOfDecay.begin();

            while (magnitude != mShakeMagnitudes.end())
            {
                currentMagnitude += *magnitude;
                mShakeCurrentDegrees += *speed;
                *magnitude -= *rateOfDecay;

                if (*magnitude <= 0.0f)
                {
                    magnitude = mShakeMagnitudes.erase(magnitude);
                    speed = mShakeSpeeds.erase(speed);
                    rateOfDecay = mShakeRatesOfDecay.erase(rateOfDecay);


                }
                else
                {
                    ++magnitude;
                    ++speed;
                    ++rateOfDecay;
                }
            }
            mShakeCurrentPosition = sin(TO_RADIANS(mShakeCurrentDegrees)) * currentMagnitude;

            if (mShakeMagnitudes.size() == 0)
            {
                mShakeCurrentDegrees = 0.0f;
                mShakeCurrentPosition = 0.0f;
            }
        }
    }

    void Camera::setDistance(float inDistance)
    {
        if (inDistance < 0.0f)
            mDistance = 0.0f;
        else
            mDistance = inDistance;
    }

    void Camera::changeDistance(float inOffset)
    {
        setDistance(mDistance + inOffset);
    }

    void Camera::setRotation(float inRotation)
    {
        if (inRotation < 0.0f)
            mRotation = fmod(inRotation - 180.0f, 360.0f) + 180.0f;
        else
            mRotation = fmod(inRotation + 180.0f, 360.0f) - 180.0f;
    }

    void Camera::changeRotation(float inOffset)
    {
        setRotation(mRotation + inOffset);
    }

    void Camera::setAngle(float inAngle)
    {
        if (inAngle < 0.0f)
            mAngle = fmod(inAngle - 180.0f, 360.0f) + 180.0f;
        else
            mAngle = fmod(inAngle + 180.0f, 360.0f) - 180.0f;
    }

    void Camera::changeAngle(float inOffset)
    {
        setAngle(mAngle + inOffset);
    }

    void Camera::setPosition(float inX, float inY, float inZ)
    {
        mPosition[0] = inX;
        mPosition[1] = inY;
        mPosition[2] = inZ;
    }

    void Camera::changePosition(float inX, float inY, float inZ)
    {
        mPosition[0] = inX;
        mPosition[1] = inY;
        mPosition[2] = inZ;
    }

    void Camera::smartPan(float inX, float inY)
    {
         float theta = TO_RADIANS(mRotation);
         float c = cos(theta);
         float s = sin(theta);

         float dxp = c * inX;
         float dyp = -s * inX;
         dxp += s * inY;
         dyp += c * inY;

         mPosition[0] += dxp;
         mPosition[1] += dyp;
    }

    void Camera::unfollow(bool inCopyTargetPosition)
    {
        if (mFollow && inCopyTargetPosition) mPosition = mFollow;

        mFollow = NULL;
    }

    void Camera::unfollow(const float* inTarget, bool inCopyTargetPosition)
    {
        if (mFollow == inTarget) unfollow(inCopyTargetPosition);
    }
}
