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

bool SimpleBot::shouldBuy(const Prices &history, Method method)
{
    if (method == MACD)
        return _macd.shouldBuy(history);
    return false;
}

bool SimpleBot::shouldSell(const Prices &history, Method method)
{
    if (method == MACD)
        return _macd.shouldSell(history);
    return false;
}
