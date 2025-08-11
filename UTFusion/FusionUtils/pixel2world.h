#ifndef PIXELTOWORLD_H
#define PIXELTOWORLD_H

#include <cmath>


class PixelToWorld
{
public:
    struct Matrix4x4 {
        float m[4][4];
        Matrix4x4() = default;
        Matrix4x4(float _m[4][4]) {
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    m[i][j] = _m[i][j];
        }
    };
    struct CameraIntrinsics {
        double fx, fy;    // Focal lengths
        double cx, cy;    // Principal point

        CameraIntrinsics() = default;
        CameraIntrinsics(double fx, double fy, double cx, double cy)
            : fx(fx), fy(fy), cx(cx), cy(cy) {}
    };

    struct CameraPose {
        float position[3];
        float rotation[3];
        
        Matrix4x4 rotationMatrix;

        CameraPose() = default;
        CameraPose(float pos[3], float rot[3]);
        void updateRotationMatrix();


        Matrix4x4 eulerToRotationMatrix(float roll, float pitch, float yaw);

    };

private:
    CameraIntrinsics m_intrinsics;
    CameraPose m_pose;
    bool m_intrinsicsSet;
    bool m_poseSet;

public:
    explicit PixelToWorld();
    void setCameraIntrinsics(const CameraIntrinsics& intrinsics);
    void setCameraPose(const CameraPose& pose);

    float* pixelToWorld(float pixel[2], float depth) const;


    static float* pixelToWorld(const float pixel[2], float depth,
                                  const CameraIntrinsics& intrinsics,
                                  const CameraPose& pose);

    static bool isValidDepth(float depth, float minDepth = 0.1f, float maxDepth = 100.0f);

};

#endif 
