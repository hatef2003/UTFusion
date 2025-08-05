#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include <QtGlobal>
#include <array>
#include <globals.h>
#define MAX_DATA 20
#define RADAR_SIZE 6 // max 16

class Buffer
{
public:
    struct RadarData
    {
        qint64 timestamp;
        int a;
        int b;
        int c;
        int d;
        int e;
        int f;
    };
    struct CameraData
    {
        QImage *image1;
        QImage *image2;
        qint64 timestamp;
    };
    explicit Buffer();
    void addRadar(RadarData r);
    void addCam(CameraData c);
    std::pair<RadarData, CameraData> read();
    bool isSync();
private:
    struct {
        unsigned int headRadar:4;
        unsigned int tailRadar:4;
        unsigned int headCam:4;
        unsigned int tailCam:4;
    } buffUtils;

    std::array<RadarData, MAX_DATA> m_radarArray;
    std::array<CameraData, MAX_DATA> m_camArray;
};

#endif // BUFFER_H
