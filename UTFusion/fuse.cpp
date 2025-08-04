#include "fuse.h"

Fuse::Fuse(QObject *parent)
    : QObject{parent}
{
    mu = new QMutex();
    m_fusion = new Fusion();
    float camera_position[3] = {5.0f, 10.0f, -10.0f};
    float camera_rotation[3] = {0.0f, 0.0f, 0.0f};
    PixelToWorld::CameraPose pose(camera_position, camera_rotation);
    m_fusion->setCameraPose(pose);
    m_radars.resize(6);
    for (int i = 0; i < 6; ++i) {
        m_radars[i] = Fusion::RadarData((-2.5 + i) * RADARS_DISTANCE, 0, 0, -1);
    }

}

void Fuse::unsafeSetRadars(Buffer::RadarData r)
{
    m_radars[0].output_distance = r.a;
    m_radars[1].output_distance = r.b;
    m_radars[2].output_distance = r.c;
    m_radars[3].output_distance = r.d;
    m_radars[4].output_distance = r.e;
    m_radars[5].output_distance = r.f;
}

void Fuse::dataRecieve(const std::vector<std::vector<Fusion::PixelData> > &values,
                       Buffer::RadarData r)
{
    mu->lock();
    // TODO Hashem
    unsafeSetRadars(r);
    m_fusion->setRadars(m_radars);
    std::vector<Fusion::FusionOutput> result;
    result = m_fusion->performFusion(values);
    mu->unlock();
    m_queue.enqueue(result);
    emit OperationDone();
}
