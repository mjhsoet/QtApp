#include "weather_station.h"
#include "ui_weather_station.h"
#include "client_socket.h"

Weather_Station::Weather_Station(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Weather_Station)
{
    ui->setupUi(this);
    ui->Temperature_window->setFontPointSize(36);
    ui->Humidity_window->setFontPointSize(36);
}

Weather_Station::~Weather_Station()
{
    delete ui;
}

void Weather_Station::on_Manual_refresh_clicked()
{
    ui->Temperature_window->setText("\nhello");
    ui->Humidity_window->setText("\nworld");
}

void Weather_Station::on_Ipsend_clicked()
{
    Client_socket mTest;
    mTest.Test(ui->ipaddress->text());
}
