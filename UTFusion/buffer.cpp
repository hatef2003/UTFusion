#include "buffer.h"

buffer::buffer(QObject *parent)
    : QObject{parent}
{}

buffer::buffer(int size, QObject *parent)
    : QObject{parent}
{}

void buffer::addData(RadarData r, CameraData c)
{
    int index = tail % size;
    m_camArray[index] = c;
    m_radarArray[index] = r;
    tail++;
    if (tail - head > size)
        head++;
}

std::pair<buffer::RadarData, buffer::CameraData> buffer::read()
{
    if (head == tail) {
        throw std::runtime_error("Buffer is empty");
    }

    int index = tail % size;
    RadarData radar = m_radarArray[index];
    CameraData camera = m_camArray[index];

    tail--; // move to next element

    return {radar, camera};
}
