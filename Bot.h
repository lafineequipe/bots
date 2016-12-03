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

    void setMethod(Method method) { _method = method; }
    int getMethod() const { return _method; }

    void processPrice(double todayPrice);

    virtual void setBest() = 0;
    virtual bool shouldBuy(const Prices& history) = 0;
    virtual bool shouldSell(const Prices& history) = 0;

    virtual QString toString() const = 0;

protected:
    Prices _history;
    QMap<Method, int> _scores;
    Method _method;
};

#endif // BOT_H
