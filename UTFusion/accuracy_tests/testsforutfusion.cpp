#include "testsforutfusion.h"


#include <QCoreApplication>
#include <QTcpServer>
#include <QImage>
#include <QObject>
#include <iostream>

#include "globals.h"
#include "buffer.h"
#include "datacontainer.h"
#include "mockimagereceiver.h"
#include "mockradardata.h"
#include "erfanmocker.h"
#include "fuse.h"

#define TEST(name, expr) \
std::cout << (name) << ": " << ((expr) ? "PASS" : "FAIL") << std::endl;

void utFusionTests() {

    std::cout << "--- Application Startup Tests ---" << std::endl;

    {
        DataContainer dc;
        MockRadarData    radar;
        MockImageReceiver imgRec;
        ErfanMocker      erfan;
        Fuse              fuse;

        radar.startServer(8000);
        imgRec.startServer(8080);
        erfan.startServer(8001);

        QTcpServer* rSrv = radar.findChild<QTcpServer*>();
        QTcpServer* iSrv = imgRec.findChild<QTcpServer*>();
        QTcpServer* eSrv = erfan.findChild<QTcpServer*>();

        TEST("App: Radar server listening on 8000", rSrv && rSrv->isListening() && rSrv->serverPort() == 8000);
        TEST("App: ImageReceiver server listening on 8080", iSrv && iSrv->isListening() && iSrv->serverPort() == 8080);
        TEST("App: ErfanMocker server listening on 8001", eSrv && eSrv->isListening() && eSrv->serverPort() == 8001);
    }



    std::cout << "All tests done." << std::endl;
}
