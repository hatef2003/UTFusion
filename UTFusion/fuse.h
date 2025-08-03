#ifndef FUSE_H
#define FUSE_H

#include <QMutex>
#include <QObject>
#include <QQueue>
#include <./FusionUtils/fusion.h>
#include <buffer.h>

#define RADARS_DISTANCE 10.0

class Fuse : public QObject
{
    Q_OBJECT
public:
    explicit Fuse(QObject *parent = nullptr);

private:
    QMutex *mu;
    QQueue<std::vector<Fusion::FusionOutput>> m_queue;
    Fusion *m_fusion;
    std::vector<Fusion::RadarData> m_radars;
    void unsafeSetRadars(Buffer::RadarData r);
signals:
    void OperationDone();
public slots:
    void dataRecieve(const std::vector<std::vector<Fusion::PixelData>> &values, Buffer::RadarData r);
};

#endif // FUSE_H
