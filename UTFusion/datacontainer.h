#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QDateTime>
#include <QMutex>
#include <QObject>
#include <buffer.h>
class DataContainer : public QObject
{
    Q_OBJECT
public:
    explicit DataContainer(QObject *parent = nullptr);
    void newCamData(Buffer::CameraData);
    void newRadarData(Buffer::RadarData);
    std::pair<Buffer::RadarData, Buffer::CameraData> getData();

private:
    std::array<std::unique_ptr<Buffer>, 2> m_buffers;
    int m_readIndex;
    QMutex *mu;
signals:
    void dataSync();
};

#endif // DATACONTAINER_H
