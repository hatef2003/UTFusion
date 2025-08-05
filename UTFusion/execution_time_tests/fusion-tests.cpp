#include "FusionUtils/pixel2world.h"
#include "FusionUtils/distance_calculator.h"
#include "FusionUtils/fusion.h"

void fusion_test_simple() {
    Fusion fusion;

    PixelToWorld::CameraIntrinsics intrinsics;
    intrinsics.fx = CAM_FX;
    intrinsics.fy = CAM_FY;
    intrinsics.cx = CAM_CX;
    intrinsics.cy = CAM_CY;
    fusion.setCameraIntrinsics(intrinsics);

    float rot[3] = {0,0,0},pos[3] = {0,0,0};
    PixelToWorld::CameraPose pose(rot, pos);
    fusion.setCameraPose(pose);

    std::vector<Fusion::RadarData> radars = {
        {1.0f, 0.0f, 0.0f, 1.2f},
        {2.0f, 0.0f, 0.0f, 2.2f}
    };
    fusion.setRadars(radars);
    fusion.setEpsilon(0.5f);

    Fusion::ObjectVector objects = {
        {
            {1.2f, 320.0f, 240.0f},
            {1.2f, 321.0f, 241.0f}
        }
    };

    std::vector<Fusion::FusionOutput> results = fusion.performFusion(objects);
}
