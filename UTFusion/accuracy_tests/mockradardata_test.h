#ifndef MOCKRADARDATA_TEST_H
#define MOCKRADARDATA_TEST_H


#include <QCoreApplication>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include <QThread>

#include "mockradardata.h"


class mockradardata_test {
public:
    int run() {
        int fails = 0;
        std::cout << "=== MockRadarDataTest (simple) ===" << std::endl;
        if (!test_singleMessage())    { std::cout << "[FAIL] singleMessage\n";    fails++; } else std::cout << "[PASS] singleMessage" << std::endl;
        if (!test_missingTimestamp()) { std::cout << "[FAIL] missingTimestamp\n"; fails++; } else std::cout << "[PASS] missingTimestamp" << std::endl;
        std::cout << "=== Done. Failures: " << fails << " ===" << std::endl;
        return fails;
    }

private:
    static quint16 freePort() {
        QTcpServer probe;
        if (!probe.listen(QHostAddress::LocalHost, 0)) return 0;
        return probe.serverPort();
    }

    static void sendJson(quint16 port, const QJsonObject& obj) {
        QTcpSocket sock;
        sock.connectToHost(QHostAddress::LocalHost, port);
        if (!sock.waitForConnected(1000)) {
            std::cout << "could not connect to port " << port  << std::endl;
            return;
        }
        sock.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
        sock.flush();
        sock.waitForBytesWritten(500);
        sock.disconnectFromHost();
        sock.close();
    }

    static bool waitFor(std::function<bool()> pred, int ms = 1500) {
        QElapsedTimer t; t.start();
        while (t.elapsed() < ms) {
            if (pred()) return true;
            QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
            QThread::msleep(10);
        }
        return pred();
    }

    bool test_singleMessage() {
        quint16 port = freePort();
        if (port == 0) return false;

        MockRadarData uut;
        QList<uint> gotValues; qint64 gotTs = -1; bool got = false;
        QObject::connect(&uut, &MockRadarData::dataReceived, &uut,
                         [&](const QList<uint>& v, qint64 ts){ gotValues=v; gotTs=ts; got=true; });
        uut.startServer(port);


        QJsonObject obj; obj["values"] = QJsonArray{0,1,2,3,4,5,6}; obj["timestamp"] = 123456789;
        sendJson(port, obj);

        if (!waitFor([&]{ return got; })) return false;
        if (gotValues.size()!=7) return false;
        if (gotValues[2] != 2u)  return false;
        if (gotTs != 123456789)  return false;
        return true;
    }

    bool test_missingTimestamp() {
        quint16 port = freePort();
        if (port == 0) return false;

        MockRadarData uut;
        QList<uint> gotValues; qint64 gotTs = -1; bool got = false;
        QObject::connect(&uut, &MockRadarData::dataReceived, &uut,
                         [&](const QList<uint>& v, qint64 ts){ gotValues=v; gotTs=ts; got=true; });
        uut.startServer(port);


        QJsonObject obj; obj["values"] = QJsonArray{5,6};
        sendJson(port, obj);

        if (!waitFor([&]{ return got; })) return false;
        if (gotValues.size()!=2) return false;
        if (gotValues[0]!=5u || gotValues[1]!=6u) return false;
        if (gotTs != 0) return false;
        return true;
    }
};


#endif // MOCKRADARDATA_TEST_H
