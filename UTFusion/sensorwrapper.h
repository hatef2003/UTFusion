#ifndef SENSORWRAPPER_H
#define SENSORWRAPPER_H

#include <QObject>

class SensorWrapper : public QObject
{
    Q_OBJECT
public:
    explicit SensorWrapper(QObject *parent = nullptr);

signals:
};

#endif // SENSORWRAPPER_H
