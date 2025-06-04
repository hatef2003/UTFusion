#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QObject>

class DataContainer : public QObject
{
    Q_OBJECT
public:
    explicit DataContainer(QObject *parent = nullptr);

signals:
};

#endif // DATACONTAINER_H
