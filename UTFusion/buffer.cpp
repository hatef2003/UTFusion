#include "buffer.h"
#include "qdebug.h"

Buffer::Buffer()
{
    this->buffUtils.headCam = 0x0;
    this->buffUtils.headRadar = 0x0;
    this->buffUtils.tailCam = 0x0;
    this->buffUtils.tailRadar = 0x0;
}

void Buffer::addRadar(RadarData r)
{
    int index = this->buffUtils.tailRadar % SIZE;
    qDebug() << index;
    this->buffUtils.tailRadar++;
    m_radarArray[index] = r;
    this->buffUtils.headRadar += (this->buffUtils.tailRadar - this->buffUtils.headRadar > SIZE);
}

void Buffer::addCam(CameraData c)
{
    int index = this->buffUtils.tailCam % SIZE;
    m_camArray[index] = c;
    this->buffUtils.tailCam++;
    this->buffUtils.headCam += (this->buffUtils.tailCam - this->buffUtils.headCam > SIZE);
}

bool Buffer::isSync()
{
    int val = m_camArray[(this->buffUtils.tailCam - 1) % SIZE].timestamp
              - m_radarArray[(this->buffUtils.tailRadar - 1) % SIZE].timestap;
    qDebug() << val << (this->buffUtils.tailCam - 1) % SIZE << (this->buffUtils.tailRadar - 1) % SIZE << SIZE;
    return (-TIMESTAMP_MAX_DRIFT < val && val < TIMESTAMP_MAX_DRIFT);
}

std::pair<Buffer::RadarData, Buffer::CameraData> Buffer::read()
{
    if (this->buffUtils.headRadar == this->buffUtils.tailRadar || this->buffUtils.headCam == this->buffUtils.tailCam)
        throw std::runtime_error("Buffer is empty");
    this->buffUtils.tailCam--;
    this->buffUtils.tailRadar--;
    int indexCam = (this->buffUtils.tailCam) % SIZE;
    int indexRadar = this->buffUtils.tailRadar % SIZE;
    auto cam = m_camArray[indexCam];
    auto rad = m_radarArray[indexRadar];
    return {rad, cam};
}
