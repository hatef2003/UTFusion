#include "fusion_test_suit.h"

FusionTestSuit::FusionTestSuit() {}

void FusionTestSuit::setup()
{
    this->fusion = new Fusion();

    PixelToWorld::CameraIntrinsics intrinsics;
    intrinsics.fx = CAM_FX;
    intrinsics.fy = CAM_FY;
    intrinsics.cx = CAM_CX;
    intrinsics.cy = CAM_CY;
    this->fusion->setCameraIntrinsics(intrinsics);

    float rot[3] = {0,0,0},pos[3] = {0,0,0};
    PixelToWorld::CameraPose pose(rot, pos);
    this->fusion->setCameraPose(pose);

    std::vector<Fusion::RadarData> radars = {
        {1.0f, 0.0f, 0.0f, 1.2f},
        {2.0f, 0.0f, 0.0f, 2.2f}
    };
    this->fusion->setRadars(radars);
    this->fusion->setEpsilon(0.5f);

    this->objects = {
        {
            {1.2f, 320.0f, 240.0f},
            {1.2f, 321.0f, 241.0f}
        }
    };
}

void FusionTestSuit::test_perform_fusion()
{
    this->fusion->performFusion(this->objects);
}

void FusionTestSuit::run_suit()
{
    this->setup();
    benchmark("dummy test", [this]() {
        this->test_perform_fusion();
    }, 5);
}
