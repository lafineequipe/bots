#include <QCoreApplication>
#include "runner.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Runner runner;
    Q_UNUSED(runner);

    return a.exec();
}
