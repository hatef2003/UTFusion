#ifndef PIXELTOWORLD_H
#define PIXELTOWORLD_H

#include <QObject>
#include <QVector3D>
#include <QVector2D>
#include <QMatrix4x4>
#include <QDebug>
#include <cmath>


class PixelToWorld : public QObject
{
    Q_OBJECT

public:
    struct CameraIntrinsics {
        double fx, fy;    // Focal lengths
        double cx, cy;    // Principal point

        CameraIntrinsics() = default;
        CameraIntrinsics(double fx, double fy, double cx, double cy)
            : fx(fx), fy(fy), cx(cx), cy(cy) {}
    };

    struct CameraPose {
        QVector3D position;    // Camera position in world frame
        QVector3D rotation;    // Roll, Pitch, Yaw in radians
        QMatrix4x4 rotationMatrix;

        CameraPose() = default;
        CameraPose(const QVector3D& pos, const QVector3D& rot);
        void updateRotationMatrix();
    };

    explicit PixelToWorld(QObject *parent = nullptr);

    /**
     * @brief Set camera intrinsic parameters
     */
    void setCameraIntrinsics(const CameraIntrinsics& intrinsics);

    /**
     * @brief Set camera pose in world frame
     */
    void setCameraPose(const CameraPose& pose);

    /**
     * @brief Convert pixel to world coordinates (undistorted image)
     *
     * @param pixel Pixel coordinates (u, v) in undistorted image
     * @param depth Depth value at the pixel (must be > 0)
     * @return 3D point in world coordinates
     */
    QVector3D pixelToWorld(const QVector2D& pixel, float depth) const;

    /**
     * @brief Convert pixel to world coordinates (static version)
     */
    static QVector3D pixelToWorld(const QVector2D& pixel, float depth,
                                  const CameraIntrinsics& intrinsics,
                                  const CameraPose& pose);

    /**
     * @brief Create rotation matrix from Euler angles (roll, pitch, yaw)
     * Convention: R = R_z(yaw) * R_y(pitch) * R_x(roll)
     */
    static QMatrix4x4 eulerToRotationMatrix(float roll, float pitch, float yaw);

    /**
     * @brief Validate depth value
     */
    static bool isValidDepth(float depth, float minDepth = 0.1f, float maxDepth = 100.0f);

signals:
    void worldPointCalculated(const QVector3D& worldPoint) const;
    void projectionError(const QString& error) const;

private:
    CameraIntrinsics m_intrinsics;
    CameraPose m_pose;
    bool m_intrinsicsSet;
    bool m_poseSet;
};

#endif // PIXELTOWORLD_H
