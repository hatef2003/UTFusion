#include <QCoreApplication>
#include <QImage>
#include "MockImageReceiver.h"
#include "MockRadarData.h"
#include "datacontainer.h"
#include <buffer.h>
// int main(int argc, char *argv[])
// {
//     QCoreApplication a(argc, argv);
//     Buffer b;
//     b.addRadar({1, 2, 4, 5, 6, 7, 213213});
//     QImage image;
//     b.addCam({&image, &image, 213214});
//     // qDebug() << b.isSync() << (0 ^ 1) << (1 ^ 1);
//     // Set up code that uses the Qt event loop here.
//     // Call a.quit() or a.exit() to quit the application.
//     // A not very useful example would be including
//     // #include <QTimer>
//     // near the top of the file and calling
//     // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
//     // which quits the application after 5 seconds.

//     // If you do not need a running Qt event loop, remove the call
//     // to a.exec() or use the Non-Qt Plain C++ Application template.

//     return a.exec();
// }
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    DataContainer dataContainer;
    MockRadarData radar;
    MockImageReceiver mockImageReceiver;
    mockImageReceiver.startServer(8080); // Start server on port 8080
    radar.startServer(8000); // Start server on port 8000

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
                         cameraData.image1 = const_cast<QImage*>(&img1);
                         cameraData.image2 = const_cast<QImage*>(&img2);
                         dataContainer.newCamData(cameraData);
                     });

    return app.exec();
}
