#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include <QtGlobal>
#include <array>
#define MAX_DATA 20
class buffer : public QObject
{
    Q_OBJECT
public:
    struct RadarData
    {
        int a;
        int b;
        int c;
        int d;
        int e;
        int f;
        qint64 timestap;
    };
    struct CameraData
    {
        QImage *image1;
        QImage *image2;
        qint64 timestamp;
    };
    explicit buffer(QObject *parent = nullptr);
    explicit buffer(int size, QObject *parent = nullptr);
    inline void addData(RadarData r, CameraData c);

signals:
    // Define signals if needed

private:
    int size;
    int head;
    int tail;

    std::array<RadarData, MAX_DATA> m_radarArray;
    std::array<CameraData, MAX_DATA> m_camArray;
};

#endif // BUFFER_H
