#include <QDebug>
#include "simplebot.h"

SimpleBot::SimpleBot(const Prices &history)
    : Bot(history)
{
}

Result SimpleBot::getBest()
{
    Result better;
    better.type = MaxMethods;
    better.sells = 0;
    better.purchases = 0;
    better.mistakes = 0;

    for (auto it = _scores.constBegin(); it != _scores.constEnd(); ++it)
    {
        if (better.type == MaxMethods
            || it.value().purchases + it.value().sells > better.sells + better.purchases)
        {
            better = it.value();
        }
    }

    return better;
}

Action SimpleBot::getNextAction(const Prices &history, Method method)
{
    if (method == MACD)
        return _macd.getNextAction(history);
    else if (method == Bollinger)
    {
        Bollingers bollingers(history, 1.2);
        return bollingers.getNextAction(history);
    }
    return false;
}
