#ifndef ALGO_H
#define ALGO_H

#include <QVector>

typedef QVector<double> Prices;

typedef int Action;

static const int Sell = -1;
static const int Nothing = 0;
static const int Buy = 1;

class Algo
{
public:
    virtual Action getNextAction(const Prices &prices) = 0;
};

#endif // ALGO_H
