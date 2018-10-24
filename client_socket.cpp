#include "client_socket.h"
#include "weather_station.h"
#include "ui_weather_station.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonValueRef>


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
    else
    {
        qDebug() << "Connection succesfully";
    }
}

void Client_socket::sendData(){
    updateJson();
    qDebug() << newjson;
    qDebug() << lastjson;
    doc = QJsonDocument::fromJson(lastjson);
    test = doc.object();
    QJsonValue value = test.value(QString("temperature"));
    QJsonValue value2 = test.value(QString("humidity"));
    QJsonValue value3 = test.value(QString("pressure"));
    this->temperatureVal = value.toDouble();
    this->humidityVal = value2.toDouble();
    this->pressureVal = value3.toDouble();

}

bool Client_socket::connected(){
    if(socket->state() == QAbstractSocket::ConnectedState){
        return 1;
    }
    else{
        return 0;
    }
}

double Client_socket::returnValues(returnValTypeDef type){
    if(type == temperature){
        return this->temperatureVal;
    }
    else if(type == humidity){
        return this->humidityVal;
    }
    else if(type == pressure){
        return this->pressureVal;
    }
    else
    {
      return 0.0;
    }
}

void Client_socket::updateJson()
{

    qDebug() << "Reading...";

    newjson = 0;



    if(socket->canReadLine())
    {
        socket->setReadBufferSize(55);
        socket->readBufferSize();

        newjson = QByteArray(socket->readAll());

        if(socket->state() == QAbstractSocket::ConnectedState){
            lastjson = 0;
            lastjson = newjson;
        }
    }
}





