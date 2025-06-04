#include "buffer.h"

buffer::buffer(QObject *parent)
    : QObject{parent}
{}

buffer::buffer(int size, QObject *parent)
    : QObject{parent}
{}

void buffer::addRadar(RadarData r)
{
    int index = tailRadar % size;
    tailRadar++;
    m_radarArray[index] = r;
    headRadar += (tailRadar - headRadar > size);
}

void buffer::addCam(CameraData c)
{
    int index = tailCam % size;
    m_camArray[index] = c;
    tailCam++;
    headCam += (tailCam - headCam > size);
}

std::pair<buffer::RadarData, buffer::CameraData> buffer::read()
{
    if (headRadar == tailRadar || headCam == tailCam)
        throw std::runtime_error("Buffer is empty");

    int indexCam = tailCam % size;
    int indexRadar = tailRadar % size;
    auto cam = m_camArray[indexCam];
    auto rad = m_radarArray[indexRadar];
    return {rad, cam};
}
