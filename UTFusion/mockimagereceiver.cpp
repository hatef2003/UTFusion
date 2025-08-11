#include "mockimagereceiver.h"
#include "qdatetime.h"
#include <QDataStream>
#include<QTime>

MockImageReceiver::MockImageReceiver(QObject *parent)
    : QObject(parent), server(new QTcpServer(this)), clientSocket(nullptr)
{
    connect(server, &QTcpServer::newConnection, this, &MockImageReceiver::onNewConnection);
}

void MockImageReceiver::startServer(quint16 port)
{
    server->listen(QHostAddress::Any, port);
}

void MockImageReceiver::onNewConnection()
{
    clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &MockImageReceiver::onReadyRead);
}

void MockImageReceiver::onReadyRead()
{
    buffer.append(clientSocket->readAll());

    
    while (buffer.size() >= 8) {
        QDataStream stream(buffer);
        stream.setByteOrder(QDataStream::BigEndian);

        quint32 img1Size, img2Size;
        stream >> img1Size;

        if (buffer.size() < 4 + img1Size + 4)
            return; 

        QByteArray img1Data = buffer.mid(4, img1Size);

        stream.device()->seek(4 + img1Size);
        stream >> img2Size;

        if (buffer.size() < 4 + img1Size + 4 + img2Size)
            return; 

        QByteArray img2Data = buffer.mid(4 + img1Size + 4, img2Size);

        QImage img1, img2;
        img1.loadFromData(img1Data);
        img2.loadFromData(img2Data);

        qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
        emit imagesReceived(img1, img2, timestamp);  
        

        buffer.remove(0, 4 + img1Size + 4 + img2Size);
    }
}
