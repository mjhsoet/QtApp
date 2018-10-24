#include "weather_station.h"
#include "ui_weather_station.h"
#include "client_socket.h"

Weather_Station::Weather_Station(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Weather_Station)
{
    ui->setupUi(this);
    ui->Temperature_window->setFontPointSize(8);
    ui->Humidity_window->setFontPointSize(8);
    ui->Pressure_window->setFontPointSize(8);

    timer = new QTimer(this);
}

Weather_Station::~Weather_Station()
{
    delete ui;

    delete timer;

}

void Weather_Station::on_Ipsend_clicked()
{
    mTest.Test(ui->ipaddress->text());

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(refreshData()));
    timer->start(4500);
}

void Weather_Station::refreshData(){
    if(mTest.connected() == 1){
        mTest.sendData();
        ui->Temperature_window->setText(QString::number(mTest.returnValues(temperature)));
        qDebug() <<  mTest.returnValues(temperature);
        ui->Humidity_window->setText(QString::number(mTest.returnValues(humidity)));
        qDebug() <<  mTest.returnValues(humidity);
        ui->Pressure_window->setText(QString::number(mTest.returnValues(pressure)));
        qDebug() << mTest.returnValues(pressure);
    }
    else if(mTest.connected() == 0){
        ui->Temperature_window->setText("\nRetry");
        ui->Humidity_window->setText("\nto");
        ui->Pressure_window->setText("\nConnect");
    }
}

