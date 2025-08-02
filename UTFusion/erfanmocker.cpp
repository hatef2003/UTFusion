#include "erfanmocker.h"
#include <QJsonArray> // Add this include

ErfanMocker::ErfanMocker(QObject *parent)
    : QObject(parent)
    , server(new QTcpServer(this))
    , clientSocket(nullptr)
{
    connect(server, &QTcpServer::newConnection, this, &ErfanMocker::onNewConnection);
}

void ErfanMocker::startServer(quint16 port)
{
    server->listen(QHostAddress::Any, port);
}

void ErfanMocker::onNewConnection()
{
    clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &ErfanMocker::onReadyRead);
}

void ErfanMocker::onReadyRead()
{
    QByteArray data = clientSocket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        std::vector<std::vector<Fusion::PixelData>> mock_values;
        mock_values.reserve(obj["values"].toArray().size());
        QJsonArray valuesArray = obj["values"].toArray();
        qint64 timestamp = obj["timestamp"].toVariant().toLongLong();
        for (const QJsonValue &value : valuesArray) {
            QJsonObject valueObj = value.toObject();
            std::vector<Fusion::PixelData> pixelDataList;
            pixelDataList.reserve(valueObj["pixels"].toArray().size());
            QJsonArray pixelsArray = valueObj["pixels"].toArray();
            for (const QJsonValue &pixelValue : pixelsArray) {
                QJsonObject pixelObj = pixelValue.toObject();
                Fusion::PixelData pixelData;
                pixelData.pixel_depth = pixelObj["pixel_depth"].toDouble();
                pixelData.pixel_pos_x = pixelObj["pixel_pos_x"].toDouble();
                pixelData.pixel_pos_y = pixelObj["pixel_pos_y"].toDouble();
                pixelDataList.push_back(pixelData);
            }
            mock_values.push_back(pixelDataList);
        }
        QList<uint> radarValues;
        for (const QJsonValue &val : obj["radarData"].toArray())
            radarValues.append(val.toInt());
        Buffer::RadarData r;
        r.a = radarValues[0];
        r.b = radarValues[1];
        r.c = radarValues[2];
        r.d = radarValues[3];
        r.e = radarValues[4];
        r.f = radarValues[5];
        r.timestamp = timestamp;
        emit dataReceived(mock_values, r);
    }
}

