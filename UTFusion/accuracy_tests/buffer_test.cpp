
// buffer_test.cpp
#include <iostream>
#include <stdexcept>
#include "buffer_test.h"
#include "buffer.h"
#include "globals.h"

void buffer_test::run_all_buffer_tests() {
    struct Test { const char* name; bool (buffer_test::*fn)(); };
    Test tests[] = {
         {"testEmptyReadThrows",     &buffer_test::testEmptyReadThrows},
        // {"testAddAndReadSync",      &buffer_test::testAddAndReadSync},
        // {"testNotSyncBeyondDrift",  &buffer_test::testNotSyncBeyondDrift},
        // {"testOverflowKeepsLatest", &buffer_test::testOverflowKeepsLatest}
    };

    int passed = 0;
    const int total = sizeof(tests) / sizeof(Test);
    for (int i = 0; i < total; ++i) {
        bool ok = (this->*tests[i].fn)();
        std::cout << tests[i].name << ": "
                  << (ok ? "PASS" : "FAIL") << "\n";
        if (ok) ++passed;
    }
    std::cout << "\nSummary: Passed " << passed
              << " of " << total << " tests\n";
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
