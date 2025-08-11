#ifndef ERFANMOCKER_TEST_H
#define ERFANMOCKER_TEST_H

#include <vector>
#include <functional>
#include <QJsonObject>
#include <QHostAddress>
#include <QObject>

#include "erfanmocker.h"   

class erfanmocker_test {
public:
    int run();

private:
    static quint16 freePort();
    static void sendJson(quint16 port, const QJsonObject& obj);
    static bool waitFor(std::function<bool()> pred, int ms = 1500);

    bool test_singleValidMessage();
    bool test_missingTimestamp();
    bool test_emptyPixelsAllowed();
};




#endif // ERFANMOCKER_TEST_H

