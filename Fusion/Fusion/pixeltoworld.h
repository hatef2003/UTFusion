#ifndef PIXELTOWORLD_H
#define PIXELTOWORLD_H

#include <QObject>

class PixelToWorld : public QObject
{
    Q_OBJECT
public:
    explicit PixelToWorld(QObject *parent = nullptr);

signals:
};

#endif // PIXELTOWORLD_H
