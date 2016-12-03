#include <QCoreApplication>

#include "feeder.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Feeder *feeder = new Feeder("AAPL");

    return a.exec();
}
