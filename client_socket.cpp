#include "client_socket.h"
#include "weather_station.h"
#include "ui_weather_station.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <cmath>


Client_socket::Client_socket(QObject *parent) : QObject(parent)         // Constructor. Creation of a new socket.
{
    socket = new QTcpSocket(this);
}

Client_socket::~Client_socket()         // Destructor. Deletion of the existing socket.
{
    if(socket != nullptr)
    {
        delete socket;
    }
}

void Client_socket::connectToIP(QString ipAddr)         // Connection to entered IP address in the line edit box.
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

void Client_socket::receiveData()           // Filters and reads data coming in from server.
{
    int nIndex;
    QByteArray nIndexArray;
    QByteArray newjson;
    QJsonObject jsonobject;

    qDebug() << "Reading...";

    if(socket->canReadLine())       // Statement that returns true if a line of data can be read.
    {
        newjson = QByteArray(socket->readAll());        // Stores all remaining data that can be read in a QByteArray, which is an array of bytes.

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
    this->valuePressure = std::round(jsonobject.value(QString("pressure")).toDouble());

}

bool Client_socket::isConnected()           // Boolean function that returns '1' when the socket is connected.
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

double Client_socket::returnDataValues(returnValueState valueState)         // Function that returns a certain value, dependent on the enum state.
{
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
        return this->valuePressure / 100;
    }
    else
    {
      return 0.0;
    }
}





