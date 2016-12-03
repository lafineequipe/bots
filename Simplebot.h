#ifndef SIMPLEBOT_H
#define SIMPLEBOT_H

#include "Bot.h"
#include "macdalgo.h"
#include "bollingers.h"

class SimpleBot : public Bot
{
public:
    SimpleBot(const Prices& history, bool random = false);

    virtual Result getBest();
    virtual Action getNextAction(const Prices& history, Method method);

private:
    MacdAlgo _macd;
    Bollingers _bollingers;
};

#endif // SIMPLEBOT_H
