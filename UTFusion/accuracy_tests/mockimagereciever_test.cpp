#include "mockimagereciever_test.h"
#include <iostream>
#include <QCoreApplication>
#include <QEventLoop>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include "mockimagereceiver.h"

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
        {"testReceiveSingleFrame",     &mockimagereciever_test::testReceiveSingleFrame},
        {"testReceiveFragmentedFrame", &mockimagereciever_test::testReceiveFragmentedFrame},
        {"testReceiveMultipleFrames",  &mockimagereciever_test::testReceiveMultipleFrames},
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




bool mockimagereciever_test::testReceiveSingleFrame() {
    MockImageReceiver recv;
    recv.startServer(0);
    bool called = false;
    connect(&recv, &MockImageReceiver::imagesReceived,
            [&](const QImage&, const QImage&, qint64){ called = true; });

    quint16 port = recv.findChild<QTcpServer*>()->serverPort();
    QTcpSocket sock;
    sock.connectToHost(QHostAddress::LocalHost, port);
    if (!sock.waitForConnected(500)) return false;

    QByteArray img1(10, '\xFF'), img2(20, '\xAA');
    sock.write(makePacket(img1, img2));
    sock.flush();

    QEventLoop loop;
    QTimer::singleShot(300, &loop, &QEventLoop::quit);
    loop.exec();
    return called;
}



bool mockimagereciever_test::testReceiveFragmentedFrame() {
    MockImageReceiver recv;
    recv.startServer(0);
    bool called = false;
    connect(&recv, &MockImageReceiver::imagesReceived,
            [&](auto, auto, qint64){ called = true; });

    quint16 port = recv.findChild<QTcpServer*>()->serverPort();
    QTcpSocket sock;
    sock.connectToHost(QHostAddress::LocalHost, port);
    if (!sock.waitForConnected(500)) return false;

    QByteArray img1(5, 'A'), img2(5, 'B');
    QByteArray pkt = makePacket(img1, img2);
    int half = pkt.size()/2;
    sock.write(pkt.left(half));
    sock.flush();

    // should not emit yet
    QEventLoop loop1; QTimer::singleShot(200, &loop1, &QEventLoop::quit);
    loop1.exec();
    if (called) return false;

    sock.write(pkt.mid(half));
    sock.flush();
    QEventLoop loop2; QTimer::singleShot(300, &loop2, &QEventLoop::quit);
    loop2.exec();
    return called;
}

bool mockimagereciever_test::testReceiveMultipleFrames() {
    MockImageReceiver recv;
    recv.startServer(0);
    int count = 0;
    connect(&recv, &MockImageReceiver::imagesReceived,
            [&](auto, auto, qint64){ ++count; });

    quint16 port = recv.findChild<QTcpServer*>()->serverPort();
    QTcpSocket sock;
    sock.connectToHost(QHostAddress::LocalHost, port);
    if (!sock.waitForConnected(500)) return false;

    QByteArray img1(3, 'X'), img2(4, 'Y');
    QByteArray pkt = makePacket(img1, img2);
    sock.write(pkt + pkt);
    sock.flush();

    QEventLoop loop;
    QTimer::singleShot(300, &loop, &QEventLoop::quit);
    loop.exec();
    return count == 2;
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
