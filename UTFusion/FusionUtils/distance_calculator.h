#ifndef DISTANCECALCULATOR_H
#define DISTANCECALCULATOR_H


class DistanceCalculator
{
public:
    static float distance(float p1[3], float p2[3]);
    static float distance(float x1, float y1, float z1,
                          float x2, float y2, float z2);
    static float distanceSquared(float p1[3], float p2[3]);
    
    static float calculateDistance(float p1[3], float p2[3]);
};

#endif 
