#ifndef PIXELTOWORLD_H
#define PIXELTOWORLD_H

#include <cmath>


class PixelToWorld
{
    
private:
    CameraIntrinsics m_intrinsics;
    CameraPose m_pose;
    bool m_intrinsicsSet;
    bool m_poseSet;
    struct Matrix4x4 {
        float m[4][4];
    };

public:
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
    };

    explicit PixelToWorld();
    void setCameraIntrinsics(const CameraIntrinsics& intrinsics);
    void setCameraPose(const CameraPose& pose);

    /**
     * @brief Convert pixel to world coordinates (undistorted image)
     *
     * @param pixel Pixel coordinates (u, v) in undistorted image
     * @param depth Depth value at the pixel (must be > 0)
     * @return 3D point in world coordinates
     */
    float* pixelToWorld(float pixel[2], float depth) const;

    /**
     * @brief Convert pixel to world coordinates (static version)
     */
    static float* pixelToWorld(const float pixel[2], float depth,
                                  const CameraIntrinsics& intrinsics,
                                  const CameraPose& pose);

    /**
     * @brief Create rotation matrix from Euler angles (roll, pitch, yaw)
     * Convention: R = R_z(yaw) * R_y(pitch) * R_x(roll)
     */
    static Matrix4x4 eulerToRotationMatrix(float roll, float pitch, float yaw);

    static bool isValidDepth(float depth, float minDepth = 0.1f, float maxDepth = 100.0f);

// signals:
//     void worldPointCalculated(const QVector3D& worldPoint) const;
//     void projectionError(const QString& error) const;

};

#endif // PIXELTOWORLD_H
