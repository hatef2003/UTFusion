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
