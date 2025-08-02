#include "fuse.h"

Fuse::Fuse(QObject *parent)
    : QObject{parent}
{
    mu = new QMutex();
    m_fusion = new Fusion();
}

void Fuse::dataRecieve(const std::vector<std::vector<Fusion::PixelData> > &values,
                       Buffer::RadarData r)
{
    mu->lock();
    // TODO Hashem
    // m_fusion->setRadars();
    std::vector<Fusion::FusionOutput> result;
    // m_fusion->performFusion()
    mu->unlock();
    m_queue.enqueue(result);
    emit OperationDone();
}
