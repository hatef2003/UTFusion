#include <QCoreApplication>
#include <QImage>
#include "MockImageReceiver.h"
#include "MockRadarData.h"
#include "datacontainer.h"
#include "erfanmocker.h"
#include<fuse.h>
#include <buffer.h>
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    DataContainer dataContainer;
    MockRadarData radar;
    MockImageReceiver mockImageReceiver;
    mockImageReceiver.startServer(8080); // Start server on port 8080
    radar.startServer(8000);             // Start server on port 8000
    
    QObject::connect(&radar,
                     &MockRadarData::dataReceived,
                     [&dataContainer](const QList<uint> &values, qint64 timestamp) {
                         Buffer::RadarData radarData;
                         radarData.timestamp = timestamp;
                         radarData.a = values[1];
                         radarData.b = values[2];
                         radarData.c = values[3];
                         radarData.d = values[4];
                         radarData.e = values[5];
                         radarData.f = values[6];
                         dataContainer.newRadarData(radarData);
                     });
    QObject::connect(&mockImageReceiver,
                     &MockImageReceiver::imagesReceived,
                     [&dataContainer](const QImage &img1, const QImage &img2, qint64 timestamp) {
                         Buffer::CameraData cameraData;
                         cameraData.timestamp = timestamp;
                         cameraData.image1 = const_cast<QImage *>(&img1);
                         cameraData.image2 = const_cast<QImage *>(&img2);
                         dataContainer.newCamData(cameraData);
                     });
    ErfanMocker erfanMocker;
    erfanMocker.startServer(8001); // Start server on port 8001
    Fuse fuse;
    QObject::connect(&erfanMocker, &ErfanMocker::dataReceived, &fuse, &Fuse::dataRecieve);
    return app.exec();
}
