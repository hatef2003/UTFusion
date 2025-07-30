#include <QCoreApplication>
#include <QImage>
#include <buffer.h>
#include "MockRadarData.h"
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

    MockRadarData radar;
    radar.startServer(8000); // Start server on port 8000

    QObject::connect(&radar, &MockRadarData::dataReceived, [](const QList<uint> &values, qint64 timestamp){
        qDebug() << "Received values:" << values << "Timestamp:" << timestamp;
    });

    return app.exec();
}
