#include <QDebug>
#include "simplebot.h"

SimpleBot::SimpleBot(const Prices &history)
    : Bot(history), _macd()
{
}

void SimpleBot::setBest()
{
    int betterValue = 0;
    Method better = MaxMethods;

    for (auto it = _scores.constBegin(); it != _scores.constEnd(); ++it)
    {
        switch (it.key())
        {
            case MACD:
                qDebug() << "MACD:" << it.value() << "correct values";
                break;
            case Bollinger:
                qDebug() << "Bollinger:" << it.value() << "correct values";
                break;
            case Trends:
                qDebug() << "Trends:" << it.value() << "correct values";
                break;
            default:
                break;
        }

        if (better == MaxMethods || it.value() > betterValue)
        {
            better = it.key();
            betterValue = it.value();
        }
    }
    this->setMethod(better);
}

bool SimpleBot::shouldBuy(const Prices &history)
{
    if (this->getMethod() == MACD)
        return _macd.shouldBuy(history);
    return false;
}

bool SimpleBot::shouldSell(const Prices &history)
{
    if (this->getMethod() == MACD)
        return _macd.shouldSell(history);
    return false;
}

QString SimpleBot::toString() const
{
    if (this->getMethod() == MACD)
        return _macd.toString();
    return ""; // throw?
}
