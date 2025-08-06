#include "mockimagereciever_test.h"
#include <iostream>
#include <QCoreApplication>
#include <QEventLoop>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include "mockimagereceiver.h"

void mockimagereciever_test::run() {
    const char* name = "testImagesReceived";
    bool ok = testImagesReceived();
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << "\n";
}

bool mockimagereciever_test::testImagesReceived() {
    int argc = 0; char** argv = nullptr;
    QCoreApplication app(argc, argv);

    MockImageReceiver receiver;
    receiver.startServer(0);
    quint16 port = receiver.findChild<QTcpServer*>()->serverPort();

    bool called = false;
    QObject::connect(&receiver, &MockImageReceiver::imagesReceived,
                     [&](const QImage &img1, const QImage &img2, qint64 ts){
                         called = true;
                     });

    // Connect clnts
    QTcpSocket sock;
    sock.connectToHost(QHostAddress::LocalHost, port);
    if (!sock.waitForConnected(1000)) return false;

    QByteArray dummy1(10, '\xAA'), dummy2(20, '\xBB');
    QByteArray pkt;
    QDataStream ds(&pkt, QIODevice::WriteOnly);
    ds.setByteOrder(QDataStream::BigEndian);
    ds << quint32(dummy1.size()); pkt.append(dummy1);
    ds << quint32(dummy2.size()); pkt.append(dummy2);

    sock.write(pkt);
    sock.flush();


    QEventLoop loop;
    QTimer::singleShot(500, &loop, &QEventLoop::quit);
    loop.exec();

    return called;
}
