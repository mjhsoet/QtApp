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
    void on_Manual_refresh_clicked();

    void on_Ipsend_clicked();

private:
    QTcpSocket *socket;
    Ui::Weather_Station *ui;
    Client_socket mTest;

private:
    //double temperature = 1.1;
    //double humidity = 1.2;
    QTimer *timer;
};

#endif // WEATHER_STATION_H
