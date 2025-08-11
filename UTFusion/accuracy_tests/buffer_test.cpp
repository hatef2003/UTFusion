
// buffer_test.cpp
#include <iostream>
#include <stdexcept>
#include "buffer_test.h"
#include "buffer.h"
#include "globals.h"

void buffer_test::run_all_buffer_tests() {
    std::cout << " " << std::endl;
    std::cout << "=============== buffer_tests: ===============" << std::endl;
    struct Test { const char* name; bool (buffer_test::*fn)(); };
    Test tests[] = {
         {"testEmptyReadThrows",     &buffer_test::testEmptyReadThrows},
         {"testAddAndReadSync",      &buffer_test::testAddAndReadSync},
         {"testNotSyncBeyondDrift",  &buffer_test::testNotSyncBeyondDrift}
    };

    int passed = 0;
    const int total = sizeof(tests) / sizeof(Test);
    for (int i = 0; i < total; ++i) {
        bool ok = (this->*tests[i].fn)();
        std::cout << tests[i].name << ": "
                  << (ok ? "PASS" : "FAIL") << std::endl;
        if (ok) ++passed;
    }
    std::cout << "\nSummary: Passed " << passed
              << " of " << total << " tests" << std::endl;
}


bool buffer_test::testEmptyReadThrows() {
    Buffer buf;
    try {
        buf.read();
    } catch (const std::runtime_error&) {
        return true;   // expected
    }
    return false;      // no exception
}


bool buffer_test::testAddAndReadSync() {
    Buffer buf;
    Buffer::RadarData  r{1000,1,2,3,4,5,6};
    Buffer::CameraData c{nullptr,nullptr,1000 + (TIMESTAMP_MAX_DRIFT/2)};
    buf.addRadar(r);
    buf.addCam(c);

    if (!buf.isSync()) return false;

    auto pr = buf.read();
    return pr.first.timestamp == r.timestamp
           && pr.second.timestamp == c.timestamp;
}

bool buffer_test::testNotSyncBeyondDrift() { //check if rdr & cam drift more than TIMESTAMP_MAX_DRIFT
    Buffer buf;
    Buffer::RadarData  r{2000,0,0,0,0,0,0};
    Buffer::CameraData c{nullptr,nullptr,2000 + TIMESTAMP_MAX_DRIFT + 1};
    buf.addRadar(r);
    buf.addCam(c);
    return !buf.isSync();
}

