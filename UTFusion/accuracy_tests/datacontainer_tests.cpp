#include "accuracy_tests/datacontainer_tests.h"
#include "datacontainer.h"   // DataContainer declaration :contentReference[oaicite:2]{index=2}
#include "buffer.h"          // Buffer::RadarData, CameraData :contentReference[oaicite:3]{index=3}
#include "globals.h"         // TIMESTAMP_MAX_DRIFT
#include <iostream>
#include <stdexcept>

void datacontainer_tests::run_all_datacontainer_tests() {
    std::cout << "===== DataContainer Tests ====="<< std::endl;
    struct Test { const char* name; bool (datacontainer_tests::*fn)(); };
    // Test tests[] = {
    //     {"testGetDataBeforeAny",     &DataContainerTest::testGetDataBeforeAny},
    //     {"testSyncAfterRadarThenCam",&DataContainerTest::testSyncAfterRadarThenCam},
    //     {"testSyncAfterCamThenRadar",&DataContainerTest::testSyncAfterCamThenRadar}
    // };
    // int passed = 0;
    // int total  = sizeof(tests)/sizeof(tests[0]);
    // for (auto &t : tests) {
    //     bool ok = (this->*t.fn)();
    //     std::cout << t.name << ": " << (ok ? "PASS" : "FAIL") << "\n";
    //     if (ok) ++passed;
    // }
    //std::cout << "Summary: Passed " << passed << " of " << total << " tests\n";
}
