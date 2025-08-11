#ifndef PIXEL2WORLDTESTSUIT_H
#define PIXEL2WORLDTESTSUIT_H

#include "testsuit.h"
#include "FusionUtils/pixel2world.h"

class Pixel2WorldTestsuit : public TestSuit
{
    PixelToWorld p2w;
    PixelToWorld::CameraPose pose;
    PixelToWorld::CameraIntrinsics intrinsics;

    float pixels[2] = {120.12f, 98.002};

public:
    Pixel2WorldTestsuit();
    void setup();
    void test_pixelToWorld();
    void test_pixelToWorld_static();
    void test_isValidDepth();
    void test_updateRotationMatrix();
    void test_eulerToRotationMatrix();

    QStringList run_suit();

};

#endif 
