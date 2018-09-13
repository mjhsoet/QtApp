#ifndef WEATHER_STATION_H
#define WEATHER_STATION_H

#include <QFile>
#include <QTextStream>
#include <QWidget>
#include <string>

namespace Ui {
class Weather_Station;
}

class Weather_Station : public QWidget
{
    Q_OBJECT

public:
    explicit Weather_Station(QWidget *parent = nullptr);
    ~Weather_Station();

private slots:
    void on_Manual_refresh_clicked();

    void on_Ipsend_clicked();

private:
    Ui::Weather_Station *ui;
    QString ipAddr;
};

#endif // WEATHER_STATION_H
