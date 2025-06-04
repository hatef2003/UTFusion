#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include <QtGlobal>
#include <array>
class buffer : public QObject
{
    Q_OBJECT
public:
    explicit buffer(QObject *parent = nullptr);
    explicit buffer(int size, QObject *parent = nullptr);

signals:
    // Define signals if needed

private:
    struct RadarData
    {
        int a;
        int b;
        int c;
        int d;
        int e;
        int f;
        qint64 timestap;
    };
    struct CameraData
    {
        QImage *image1;
        QImage *image2;
        qint64 timestamp;
    };

    int size;
    int head;
    int tail;

    std::array<RadarData, 20> dataArray; // Array of 20 SixIntData structs
};

#endif // BUFFER_H
