#include "datacontainer.h"

DataContainer::DataContainer(QObject *parent)
    : QObject{parent}
{
    //TODO ..
    mu = new QMutex();
    m_readIndex&=0;
    m_buffers[0] = std::make_unique<Buffer>();
    m_buffers[1] = std::make_unique<Buffer>();
}

void DataContainer::newCamData(Buffer::CameraData c)
{
    c.timestamp = QDateTime::currentMSecsSinceEpoch();
    int writeIndex = m_readIndex ^ 1;
    m_buffers[writeIndex]->addCam(c);
    if (m_buffers[writeIndex]->isSync()) {
        mu->lock();
        m_readIndex = writeIndex;
        mu->unlock();
    }
}

void DataContainer::newRadarData(Buffer::RadarData r)
{
    r.timestap = QDateTime::currentMSecsSinceEpoch();
    int writeIndex = m_readIndex ^ 1;
    m_buffers[writeIndex]->addRadar(r);
    if (m_buffers[writeIndex]->isSync()) {
        mu->lock();
        m_readIndex = writeIndex;
        mu->unlock();
    }
}

std::pair<Buffer::RadarData, Buffer::CameraData> DataContainer::getData()
{
    mu->lock();
    auto data = m_buffers[m_readIndex]->read();
    mu->unlock();
    return data;
}
