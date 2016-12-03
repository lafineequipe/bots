#ifndef ALGO_H
#define ALGO_H

#include <QVector>

typedef QVector<double> Prices;

class Algo
{
public:
    virtual bool shouldBuy(const Prices &prices) = 0;
    virtual bool shouldSell(const Prices &prices) = 0;

    double mma(const Prices &prices, int duration);
    double mme(const Prices &prices, int duration);
    double macd(const Prices &prices, int shortDuration, int longDuration);
};

#endif // ALGO_H
