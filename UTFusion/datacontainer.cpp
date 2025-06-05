#include "datacontainer.h"

DataContainer::DataContainer(QObject *parent)
    : QObject{parent}
{}

void DataContainer::newCamData(Buffer::CameraData c)
{
    c.timestamp = QDateTime::currentMSecsSinceEpoch();
    int writeIndex = m_readIndex ^ 1;
    m_buffers[writeIndex].addCam(c);
    if (m_buffers[writeIndex].isSync()) {
        //TODO swap;
    }
}

void DataContainer::newRadarData(Buffer::RadarData r)
{
    r.timestap = QDateTime::currentMSecsSinceEpoch();
    int writeIndex = m_readIndex ^ 1;
    m_buffers[writeIndex].addRadar(r);
    if (m_buffers[writeIndex].isSync()) {
        // TODO DO SWAP
    }
}
