#include "Bot.h"

Bot::Bot(const Prices &history)
    : _history(history)
{
    for (int i = MACD; i < MaxMethods; i = i + 1)
    {
        _scores[static_cast<Method>(i)] = 0;
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
        setMethod(method);
        bool buy = shouldBuy(_history);
        bool sell = !buy ? shouldSell(_history) : false;

        if (buy || sell)
        {
            bool shouldBuy = _history.last() < todayPrice;
            if ((buy && shouldBuy) || (sell && !shouldBuy))
                _scores[method] = _scores[method] + 1;
        }
    }

    _history.append(todayPrice);
}
