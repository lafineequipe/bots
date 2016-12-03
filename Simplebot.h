#ifndef SIMPLEBOT_H
#define SIMPLEBOT_H

#include "Bot.h"
#include "macdalgo.h"

class SimpleBot : public Bot
{
public:
    SimpleBot(const Prices& history);

    virtual void setBest();
    virtual bool shouldBuy(const Prices& history);
    virtual bool shouldSell(const Prices& history);

    virtual QString toString() const;

    operator QString() const {
        return toString();
    }

private:
    MacdAlgo _macd;
};

#endif // SIMPLEBOT_H
