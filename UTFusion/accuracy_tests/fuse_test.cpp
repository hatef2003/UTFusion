#include "fuse_test.h"
#include "fuse.h"      // Fuse declaration :contentReference[oaicite:5]{index=5}
#include "buffer.h"    // Buffer::RadarData :contentReference[oaicite:6]{index=6}
#include <QObject>
#include <iostream>
#include <vector>


void fuse_test::run_all_fuse_tests() {
    std::cout << " " << std::endl;
    std::cout << "======== Fuse Tests ========" << std::endl;
    struct Test { const char* name; bool (fuse_test::*fn)(); };
    Test tests[] = {
        {"testOperationDoneOnce",  &fuse_test::testOperationDoneOnce},
        {"testOperationDoneTwice", &fuse_test::testOperationDoneTwice}
    };
    int passed = 0, total = sizeof(tests)/sizeof(tests[0]);
    for (auto &t : tests) {
        bool ok = (this->*t.fn)();
        std::cout << t.name << ": " << (ok ? "PASS" : "FAIL")  << std::endl;
        if (ok) ++passed;
    }

    std::cout << " " << std::endl;
    std::cout << "Summary: Passed " << passed << " of " << total << " tests" << std::endl;
}

bool fuse_test::testOperationDoneOnce() {
    Fuse fuse;
    int count = 0;
    // Connect OperationDone to lambda that increments count
    QObject::connect(&fuse, &Fuse::OperationDone,
                     [&](){ ++count; });

    // Prepare dummy inputs
    std::vector<std::vector<Fusion::PixelData>> values; // empty is fine
    Buffer::RadarData r{0,1,2,3,4,5,6};

    // Call the slot
    fuse.dataRecieve(values, r);  // emits OperationDone once :contentReference[oaicite:7]{index=7}

    return count == 1;
}

bool fuse_test::testOperationDoneTwice() {
    Fuse fuse;
    int count = 0;
    QObject::connect(&fuse, &Fuse::OperationDone,
                     [&](){ ++count; });

    std::vector<std::vector<Fusion::PixelData>> values;
    Buffer::RadarData r{0,10,20,30,40,50,60};

    // Two calls ⇒ two emits :contentReference[oaicite:8]{index=8}
    fuse.dataRecieve(values, r);
    fuse.dataRecieve(values, r);

    return count == 2;
}
