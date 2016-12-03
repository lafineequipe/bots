#ifndef SIMPLEBOT_H
#define SIMPLEBOT_H

#include "Bot.h"
#include "macdalgo.h"

class SimpleBot : public Bot
{
public:
    SimpleBot(const Prices& history);

    virtual Result getBest();
    virtual bool shouldBuy(const Prices& history, Method method);
    virtual bool shouldSell(const Prices& history, Method method);

private:
    MacdAlgo _macd;
};

#endif // SIMPLEBOT_H
