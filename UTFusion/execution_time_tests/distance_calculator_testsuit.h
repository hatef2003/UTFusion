#ifndef DISTANCE_CALCULATOR_TESTSUIT_H
#define DISTANCE_CALCULATOR_TESTSUIT_H

#include "testsuit.h"
#include "FusionUtils/distance_calculator.h"

class distanceCalculatorTestsuit:TestSuit
{
    float p1[3], p2[3];
    DistanceCalculator calc;
public:
    distanceCalculatorTestsuit();
    void setup();
    void test_distance_num();
    void test_distance_arr();
    void test_distance_squared();
    void test_calculate_distance();

    QStringList run_suit();
};

#endif 
