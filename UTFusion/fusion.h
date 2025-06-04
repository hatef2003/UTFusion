#ifndef FUSION_H
#define FUSION_H

#include <QIODevice>
#include <QObject>

class Fusion : public QObject
{
    Q_OBJECT
public:
    explicit Fusion(QObject *parent = nullptr);
public slots:
    void fuse(void *radarData, void *camData);
signals:
    void DataReady();

private:
    QIODevice *m_outputDevice;
};

#endif // FUSION_H
