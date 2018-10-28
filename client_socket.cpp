#include "client_socket.h"
#include "weather_station.h"
#include "ui_weather_station.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>


Client_socket::Client_socket(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
}

Client_socket::~Client_socket()
{
    if(socket != nullptr)
    {
        delete socket;
    }
}

void Client_socket::connectToIP(QString ipAddr)
{

    qDebug() << "Connecting to server...";

    socket->connectToHost(ipAddr, 54000);

    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    }
    else
    {
        qDebug() << "Connection succesfull!";
    }
}

void Client_socket::receiveData()
{
    int nIndex;
    QByteArray nIndexArray;
    QByteArray newjson;
    QJsonObject jsonobject;

    qDebug() << "Reading...";

    if(socket->canReadLine())
    {
        newjson = QByteArray(socket->readAll());

        if(socket->state() == QAbstractSocket::ConnectedState)
        {
            this->jsonString.clear();
            this->jsonString = newjson;
        }
    }


    nIndex = jsonString.indexOf("\n");
    nIndexArray = jsonString.left(nIndex);

    qDebug() << nIndexArray;

    jsonobject = QJsonDocument::fromJson(nIndexArray).object();

    this->valueTemperature = jsonobject.value(QString("temperature")).toDouble();
    this->valueHumidity = jsonobject.value(QString("humidity")).toDouble();
    this->valuePressure = jsonobject.value(QString("pressure")).toDouble();




}

bool Client_socket::isConnected(){
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

double Client_socket::returnDataValues(returnValueState valueState){
    if(valueState == stateTemperature)
    {
        return this->valueTemperature;
    }
    else if(valueState == stateHumidity)
    {
        return this->valueHumidity;
    }
    else if(valueState == statePressure)
    {
        return this->valuePressure;
    }
    else
    {
      return 0.0;
    }
}





