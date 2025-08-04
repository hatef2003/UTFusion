#include "testsforutfusion.h"


#include <QCoreApplication>
#include <QTcpServer>
#include <QImage>
#include <QObject>
#include <iostream>

#include "globals.h"
#include "buffer.h"
#include "datacontainer.h"
#include "MockImageReceiver.h"
#include "MockRadarData.h"
#include "erfanmocker.h"
#include "fuse.h"

#define TEST(name, expr) \
std::cout << (name) << ": " << ((expr) ? "PASS" : "FAIL") << std::endl;

void utFusionTests() {



    // std::cout << "All simple tests done." << std::endl;
}
