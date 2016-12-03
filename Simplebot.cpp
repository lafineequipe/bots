#include <QDebug>
#include "simplebot.h"

SimpleBot::SimpleBot(const Prices &history, bool random)
    : Bot(history), _macd(random), _bollingers(1.0002, 20)
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
        return _bollingers.getNextAction(history);
    return false;
}
