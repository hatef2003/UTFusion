#ifndef erfanmocker_H
#define erfanmocker_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

class erfanmocker : public QObject
{
    Q_OBJECT
public:
    explicit erfanmocker(QObject *parent = nullptr);

    void startServer(quint16 port = 8001);
private:
    struct PixelData {
        float pixel_depth;
        float pixel_pos_x;
        float pixel_pos_y;
    };

signals:
    void dataReceived(const std::vector<std::vector<PixelData>> &values);

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer *server;
    QTcpSocket *clientSocket;
};

#endif // erfanmocker_H
