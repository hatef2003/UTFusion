#include "./FusionUtils/distance_calculator.h"
#include <cmath>

float DistanceCalculator::distance(float p1[3], float p2[3])
{
    return distance(p1[0], p1[1], p1[2], p2[0], p2[1], p2[2]);
}

float DistanceCalculator::distance(float x1, float y1, float z1,
                                   float x2, float y2, float z2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dz = z2 - z1;

    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

float DistanceCalculator::distanceSquared(float p1[3], float p2[3])
{
    
    float dx = p2[0] - p1[0];
    float dy = p2[1] - p1[1];
    float dz = p2[2] - p1[2];

    return dx*dx + dy*dy + dz*dz;
}

float DistanceCalculator::calculateDistance(float p1[3], float p2[3])
{
    return distance(p1, p2);
}
