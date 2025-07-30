#include "pixeltoworld.h"

// CameraPose implementation
PixelToWorld::CameraPose::CameraPose(const QVector3D& pos, const QVector3D& rot)
    : position(pos), rotation(rot)
{
    updateRotationMatrix();
}

void PixelToWorld::CameraPose::updateRotationMatrix()
{
    rotationMatrix = PixelToWorld::eulerToRotationMatrix(
        rotation.x(), rotation.y(), rotation.z());
}

// PixelToWorld implementation
PixelToWorld::PixelToWorld(QObject *parent)
    : QObject(parent), m_intrinsicsSet(false), m_poseSet(false)
{
}

void PixelToWorld::setCameraIntrinsics(const CameraIntrinsics& intrinsics)
{
    m_intrinsics = intrinsics;
    m_intrinsicsSet = true;
}

void PixelToWorld::setCameraPose(const CameraPose& pose)
{
    m_pose = pose;
    m_poseSet = true;
}

QVector3D PixelToWorld::pixelToWorld(const QVector2D& pixel, float depth) const
{
    if (!m_intrinsicsSet || !m_poseSet) {
        qWarning() << "Camera intrinsics or pose not set";
        return QVector3D();
    }

    return pixelToWorld(pixel, depth, m_intrinsics, m_pose);
}

QVector3D PixelToWorld::pixelToWorld(const QVector2D& pixel, float depth,
                                     const CameraIntrinsics& intrinsics,
                                     const CameraPose& pose)
{
    // Validate depth
    if (!isValidDepth(depth)) {
        qWarning() << "Invalid depth value:" << depth;
        return QVector3D();
    }

    // Extract pixel coordinates
    float u = pixel.x();
    float v = pixel.y();

    // Convert to normalized camera coordinates
    // Since image is already undistorted, we can directly use pixel coordinates
    float x_norm = (u - intrinsics.cx) / intrinsics.fx;
    float y_norm = (v - intrinsics.cy) / intrinsics.fy;

    // Calculate 3D point in camera frame
    QVector3D point_cam(x_norm * depth, y_norm * depth, depth);

    // Transform to world frame: point_world = R * point_cam + t
    QVector3D point_world = pose.rotationMatrix.map(point_cam) + pose.position;

    return point_world;
}

QMatrix4x4 PixelToWorld::eulerToRotationMatrix(float roll, float pitch, float yaw)
{
    float cx = std::cos(roll),  sx = std::sin(roll);
    float cy = std::cos(pitch), sy = std::sin(pitch);
    float cz = std::cos(yaw),   sz = std::sin(yaw);

    // Create rotation matrix using QMatrix4x4
    QMatrix4x4 rotMatrix;

    // Combined rotation: R = R_z(yaw) * R_y(pitch) * R_x(roll)
    // Row 0
    rotMatrix(0, 0) = cy * cz;
    rotMatrix(0, 1) = -cy * sz;
    rotMatrix(0, 2) = sy;
    rotMatrix(0, 3) = 0.0f;

    // Row 1
    rotMatrix(1, 0) = sx * sy * cz + cx * sz;
    rotMatrix(1, 1) = -sx * sy * sz + cx * cz;
    rotMatrix(1, 2) = -sx * cy;
    rotMatrix(1, 3) = 0.0f;

    // Row 2
    rotMatrix(2, 0) = -cx * sy * cz + sx * sz;
    rotMatrix(2, 1) = cx * sy * sz + sx * cz;
    rotMatrix(2, 2) = cx * cy;
    rotMatrix(2, 3) = 0.0f;

    // Row 3
    rotMatrix(3, 0) = 0.0f;
    rotMatrix(3, 1) = 0.0f;
    rotMatrix(3, 2) = 0.0f;
    rotMatrix(3, 3) = 1.0f;

    return rotMatrix;
}

bool PixelToWorld::isValidDepth(float depth, float minDepth, float maxDepth)
{
    return (depth > minDepth && depth < maxDepth && std::isfinite(depth));
}
