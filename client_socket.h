#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "ui_weather_station.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

typedef enum
{
    stateTemperature,
    stateHumidity,
    statePressure
} returnValueState;

class Client_socket : public QObject
{

public:
    Client_socket(QObject *parent = nullptr);
    virtual ~Client_socket();

public:
    void connectToIP(QString ipAddr);
    void receiveData();
    bool isConnected();
    double returnDataValues(returnValueState);

private:
    QTcpSocket *socket;
    QByteArray jsonString;
    double valueTemperature, valueHumidity, valuePressure;
};

#endif // CLIENT_SOCKET_H
