#ifndef DISTANCECALCULATOR_H
#define DISTANCECALCULATOR_H

#include <QObject>
#include <QVector3D>
#include <cmath>

class DistanceCalculator : public QObject
{
    Q_OBJECT
public:
    explicit DistanceCalculator(QObject *parent = nullptr);

    static float distance(const QVector3D& p1, const QVector3D& p2);
    static float distance(float x1, float y1, float z1,
                          float x2, float y2, float z2);
    static float distanceSquared(const QVector3D& p1, const QVector3D& p2);

signals:
    void distanceCalculated(float distance);

public slots:
    void calculateDistance(const QVector3D& p1, const QVector3D& p2);
};

#endif // DISTANCECALCULATOR_H
