#include "mockimagereciever_test.h"
#include <iostream>
#include <QCoreApplication>
#include <QEventLoop>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include "mockimagereceiver.h"
#include <QBuffer>

static QByteArray makePacket(const QByteArray &img1, const QByteArray &img2) {
    QByteArray pkt;
    QDataStream ds(&pkt, QIODevice::WriteOnly);
    ds.setByteOrder(QDataStream::BigEndian);
    ds << quint32(img1.size());
    pkt.append(img1);
    ds << quint32(img2.size());
    pkt.append(img2);
    return pkt;
}



void mockimagereciever_test::run_all_mockimagereciever_tests() {
    std::cout << "========== mockimagereciever_tests: ==========" << std::endl;
    struct Test { const char* name; bool (mockimagereciever_test::*fn)(); };
    Test tests[] = {

        {"testIgnoreIncompletePacket", &mockimagereciever_test::testIgnoreIncompletePacket}
    };
    int passed = 0;
    int total = sizeof(tests)/sizeof(tests[0]);
    for (auto &t : tests) {
        bool ok = (this->*t.fn)();
        std::cout << t.name << ": " << (ok ? "PASS" : "FAIL") << std::endl;
        if (ok) ++passed;
    }
    std::cout << "Summary: Passed "  << passed << " of " << total << " tests." << std::endl;
}

bool mockimagereciever_test::testIgnoreIncompletePacket() {
    MockImageReceiver recv;
    recv.startServer(0);
    bool called = false;
    connect(&recv, &MockImageReceiver::imagesReceived,
            [&](auto, auto, qint64){ called = true; });

    quint16 port = recv.findChild<QTcpServer*>()->serverPort();
    QTcpSocket sock;
    sock.connectToHost(QHostAddress::LocalHost, port);
    if (!sock.waitForConnected(500)) return false;

    // send wrong size header and no data
    QByteArray bad;
    QDataStream ds(&bad, QIODevice::WriteOnly);
    ds.setByteOrder(QDataStream::BigEndian);
    ds << quint32(1000); // declare large size
    sock.write(bad);
    sock.flush();

    QEventLoop loop;
    QTimer::singleShot(300, &loop, &QEventLoop::quit);
    loop.exec();
    return !called;
}
