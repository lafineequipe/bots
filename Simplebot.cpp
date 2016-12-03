#include <QDebug>
#include "simplebot.h"

SimpleBot::SimpleBot(WisdomBot *wisdom, Method method, const Prices &history, bool random)
    : Bot(wisdom, method, history), _macd(random), _bollingers(1.0002, 20)
{
}

Action SimpleBot::getNextAction(const Prices &history, Method method)
{
    if (method != _method)
        return Nothing;

    if (method == MACD)
        return _macd.getNextAction(history);
    if (method == Bollinger)
        return _bollingers.getNextAction(history);

    return Nothing;
}
