#include <QCoreApplication>
#include <ctime>
#include "runner.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qsrand(time(0));

    Runner runner;
    Q_UNUSED(runner);

    return a.exec();
}
