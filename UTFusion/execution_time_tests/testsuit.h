#ifndef TESTSUIT_H
#define TESTSUIT_H

#include "test-benchmark.h"

class TestSuit
{
public:
    TestSuit();
    virtual void run_suit() = 0;
    virtual void setup() = 0;

};

#endif // TESTSUIT_H
