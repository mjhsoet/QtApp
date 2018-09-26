#include "client_socket.h"
#include "weather_station.h"
#include "ui_weather_station.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>


Client_socket::Client_socket(QObject *parent) : QObject(parent)
{

}

Client_socket::~Client_socket()
{
    if(socket != nullptr)
    {
        delete socket;
    }
}

void Client_socket::Test(QString ipAddr)
{
    socket = new QTcpSocket(this);

    qDebug() << "Connecting to server...";


    socket->connectToHost(ipAddr, 54000);

    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    }

    if(socket->ConnectedState == true)
    {
        while(!socket->waitForDisconnected(2000))
        {
            updateJson();
            qDebug() << lastjson;
            QJsonDocument doc = QJsonDocument::fromJson(lastjson);
            QJsonObject test = doc.object();
            QJsonValue value = test.value(QString("temperature"));
            qDebug() << value.toDouble();
        }
    }

}

void Client_socket::updateJson()
{
    qDebug() << "Reading...";

    if(socket->waitForReadyRead(3000))
    {
        lastjson = QByteArray(socket->readAll());
    }
}





