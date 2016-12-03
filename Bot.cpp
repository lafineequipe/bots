#include <QDebug>
#include "Bot.h"

Bot::Bot(const Prices &history)
    : _history(history)
{
    for (int i = MACD; i < MaxMethods; i = i + 1)
    {
        Result &d = _scores[static_cast<Method>(i)];
        d.type = static_cast<Method>(i);
        d.mistakes = 0;
        d.purchases = 0;
        d.sells = 0;
    }
}

Bot::~Bot()
{
}

void Bot::processPrice(double todayPrice)
{
    for (int i = MACD; i < MaxMethods; ++i)
    {
        Method method = static_cast<Method>(i);
        Action result = getNextAction(_history, method);
        bool buy = result == Buy;
        bool sell = !buy && result == Sell;

        if (buy || sell)
        {
            bool shouldBuy = _history.last() < todayPrice;
            if ((buy && shouldBuy) || (sell && !shouldBuy))
            {
                if (buy)
                    _scores[method].purchases += 1;
                else
                    _scores[method].sells += 1;
            }
            else
            {
                //qDebug() << "Mistake" << _history.last() << buy;
                _scores[method].mistakes += 1;
            }
        }
    }

    _history.append(todayPrice);
}
