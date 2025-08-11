#include "mockradardata.h"
#include <QJsonArray> 
MockRadarData::MockRadarData(QObject *parent)
    : QObject(parent), server(new QTcpServer(this)), clientSocket(nullptr)
{
    connect(server, &QTcpServer::newConnection, this, &MockRadarData::onNewConnection);
}

void MockRadarData::startServer(quint16 port)
{
    server->listen(QHostAddress::Any, port);
}

void MockRadarData::onNewConnection()
{
    clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &MockRadarData::onReadyRead);
}

void MockRadarData::onReadyRead()
{
    QByteArray data = clientSocket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        QList<uint> values;
        for (const QJsonValue &val : obj["values"].toArray())
            values.append(val.toInt());

        
        qint64 timestamp = obj["timestamp"].toVariant().toLongLong();

        
       
        emit dataReceived(values, timestamp);
    }
}
