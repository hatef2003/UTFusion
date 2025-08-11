#include "erfanmocker_test.h"

// tests/erfanmocker_test.cpp
#include <QCoreApplication>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QElapsedTimer>
#include <QThread>
#include <iostream>
#include "erfanmocker_test.h"

#include <QCoreApplication>
#include <QTcpSocket>
#include <QTcpServer>
#include <QJsonDocument>
#include <QJsonArray>
#include <QElapsedTimer>
#include <QThread>
#include <iostream>

int erfanmocker_test::run() {
    int fails = 0;
    std::cout << "=== ErfanMockerTest (simple) ===" << std::endl;
    if (!test_singleValidMessage())    { std::cout << "[FAIL] singleValidMessage\n";    fails++; } else std::cout << "[PASS] singleValidMessage" << std::endl;
    if (!test_missingTimestamp())      { std::cout << "[FAIL] missingTimestamp\n";      fails++; } else std::cout << "[PASS] missingTimestamp" << std::endl;
    if (!test_emptyPixelsAllowed())    { std::cout << "[FAIL] emptyPixelsAllowed\n";    fails++; } else std::cout << "[PASS] emptyPixelsAllowed" << std::endl;
    std::cout << "=== Done. Failures: " << fails << " ===" << std::endl;
    return fails;
}

quint16 erfanmocker_test::freePort() {
    QTcpServer probe;
    if (!probe.listen(QHostAddress::LocalHost, 0)) return 0;
    return probe.serverPort();
}

void erfanmocker_test::sendJson(quint16 port, const QJsonObject& obj) {
    QTcpSocket sock;
    sock.connectToHost(QHostAddress::LocalHost, port);
    if (!sock.waitForConnected(1000)) {
        std::cout << "could not connect to port " << port << std::endl;
        return;
    }
    sock.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
    sock.flush();
    sock.waitForBytesWritten(500);
    sock.disconnectFromHost();
    sock.close();
}

bool erfanmocker_test::waitFor(std::function<bool()> pred, int ms) {
    QElapsedTimer t;
    t.start();
    while (t.elapsed() < ms) {
        if (pred()) return true;
        QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
        QThread::msleep(10);
    }
    return pred();
}

bool erfanmocker_test::test_singleValidMessage() {
    quint16 port = freePort();
    if (port == 0) return false;

    ErfanMocker uut;
    bool got = false;
    std::vector<std::vector<Fusion::PixelData>> gotValues;
    Buffer::RadarData gotR{};
    QObject::connect(&uut, &ErfanMocker::dataReceived, &uut,
                     [&](const std::vector<std::vector<Fusion::PixelData>>& v, Buffer::RadarData r){
                         got = true; gotValues = v; gotR = r;
                     });
    uut.startServer(port);

    QJsonArray pixels0 = QJsonArray{
        QJsonObject{{"pixel_depth", 1.5}, {"pixel_pos_x", 10.0}, {"pixel_pos_y", 20.0}},
        QJsonObject{{"pixel_depth", 2.0}, {"pixel_pos_x", 11.0}, {"pixel_pos_y", 21.0}}
    };
    QJsonArray pixels1 = QJsonArray{
        QJsonObject{{"pixel_depth", 3.0}, {"pixel_pos_x", 12.0}, {"pixel_pos_y", 22.0}}
    };
    QJsonArray values = QJsonArray{
        QJsonObject{{"pixels", pixels0}},
        QJsonObject{{"pixels", pixels1}}
    };
    QJsonObject obj;
    obj["values"]    = values;
    obj["radarData"] = QJsonArray{1,2,3,4,5,6};
    obj["timestamp"] = 111;

    sendJson(port, obj);
    if (!waitFor([&]{ return got; })) return false;

    if (gotValues.size() != 2) return false;
    if (gotValues[0].size() != 2) return false;
    if (gotValues[1].size() != 1) return false;
    if (gotR.a != 1 || gotR.b != 2 || gotR.c != 3 || gotR.d != 4 || gotR.e != 5 || gotR.f != 6) return false;
    if (gotR.timestamp != 111) return false;
    return true;
}

bool erfanmocker_test::test_missingTimestamp() {
    quint16 port = freePort();
    if (port == 0) return false;

    ErfanMocker uut;
    bool got = false;
    Buffer::RadarData gotR{};
    QObject::connect(&uut, &ErfanMocker::dataReceived, &uut,
                     [&](const std::vector<std::vector<Fusion::PixelData>>&, Buffer::RadarData r){
                         got = true; gotR = r;
                     });
    uut.startServer(port);

    QJsonArray values = QJsonArray{ QJsonObject{{"pixels", QJsonArray{}}} };
    QJsonObject obj;
    obj["values"]    = values;
    obj["radarData"] = QJsonArray{10,20,30,40,50,60};

    sendJson(port, obj);
    if (!waitFor([&]{ return got; })) return false;

    if (gotR.timestamp != 0) return false;
    if (gotR.a != 10 || gotR.f != 60) return false;
    return true;
}

bool erfanmocker_test::test_emptyPixelsAllowed() {
    quint16 port = freePort();
    if (port == 0) return false;

    ErfanMocker uut;
    bool got = false;
    std::vector<std::vector<Fusion::PixelData>> gotValues;
    QObject::connect(&uut, &ErfanMocker::dataReceived, &uut,
                     [&](const std::vector<std::vector<Fusion::PixelData>>& v, Buffer::RadarData){
                         got = true; gotValues = v;
                     });
    uut.startServer(port);

    QJsonObject obj;
    obj["values"]    = QJsonArray{ QJsonObject{{"pixels", QJsonArray{}}} };
    obj["radarData"] = QJsonArray{0,0,0,0,0,0};
    obj["timestamp"] = 42;

    sendJson(port, obj);
    if (!waitFor([&]{ return got; })) return false;

    if (gotValues.size() != 1) return false;
    if (gotValues[0].size() != 0) return false;
    return true;
}
