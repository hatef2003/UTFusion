#ifndef FUSION_H
#define FUSION_H

#include <QObject>

class Fusion : public QObject
{
    Q_OBJECT
public:
    explicit Fusion(QObject *parent = nullptr);

signals:
};

#endif // FUSION_H
