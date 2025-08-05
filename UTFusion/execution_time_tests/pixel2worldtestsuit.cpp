#include "pixel2worldtestsuit.h"

#define CAM_FX 1146.3511547076373
#define CAM_FY 1096.8692812423094
#define CAM_CX 346.74179054850418
#define CAM_CY 227.22216526982555

Pixel2WorldTestsuit::Pixel2WorldTestsuit() {}

void Pixel2WorldTestsuit::setup()
{
    this->intrinsics.fx = CAM_FX;
    this->intrinsics.fy = CAM_FY;
    this->intrinsics.cx = CAM_CX;
    this->intrinsics.cy = CAM_CY;
    this->p2w.setCameraIntrinsics(this->intrinsics);

    float rot[3] = {0.123,1.23,2.123},pos[3] = {123.12,12.32,0.321};
    this->pose=PixelToWorld::CameraPose(rot,pos);

    float arr[4][4] = {
        {123.932,123.23,32.32,32.91},
        {123.932,123.23,32.32,32.91},
        {123.932,123.23,32.32,32.91},
        {123.932,123.23,32.32,32.91}
    };
    PixelToWorld::Matrix4x4 rotmat(arr);

    this->pose.rotationMatrix=rotmat;

    this->p2w.setCameraPose(this->pose);
}

void Pixel2WorldTestsuit::test_pixelToWorld()
{
    this->p2w.pixelToWorld(this->pixels, 120.12f, this->intrinsics, this->pose);
}

void Pixel2WorldTestsuit::test_pixelToWorld_static()
{
    this->p2w.pixelToWorld(this->pixels, 120.12f);
}

void Pixel2WorldTestsuit::test_isValidDepth()
{
    this->p2w.isValidDepth(123.12);
}

void Pixel2WorldTestsuit::test_updateRotationMatrix()
{
    this->pose.updateRotationMatrix();
}

void Pixel2WorldTestsuit::test_eulerToRotationMatrix()
{
    this->pose.eulerToRotationMatrix(1.312,1.23,2.321);
}

QStringList Pixel2WorldTestsuit::run_suit()
{
    QStringList results;

    results << "Pixel2WorldTestSuit:";
    this->setup();

    results << benchmark("pixel2World", [this]() {
        this->test_pixelToWorld();
    }, 5);
    results << benchmark("pixel2World_static", [this]() {
        this->test_pixelToWorld_static();
    }, 5);
    results << benchmark("isValidDepth", [this]() {
        this->test_isValidDepth();
    }, 5);
    results << benchmark("updateRotationMatrix", [this]() {
        this->test_updateRotationMatrix();
    }, 5);
    results << benchmark("eulerToRotationMatrix", [this]() {
        this->test_eulerToRotationMatrix();
    }, 5);

    for (const QString& line : results) {
        qDebug() << line;
    }

    return results;
}
