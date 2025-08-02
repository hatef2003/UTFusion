#include "erfanmocker.h"
#include <QJsonArray> // Add this include

erfanmocker::erfanmocker(QObject *parent)
    : QObject(parent), server(new QTcpServer(this)), clientSocket(nullptr)
{
    connect(server, &QTcpServer::newConnection, this, &erfanmocker::onNewConnection);
}

void erfanmocker::startServer(quint16 port)
{
    server->listen(QHostAddress::Any, port);
}

void erfanmocker::onNewConnection()
{
    clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &erfanmocker::onReadyRead);
}

void erfanmocker::onReadyRead()
{
    QByteArray data = clientSocket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        std::vector<std::vector<PixelData>> mock_values;
        mock_values.reserve(obj["values"].toArray().size());
        QJsonArray valuesArray = obj["values"].toArray();

        for (const QJsonValue &value : valuesArray) {
            QJsonObject valueObj = value.toObject();
            std::vector<PixelData> pixelDataList;
            pixelDataList.reserve(valueObj["pixels"].toArray().size());
            QJsonArray pixelsArray = valueObj["pixels"].toArray();
            for (const QJsonValue &pixelValue : pixelsArray) {
                QJsonObject pixelObj = pixelValue.toObject();
                PixelData pixelData;
                pixelData.pixel_depth = pixelObj["pixel_depth"].toDouble();
                pixelData.pixel_pos_x = pixelObj["pixel_pos_x"].toDouble();
                pixelData.pixel_pos_y = pixelObj["pixel_pos_y"].toDouble();
                pixelDataList.push_back(pixelData);
            }
            mock_values.push_back(pixelDataList);
        }

        emit dataReceived(mock_values);
    }
}

