#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "ui_weather_station.h"

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
    double returnValues(double valueDef);
private:
    QTcpSocket *socket;
    QByteArray lastjson;
    double temperature, humidity;
};

#endif // CLIENT_SOCKET_H
