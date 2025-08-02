#include "MockRadarData.h"
#include <QJsonArray> // Add this include
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

        //S: in here, we R getting info from Json:
        // replace with this to get info from sensor: //cam - Radar
        //Alternative to code below:
        // qint64 timestamp = obj["timestamp"].toVariant().toLongLong();
        qint64 timestamp = QDateTime::currentMSecsSinceEpoch();

        emit dataReceived(values, timestamp);
    }
}
