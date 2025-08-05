#ifndef FUSION_TEST_SUIT_H
#define FUSION_TEST_SUIT_H

#include "FusionUtils/pixel2world.h"
#include "FusionUtils/distance_calculator.h"
#include "FusionUtils/fusion.h"
#include "testsuit.h"

class FusionTestSuit : TestSuit
{
    Fusion* fusion;
    Fusion::ObjectVector objects;
public:
    FusionTestSuit();
    void setup();
    void test_perform_fusion();

    void run_suit();
};

#endif // FUSION_TEST_SUIT_H
