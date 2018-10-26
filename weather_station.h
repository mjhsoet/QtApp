#ifndef WEATHER_STATION_H
#define WEATHER_STATION_H

#include "client_socket.h"

#include <QFile>
#include <QTextStream>
#include <QWidget>
#include <string>
#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QTimer>




namespace Ui {
class Weather_Station;
}

class Weather_Station : public QWidget
{
    Q_OBJECT

public:
    explicit Weather_Station(QWidget *parent = nullptr);
    ~Weather_Station();

public slots:
    void refreshData();

private slots:
    void on_Ipsend_clicked();

private:
    QTcpSocket *socket;
    Ui::Weather_Station *ui;
    Client_socket cSocket;

private:
    QTimer *timer;
};

#endif // WEATHER_STATION_H
