#include "fusion.h"

Fusion::Fusion(QObject *parent)
    : QObject{parent}
{}

void Fusion::fuse(void *radarData, void *camData)
{
    char *result;
    // TODO Fusino
    m_outputDevice->write(result);
}
