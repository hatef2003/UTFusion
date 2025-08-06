#include "accuracy_tests/datacontainer_tests.h"
#include "datacontainer.h"   // DataContainer declaration :contentReference[oaicite:2]{index=2}
#include "buffer.h"          // Buffer::RadarData, CameraData :contentReference[oaicite:3]{index=3}
#include "globals.h"         // TIMESTAMP_MAX_DRIFT
#include <iostream>
#include <stdexcept>

void datacontainer_tests::run_all_datacontainer_tests() {
    std::cout << " " << std::endl;
    std::cout << "======== DataContainer Tests ========"<< std::endl;
    struct Test { const char* name; bool (datacontainer_tests::*fn)(); };
    Test tests[] = {
        {"testGetDataBeforeAny",     &datacontainer_tests::testGetDataBeforeAny},
        {"testSyncAfterRadarThenCam",&datacontainer_tests::testSyncAfterRadarThenCam},
        {"testSyncAfterCamThenRadar",&datacontainer_tests::testSyncAfterCamThenRadar}
    };
    int passed = 0;
    int total  = sizeof(tests)/sizeof(tests[0]);
    for (auto &t : tests) {
        bool ok = (this->*t.fn)();
        std::cout << t.name << ": " << (ok ? "PASS" : "FAIL") << std::endl;
        if (ok) ++passed;
    }
    std::cout << " " << std::endl;
    std::cout << "Summary: Passed " << passed << " of " << total << " tests" << std::endl;
}


bool datacontainer_tests::testGetDataBeforeAny() {
    DataContainer dc;
    try {
        dc.getData();
    } catch (const std::runtime_error&) {
        return true;    // expected: no data available
    }
    return false;       // no exception ⇒ fail
}

bool datacontainer_tests::testSyncAfterRadarThenCam() {
    DataContainer dc;
    // Create radar and camera data within drift
    Buffer::RadarData  r{1000, 1,2,3,4,5,6};
    Buffer::CameraData c{nullptr, nullptr, 1000 + (TIMESTAMP_MAX_DRIFT/2)};
    dc.newRadarData(r);
    dc.newCamData(c);

    try {
        auto pr = dc.getData();
        return pr.first.timestamp  == r.timestamp
               && pr.second.timestamp == c.timestamp;
    } catch (...) {
        return false;
    }
}

bool datacontainer_tests::testSyncAfterCamThenRadar() {
    DataContainer dc;
    Buffer::CameraData c{nullptr, nullptr, 2000};
    Buffer::RadarData  r{2000 + (TIMESTAMP_MAX_DRIFT/2), 9,8,7,6,5,4};
    dc.newCamData(c);
    dc.newRadarData(r);

    try {
        auto pr = dc.getData();
        return pr.first.timestamp  == r.timestamp
               && pr.second.timestamp == c.timestamp;
    } catch (...) {
        return false;
    }
}
