#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>
#include "Bot.h"

class Runner : public QObject
{
    Q_OBJECT

public:
    explicit Runner(QObject *parent = 0);

public slots:
    void start(const Prices &history);
};

#endif // RUNNER_H
