#include "simplebot.h"

SimpleBot::SimpleBot(const Prices &history)
    : Bot(history)
{
}

Method SimpleBot::getBest()
{
    int betterValue = 0;
    Method better = MaxMethods;

    for (auto it = _scores.constBegin(); it != _scores.constEnd(); ++it)
        if (better == MaxMethods || it.value() > betterValue)
        {
            better = it.key();
            betterValue = it.value();
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
