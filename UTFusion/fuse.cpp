#include "fuse.h"

Fuse::Fuse(QObject *parent)
    : QObject{parent}
{
    mu = new QMutex();
    m_fusion = new Fusion();
    // m_fusion->setCameraPose();
    for (int i = 0; i < 6; ++i) {
        m_radars.append(Fusion::RadarData((-2.5 + i) * RADARS_DISTANCE, 0, 0 ,-1));
    }

}

void Fuse::unsafeSetRadars(Buffer::RadarData r)
{
    m_radars[0] = r.a;
    m_radars[1] = r.b;
    m_radars[2] = r.c;
    m_radars[3] = r.d;
    m_radars[4] = r.e;
    m_radars[5] = r.f;
}

void Fuse::dataRecieve(const std::vector<std::vector<Fusion::PixelData> > &values,
                       Buffer::RadarData r)
{
    mu->lock();
    // TODO Hashem
    unsafeSetRadars(r);
    m_fusion->setRadars(m_radars);
    std::vector<Fusion::FusionOutput> result;
    // m_fusion->performFusion()
    mu->unlock();
    m_queue.enqueue(result);
    emit OperationDone();
}
