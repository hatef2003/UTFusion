#ifndef MOCKIMAGERECEIVER_H
#define MOCKIMAGERECEIVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QImage>

class MockImageReceiver : public QObject
{
    Q_OBJECT
public:
    explicit MockImageReceiver(QObject *parent = nullptr);
    void startServer(quint16 port = 8080);

signals:
    //s:
    void imagesReceived(const QImage &img1, const QImage &img2,qint64 timestamp );

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer *server;
    QTcpSocket *clientSocket;
    QByteArray buffer;
};

#endif // MOCKIMAGERECEIVER_H
