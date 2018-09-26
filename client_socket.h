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

private:
    QTcpSocket *socket;
    QByteArray lastjson;
    QString ipAdress;

};

#endif // CLIENT_SOCKET_H
