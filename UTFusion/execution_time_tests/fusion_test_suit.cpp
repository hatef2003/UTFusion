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

    float rot[3] = {0.123,1.23,2.123},pos[3] = {123.12,12.32,0.321};
    PixelToWorld::CameraPose pose(rot, pos);
    this->fusion->setCameraPose(pose);

    std::vector<Fusion::RadarData> radars = {
        {1.0f, 0.0f, 0.0f, 1.2f},
        {1.0f, 0.0f, 0.0f, 1.2f},
        {1.0f, 0.0f, 0.0f, 1.2f},
        {2.0f, 0.0f, 0.0f, 2.2f}
    };
    this->fusion->setRadars(radars);
    this->fusion->setEpsilon(0.5f);

    //TODO: fix size
    this->objects = std::vector<std::vector<Fusion::PixelData>>(80, std::vector<Fusion::PixelData>
                                                                (640*480, Fusion::PixelData(1.2f, 320.0f, 240.0f)));
}

void FusionTestSuit::test_perform_fusion()
{
    this->fusion->performFusion(this->objects);
}

QStringList FusionTestSuit::run_suit()
{
    QStringList results;

    results << "FusionTestSuit:";
    results << benchmark("setup", [this]() {
        this->setup();
    }, 1);
    results << benchmark("performFusion", [this]() {
        this->test_perform_fusion();
    }, 5);

    for (const QString& line : results) {
        qDebug() << line;
    }

    return results;
}
