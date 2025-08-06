#include "mockimagereciever_test.h"
#include <iostream>
#include <QCoreApplication>
#include <QEventLoop>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include "mockimagereceiver.h"

void mockimagereciever_test::run_all_mockimagereciever_tests() {
     std::cout << "============ mockimagereciever_tests: ============" << std::endl;
    struct Test { const char* name; bool (mockimagereciever_test::*fn)(); };
    // Test tests[] = {
    //     {"testSingleFrame",    &mockimagereciever_test::testSingleFrame},
    //     {"testFragmentedFrame",&mockimagereciever_test::testFragmentedFrame},
    //     {"testMultipleFrames", &mockimagereciever_test::testMultipleFrames},
    //     {"testInvalidFrameSize",&mockimagereciever_test::testInvalidFrameSize}
    // };

    // int passed = 0, total = sizeof(tests)/sizeof(Test);
    // for (auto &t : tests) {
    //     bool ok = (this->*t.fn)();
    //     std::cout << t.name << ": " << (ok ? "PASS" : "FAIL") << "\n";
    //     if (ok) ++passed;
    // }
    // std::cout << "\nSummary: Passed " << passed << " of " << total << " tests\n";
}
