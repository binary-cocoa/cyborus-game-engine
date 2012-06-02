#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix4x4.h"
#include "Vectors.h"
#include "Tools.h"

#include <list>

namespace CGE
{
    class Camera
    {
        public:
            Camera();
            ~Camera();

            inline const mat4f& getTranslateMatrix() const
            {
                return mTranslateMatrix;
            }

            inline const mat4f& getAngleMatrix() const
            {
                return mAngleMatrix;
            }

            inline void follow(const float* inTarget)
            {
                mFollow = inTarget;
            }

            void update();
            void setDistance(float inDistance);
            void changeDistance(float inOffset);
            void setRotation(float inRotation);
            void changeRotation(float inOffset);
            void setAngle(float inAngle);
            void changeAngle(float inOffset);
            void setPosition(float inX, float inY, float inZ);
            void changePosition(float inX, float inY, float inZ);
            void smartPan(float inX, float inY);

            void unfollow(bool inCopyTargetPosition = true);
            void unfollow(const float* inTarget,
                bool inCopyTargetPosition = true);

            void shakeCamera(double inMagnitude, double inSpeed,
                double inRateOfDecay);

            void stopCameraShake();

        private:
            void calculateShakePosition();

            mat4f mTranslateMatrix;
            mat4f mAngleMatrix;
            vec3f mPosition;
            float mDistance;
            float mRotation;
            float mAngle;
            const float* mFollow;
            float mShakeCurrentPositionX;
            float mShakeCurrentPositionY;
            std::list<double> mShakeMagnitudes;
            std::list<double> mShakeSpeeds;
            double mShakeCurrentDegrees;
            std::list<double> mShakeRatesOfDecay;
    };
}

#endif
