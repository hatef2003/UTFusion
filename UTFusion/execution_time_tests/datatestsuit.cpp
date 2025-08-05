#include "datatestsuit.h"
#include <QImage>

DataTestsuit::DataTestsuit() {}

void DataTestsuit::setup()
{
    QImage img1(640, 480, QImage::Format_RGB32);
    img1.fill(Qt::white);
    QImage img2(640, 480, QImage::Format_RGB32);
    img2.fill(Qt::white);

    this->buf.addRadar({2100, 1, 2, 3, 4, 5, 6});
    this->buf.addCam({&img1, &img2, 2000});
}

void DataTestsuit::test_buffer_isValid()
{
    this->buf.isSync();
}

QStringList DataTestsuit::run_suit()
{
    QStringList results;

    results << "DataTestSuit:";
    results << benchmark("setup", [this]() {
        this->setup();
    }, 1);

    results << benchmark("buffer_isValid", [this]() {
        this->test_buffer_isValid();
    }, 5);

    for (const QString& line : results) {
        qDebug() << line;
    }

    return results;
}
