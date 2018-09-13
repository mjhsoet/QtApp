#include "weather_station.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Weather_Station w;
    w.show();

    return a.exec();
}
