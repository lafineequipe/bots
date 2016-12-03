#ifndef BOT_H
#define BOT_H

#include <QMap>
#include "algo.h"

enum Method
{
    MACD,
    Bollinger,
    Trends,
    MaxMethods
};

class Bot
{
public:
    Bot(const Prices& history);
    virtual ~Bot();

    void processPrice(double todayPrice);

    virtual Method getBest() = 0;
    virtual bool shouldBuy(const Prices& history, Method method) = 0;
    virtual bool shouldSell(const Prices& history, Method method) = 0;

protected:
    Prices _history;
    QMap<Method, int> _scores;
};

#endif // BOT_H
