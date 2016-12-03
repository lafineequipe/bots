#ifndef BOT_H
#define BOT_H

#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include "algo.h"

enum Method
{
    MACD,
    Bollinger,
    Wisdom,
    MaxMethods
};

struct Result
{
    Method type;
    int sells;
    int purchases;
    int mistakes;
};

class WisdomBot;

class Bot
{
public:
    Bot(WisdomBot *wisdom, Method method, const Prices& history);
    virtual ~Bot();

    QJsonObject toJson() const;
    void processPrice(double todayPrice);

    virtual Action getNextAction(const Prices& history, Method method) = 0;

protected:
    WisdomBot *_wisdom;
    QJsonArray _feed;
    Method _method;
    Prices _history;
    Result _score;
};

#endif // BOT_H
