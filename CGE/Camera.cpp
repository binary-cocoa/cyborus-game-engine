#include "Camera.h"
#include "Tools.h"

using namespace std;

namespace CGE
{
    Camera::Camera() : mDistance(0.0f), mRotation(0.0f), mAngle(0.0f),
        mFollow(NULL), mShakeCurrentPositionX(0.0f), mShakeCurrentPositionY(0.0f), mShakeCurrentDegrees(0.0f)
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
            mTranslateMatrix.translate(-mFollow[0] + mShakeCurrentPositionX, -mFollow[1] + mShakeCurrentPositionY,
                -mFollow[2]);
        }
        else
        {
            mTranslateMatrix.translate(-mPosition[0] + mShakeCurrentPositionX, -mPosition[1] + mShakeCurrentPositionY,
                -mPosition[2]);
        }

    }

    void Camera::shakeCamera(float inMagnitude, float inSpeed, float inRateOfDecay)
    {
        mShakeMagnitudes.push_back(inMagnitude);
        mShakeSpeeds.push_back(inSpeed);
        mShakeRatesOfDecay.push_back(inRateOfDecay);
    }

    void Camera::stopCameraShake()
    {
        vector<float>::iterator rateOfDecay = mShakeRatesOfDecay.begin();
        vector<float>::iterator magnitude = mShakeMagnitudes.begin();

        while (rateOfDecay != mShakeRatesOfDecay.end())
        {
            *rateOfDecay = *magnitude;
            ++rateOfDecay;
            ++magnitude;
        }
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

                    if (mShakeMagnitudes.size() == 0)
                    {
                        mShakeCurrentDegrees = 0.0f;
                        mShakeCurrentPositionX = 0.0f;
                        mShakeCurrentPositionY = 0.0f;
                    }
                }
                else
                {
                    ++magnitude;
                    ++speed;
                    ++rateOfDecay;
                }
            }
            float radians = TO_RADIANS(mShakeCurrentDegrees);
            //float sinResult = ;
            mShakeCurrentPositionX = sin(radians) * currentMagnitude;
            mShakeCurrentPositionY = sin(radians * 2) * currentMagnitude;
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
