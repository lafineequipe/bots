#ifndef ALGO_H
#define ALGO_H

#include <QVector>

typedef QVector<double> Prices;

class Algo
{
public:
    virtual bool shouldBuy(const Prices &prices) = 0;
    virtual bool shouldSell(const Prices &prices) = 0;

    Prices mma(const Prices &prices, int duration);
    Prices mme(const Prices &prices, int duration);
    Prices macd(const Prices &prices, int shortDuration, int longDuration);
};

#endif // ALGO_H
