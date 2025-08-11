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
    int run();

private:
    static quint16 freePort();
    static void sendJson(quint16 port, const QJsonObject& obj);
    static bool waitFor(std::function<bool()> pred, int ms = 1500);
    bool test_singleMessage();
    bool test_missingTimestamp();
};


#endif // MOCKRADARDATA_TEST_H
