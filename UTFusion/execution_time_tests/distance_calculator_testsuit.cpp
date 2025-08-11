#include "distance_calculator_testsuit.h"
#include <iostream>

distanceCalculatorTestsuit::distanceCalculatorTestsuit() {}

void distanceCalculatorTestsuit::setup()
{
    this->p1[0] = 0.12f, this->p1[1] = 102.492f, this->p1[2] = 983.92f;
    this->p2[0] = 1232.23f, this->p2[1] = 123.12f, this->p2[2] = 123.12f;
}

void distanceCalculatorTestsuit::test_distance_num()
{
    this->calc.distance(this->p1[0],this->p1[1],this->p1[2],
             this->p2[0],this->p2[1],this->p2[2]);
}

void distanceCalculatorTestsuit::test_distance_arr()
{
    this->calc.distance(this->p1, this->p2);
}

void distanceCalculatorTestsuit::test_distance_squared()
{
    this->calc.distanceSquared(this->p1, this->p2);
}

void distanceCalculatorTestsuit::test_calculate_distance()
{
    this->calc.calculateDistance(this->p1, this->p2);
}

QStringList distanceCalculatorTestsuit::run_suit()
{
    QStringList results;

    results << "DistanceCalculatorTestSuit:";
    this->setup();

    results << benchmark("distanceNum", [this]() {
        this->test_distance_num();
    }, 5);
    results << benchmark("distanceArr", [this]() {
        this->test_distance_arr();
    }, 5);
    results << benchmark("distanceSquared", [this]() {
        this->test_distance_squared();
    }, 5);

    results << benchmark("calculatedDistance", [this]() {
        this->test_calculate_distance();
    }, 5);

    for (const QString& line : results) {
        std::cout << line.toStdString() << std::endl;
    }

    return results;
}
