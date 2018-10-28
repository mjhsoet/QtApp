#include "weather_station.h"
#include "ui_weather_station.h"
#include "client_socket.h"

Weather_Station::Weather_Station(QWidget *parent) : QWidget(parent), ui(new Ui::Weather_Station)
{
    ui->setupUi(this);
    ui->Temperature_window->setFontPointSize(32);
    ui->Humidity_window->setFontPointSize(32);
    ui->Pressure_window->setFontPointSize(32);

    timer = new QTimer(this);
}

Weather_Station::~Weather_Station()
{
    delete ui;
    delete timer;
}

void Weather_Station::on_Ipsend_clicked()
{
    cSocket.connectToIP(ui->ipaddress->text());
    if(cSocket.isConnected() == 1)
    {
        ui->Connection_window->setText("Connected to server!");
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(refreshData()));
        timer->start(5000);
    }
    else if(cSocket.isConnected() == 0)
    {
        ui->Connection_window->setText("Connection failed...");
        ui->Connection_window->append("Retry connection");
    }
}

void Weather_Station::refreshData()
{

    if(cSocket.isConnected() == 1)
    {
        cSocket.receiveData();

        ui->Temperature_window->setText(QString::number(cSocket.returnDataValues(stateTemperature)));
        ui->Humidity_window->setText(QString::number(cSocket.returnDataValues(stateHumidity)));
        ui->Pressure_window->setText(QString::number(cSocket.returnDataValues(statePressure)));

        qDebug() <<  cSocket.returnDataValues(stateTemperature);
        qDebug() <<  cSocket.returnDataValues(stateHumidity);
        qDebug() << cSocket.returnDataValues(statePressure);
    }
    else
    {
        ui->Connection_window->append("Looking for connection...");
        qDebug() << "Looking for connection...";

        timer->stop();
        Weather_Station::on_Ipsend_clicked();
    }

}

