#include "pixel2world.h"

PixelToWorld::CameraPose::CameraPose(float pos[3], float rot[3])
{
    position[0] = pos[0];
    position[1] = pos[1];
    position[2] = pos[2];
    rotation[0] = rot[0];
    rotation[1] = rot[1];
    rotation[2] = rot[2];
    updateRotationMatrix();
}

void PixelToWorld::CameraPose::updateRotationMatrix()
{
    rotationMatrix = PixelToWorld::CameraPose::eulerToRotationMatrix(
        rotation[0], rotation[1], rotation[2]);
}

PixelToWorld::PixelToWorld()
    : m_intrinsicsSet(false), m_poseSet(false)
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

float* PixelToWorld::pixelToWorld(float pixel[2], float depth) const
{
    if (!m_intrinsicsSet || !m_poseSet) {
        // qWarning() << "Camera intrinsics or pose not set";
        return NULL;
    }

    return pixelToWorld(pixel, depth, m_intrinsics, m_pose);
}

float* PixelToWorld::pixelToWorld(const float pixel[2], float depth,
                                     const CameraIntrinsics& intrinsics,
                                     const CameraPose& pose)
{
    if (!isValidDepth(depth)) {
        // qWarning() << "Invalid depth value:" << depth;
        return NULL;
    }

    float x_norm = (pixel[0] - intrinsics.cx) / intrinsics.fx;
    float y_norm = (pixel[1] - intrinsics.cy) / intrinsics.fy;

    float point_cam[3] = {x_norm * depth, y_norm * depth, depth};


    // map according to QT, yeah i read the fucking library
    float point_world[3];
    point_world[0] = pose.rotationMatrix.m[0][0] * point_cam[0] +
                        pose.rotationMatrix.m[0][1] * point_cam[1] +
                        pose.rotationMatrix.m[0][2] * point_cam[2] +
                        pose.rotationMatrix.m[0][3] * 1.0f;
    point_world[1] = pose.rotationMatrix.m[1][0] * point_cam[0] +
                        pose.rotationMatrix.m[1][1] * point_cam[1] +
                        pose.rotationMatrix.m[1][2] * point_cam[2] +
                        pose.rotationMatrix.m[1][3] * 1.0f;
    point_world[2] = pose.rotationMatrix.m[2][0] * point_cam[0] +
                        pose.rotationMatrix.m[2][1] * point_cam[1] +
                        pose.rotationMatrix.m[2][2] * point_cam[2] +
                        pose.rotationMatrix.m[2][3] * 1.0f;
    float w =           pose.rotationMatrix.m[3][0] * point_cam[0] +
                        pose.rotationMatrix.m[3][1] * point_cam[1] +
                        pose.rotationMatrix.m[3][2] * point_cam[2] +
                        pose.rotationMatrix.m[3][3] * 1.0f;
    point_world[0] /= w;
    point_world[1] /= w;
    point_world[2] /= w;

    point_world[0] += pose.position[0];
    point_world[1] += pose.position[1];
    point_world[2] += pose.position[2];
    //  = pose.rotationMatrix.map(point_cam) + pose.position;

    return point_world;
}

PixelToWorld::Matrix4x4 PixelToWorld::CameraPose::eulerToRotationMatrix(float roll, float pitch, float yaw)
{
    float cx = std::cos(roll),  sx = std::sin(roll);
    float cy = std::cos(pitch), sy = std::sin(pitch);
    float cz = std::cos(yaw),   sz = std::sin(yaw);

    Matrix4x4 rotMatrix;

    // Combined rotation: R = R_z(yaw) * R_y(pitch) * R_x(roll)
    // Row 0
    rotMatrix.m[0][0] = cy * cz;
    rotMatrix.m[0][1] = -cy * sz;
    rotMatrix.m[0][2] = sy;
    rotMatrix.m[0][3] = 0.0f;

    // Row 1
    rotMatrix.m[1][0] = sx * sy * cz + cx * sz;
    rotMatrix.m[1][1] = -sx * sy * sz + cx * cz;
    rotMatrix.m[1][2] = -sx * cy;
    rotMatrix.m[1][3] = 0.0f;

    // Row 2
    rotMatrix.m[2][0] = -cx * sy * cz + sx * sz;
    rotMatrix.m[2][1] = cx * sy * sz + sx * cz;
    rotMatrix.m[2][2] = cx * cy;
    rotMatrix.m[2][3] = 0.0f;

    // Row 3
    rotMatrix.m[3][0] = 0.0f;
    rotMatrix.m[3][1] = 0.0f;
    rotMatrix.m[3][2] = 0.0f;
    rotMatrix.m[3][3] = 1.0f;

    return rotMatrix;
}

bool PixelToWorld::isValidDepth(float depth, float minDepth, float maxDepth)
{
    return (depth > minDepth && depth < maxDepth && std::isfinite(depth));
}
