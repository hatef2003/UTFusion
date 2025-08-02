#ifndef LASERSENSOR_VL531X_H
#define LASERSENSOR_VL531X_H


#include <QObject>
#include <QTimer>
#include <QDateTime>
#include "buffer.h"

class Lasersensor_VL531X : public QObject
{
    Q_OBJECT
public:
    explicit Lasersensor_VL531X(QObject* parent = nullptr);

    void start(int intervalMs = 50); // Polling interval

signals:
    void dataReceived(Buffer::RadarData data);

private slots:
    void readSensor();

private:
    QTimer timer;
    // VL53L1_Dev_t dev; // example if using ST driver
};

#endif

