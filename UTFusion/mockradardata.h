#ifndef MOCKRADARDATA_H
#define MOCKRADARDATA_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

class MockRadarData : public QObject
{
    Q_OBJECT
public:
    explicit MockRadarData(QObject *parent = nullptr);

    void startServer(quint16 port = 8000);

signals:
    void dataReceived(const QList<uint> &values, qint64 timestamp);

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer *server;
    QTcpSocket *clientSocket;
};

#endif // MOCKRADARDATA_H
