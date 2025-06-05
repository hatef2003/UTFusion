#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include <QtGlobal>
#include <array>
#include <globals.h>
#define MAX_DATA 20
class Buffer : public QObject
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
    explicit Buffer(QObject *parent = nullptr);
    explicit Buffer(int size, QObject *parent = nullptr);
    inline void addRadar(RadarData r);
    inline void addCam(CameraData c);
    inline std::pair<RadarData, CameraData> read();
    inline bool isSync();

signals:
    // Define signals if needed

private:
    int size;
    int headRadar;
    int tailRadar;
    int headCam;
    int tailCam;

    std::array<RadarData, MAX_DATA> m_radarArray;
    std::array<CameraData, MAX_DATA> m_camArray;
};

#endif // BUFFER_H
