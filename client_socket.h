#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "ui_weather_station.h"

typedef enum {
    temperature,
    humidity
} returnValTypeDef;

class Client_socket : public QObject
{

public:
    Client_socket(QObject *parent = nullptr);
    virtual ~Client_socket();

public:
    void Test(QString ipAddr);
    void updateJson();
    void sendData();
    bool connected();
    double returnValues(returnValTypeDef type);
private:
    QTcpSocket *socket;
    QByteArray lastjson, newjson;
    double temperatureVal, humidityVal;
};

#endif // CLIENT_SOCKET_H
