#include <QtCore/QCoreApplication>
#include <QApplication>

#include "weather_station.h"
#include "client_socket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Weather_Station w;


    w.show();


    return a.exec();
}
