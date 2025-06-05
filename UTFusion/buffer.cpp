#include "buffer.h"
#include "qdebug.h"

Buffer::Buffer(QObject *parent)
    : QObject{parent}
{
    size = 6;
}

Buffer::Buffer(int size, QObject *parent)
    : QObject{parent}
{
    headCam = 0;
    headRadar = 0;
    tailCam = 0;
    tailRadar = 0;
    this->size = size;
}

void Buffer::addRadar(RadarData r)
{
    int index = tailRadar % size;
    qDebug() << index;
    tailRadar++;
    m_radarArray[index] = r;
    headRadar += (tailRadar - headRadar > size);
}

void Buffer::addCam(CameraData c)
{
    int index = tailCam % size;
    m_camArray[index] = c;
    tailCam++;
    headCam += (tailCam - headCam > size);
}

bool Buffer::isSync()
{
    int val = m_camArray[(tailCam - 1) % size].timestamp
              - m_radarArray[(tailRadar - 1) % size].timestap;
    qDebug() << val << (tailCam - 1) % size << (tailRadar - 1) % size << size;
    return (-TIMESTAMP_MAX_DRIFT < val && val < TIMESTAMP_MAX_DRIFT);
}

std::pair<Buffer::RadarData, Buffer::CameraData> Buffer::read()
{
    if (headRadar == tailRadar || headCam == tailCam)
        throw std::runtime_error("Buffer is empty");
    tailCam--;
    tailRadar--;
    int indexCam = (tailCam) % size;
    int indexRadar = tailRadar % size;
    auto cam = m_camArray[indexCam];
    auto rad = m_radarArray[indexRadar];
    return {rad, cam};
}
