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

struct Result
{
    Method type;
    int sells;
    int purchases;
    int mistakes;
};

class Bot
{
public:
    Bot(const Prices& history);
    virtual ~Bot();

    void processPrice(double todayPrice);

    virtual Result getBest() = 0;
    virtual Action getNextAction(const Prices& history, Method method) = 0;

protected:
    Prices _history;
    QMap<Method, Result> _scores;
};

#endif // BOT_H
