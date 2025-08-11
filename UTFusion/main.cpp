#include <QCoreApplication>
#include <QImage>
#include "MockImageReceiver.h"
#include "MockRadarData.h"
#include "datacontainer.h"
#include "erfanmocker.h"
#include<fuse.h>
#include <buffer.h>
#include "execution_time_tests/fusion_test_suit.h"
#include "execution_time_tests/distance_calculator_testsuit.h"
#include "execution_time_tests/pixel2worldtestsuit.h"
#include "execution_time_tests/datatestsuit.h"
#include "accuracy_tests/buffer_test.h"
#include <iostream>
#include "accuracy_tests/testsforutfusion.h"
#include "accuracy_tests/mockimagereciever_test.h"
#include "accuracy_tests/datacontainer_tests.h"
#include "accuracy_tests/fuse_test.h"

int main(int argc, char *argv[])
{
     QCoreApplication app(argc, argv);

    FusionTestSuit t_fuse;
    t_fuse.run_suit();
    distanceCalculatorTestsuit t_calc;
    t_calc.run_suit();
    Pixel2WorldTestsuit t_p2w;
    t_p2w.run_suit();
    DataTestsuit t_data;
    t_data.run_suit();
    // // benchmark("dummy test", fusion_test_simple, 5);



    buffer_test buffer_tester;
    buffer_tester.run_all_buffer_tests();

    mockimagereciever_test mockimagereciever_tester;
   // mockimagereciever_tester.run_all_mockimagereciever_tests();

    datacontainer_tests datacontainer_tester;
    datacontainer_tester.run_all_datacontainer_tests();

    fuse_test fuse_tester;
    fuse_tester.run_all_fuse_tests();

    return app.exec();
}

// int main(int argc, char *argv[])
// {
//     QCoreApplication app(argc, argv);

//     //utFusionTests();


//     //std::cout << "hiiiii" << std::endl;

//     // DataContainer dataContainer;
//     // MockRadarData radar;
//     // MockImageReceiver mockImageReceiver;
//     // mockImageReceiver.startServer(8080); // Start server on port 8080
//     // radar.startServer(8000);             // Start server on port 8000
    
//     // QObject::connect(&radar,
//     //                  &MockRadarData::dataReceived,
//     //                  [&dataContainer](const QList<uint> &values, qint64 timestamp) {
//     //                      Buffer::RadarData radarData;
//     //                      radarData.timestamp = timestamp;
//     //                      radarData.a = values[1];
//     //                      radarData.b = values[2];
//     //                      radarData.c = values[3];
//     //                      radarData.d = values[4];
//     //                      radarData.e = values[5];
//     //                      radarData.f = values[6];
//     //                      dataContainer.newRadarData(radarData);
//     //                  });
//     // QObject::connect(&mockImageReceiver,
//     //                  &MockImageReceiver::imagesReceived,
//     //                  [&dataContainer](const QImage &img1, const QImage &img2, qint64 timestamp) {
//     //                      Buffer::CameraData cameraData;
//     //                      cameraData.timestamp = timestamp;
//     //                      cameraData.image1 = const_cast<QImage *>(&img1);
//     //                      cameraData.image2 = const_cast<QImage *>(&img2);
//     //                      dataContainer.newCamData(cameraData);
//     //                  });
//     // ErfanMocker erfanMocker;
//     // erfanMocker.startServer(8001); // Start server on port 8001
//     // Fuse fuse;
//     // QObject::connect(&erfanMocker, &ErfanMocker::dataReceived, &fuse, &Fuse::dataRecieve);

//     return app.exec();
// }
