#include "datatestsuit.h"
#include <QImage>

DataTestsuit::DataTestsuit() {}

void DataTestsuit::setup()
{
    setup_container();
    setup_buf();
}

void DataTestsuit::setup_buf()
{
    QImage img1(640, 480, QImage::Format_RGB32);
    img1.fill(Qt::black);
    QImage img2(640, 480, QImage::Format_RGB32);
    img2.fill(Qt::white);

    this->buf.addRadar({2100, 1, 2, 3, 4, 5, 6});
    this->buf.addCam({&img1, &img2, 2000});
}

void DataTestsuit::setup_container()
{
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();

    Buffer::RadarData radarData = {timestamp, 1, 2, 3, 4, 5, 6};
    QImage* img1 = new QImage(640, 480, QImage::Format_RGB32);
    QImage* img2 = new QImage(640, 480, QImage::Format_RGB32);
    img1->fill(Qt::black);
    img2->fill(Qt::white);
    Buffer::CameraData camData = {img1, img2, timestamp};

    qint64 timestamp2 = timestamp + 15;

    Buffer::RadarData radarData2 = {timestamp2, 1, 2, 3, 4, 5, 6};
    Buffer::CameraData camData2 = {img1, img2, timestamp2};

    this->container.newRadarData(radarData);
    this->container.newCamData(camData);

    this->container.newRadarData(radarData2);
    this->container.newCamData(camData2);
}

void DataTestsuit::test_buffer_isValid()
{
    this->buf.isSync();
}

void DataTestsuit::test_container_getData()
{
    this->container.getData();
}

QStringList DataTestsuit::run_suit()
{
    QStringList results;

    results << "DataTestSuit:";
    results << benchmark("setup_buf", [this]() {
        this->setup_buf();
    }, 1);
    results << benchmark("setup_container", [this]() {
        this->setup_container();
    }, 1);

    results << benchmark("buffer_isValid", [this]() {
        this->test_buffer_isValid();
    }, 5);

    results << benchmark("container_getData", [this]() {
        this->test_container_getData();
    }, 1);

    for (const QString& line : results) {
        qDebug() << line;
    }

    return results;
}
