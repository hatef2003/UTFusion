#include "buffer.h"

Buffer::Buffer(QObject *parent)
    : QObject{parent}
{}

Buffer::Buffer(int size, QObject *parent)
    : QObject{parent}
{}

void Buffer::addRadar(RadarData r)
{
    int index = tailRadar % size;
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
    int val = m_camArray[tailCam % size].timestamp - m_radarArray[tailRadar % size].timestap;

    return (-TIMESTAMP_MAX_DRIFT < val && val < TIMESTAMP_MAX_DRIFT);
}

std::pair<Buffer::RadarData, Buffer::CameraData> Buffer::read()
{
    if (headRadar == tailRadar || headCam == tailCam)
        throw std::runtime_error("Buffer is empty");

    int indexCam = tailCam % size;
    int indexRadar = tailRadar % size;
    auto cam = m_camArray[indexCam];
    auto rad = m_radarArray[indexRadar];
    return {rad, cam};
}
