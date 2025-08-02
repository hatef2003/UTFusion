#ifndef erfanmocker_H
#define erfanmocker_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <./FusionUtils/fusion.h>
#include <buffer.h>
class ErfanMocker : public QObject
{
    Q_OBJECT
public:
    explicit ErfanMocker(QObject *parent = nullptr);

    void startServer(quint16 port = 8001);

signals:
    void dataReceived(const std::vector<std::vector<Fusion::PixelData>> &values,
                      Buffer::RadarData r);

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer *server;
    QTcpSocket *clientSocket;
};

#endif // erfanmocker_H
