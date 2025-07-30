#include "distancecalculator.h"
#include <QDebug>

DistanceCalculator::DistanceCalculator(QObject *parent)
    : QObject{parent}
{}

float DistanceCalculator::distance(const QVector3D& p1, const QVector3D& p2)
{
    QVector3D diff = p2 - p1;

    return diff.length();
}

float DistanceCalculator::distance(float x1, float y1, float z1,
                                   float x2, float y2, float z2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dz = z2 - z1;

    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

float DistanceCalculator::distanceSquared(const QVector3D& p1, const QVector3D& p2)
{
    QVector3D diff = p2 - p1;

    return diff.lengthSquared();
}

void DistanceCalculator::calculateDistance(const QVector3D& p1, const QVector3D& p2)
{
    float dist = distance(p1, p2);
    emit distanceCalculated(dist);

    qDebug() << "Distance calculated:" << dist;
}
