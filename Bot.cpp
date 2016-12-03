#include <QDebug>
#include "Bot.h"

Bot::Bot(Method method, const Prices &history)
    : _method(method), _history(history)
{
    _score.type = method;
    _score.mistakes = 0;
    _score.purchases = 0;
    _score.sells = 0;
}

Bot::~Bot()
{
}

QJsonObject Bot::toJson() const
{
    static int macdCount = 0;
    static int bollingerCount = 0;

    QJsonObject obj;

    if (_method == MACD)
        obj.insert("name", QString("Bot MACD %1").arg(++macdCount));
    else
        obj.insert("name", QString("Bot Bollinger %1").arg(++bollingerCount));

    obj.insert("feed", _feed);
    return obj;
}

void Bot::processPrice(double todayPrice)
{
    Action result = getNextAction(_history, _method);
    bool buy = result == Buy;
    bool sell = !buy && result == Sell;

    if (buy || sell)
    {
        bool shouldBuy = _history.last() < todayPrice;
        if ((buy && shouldBuy) || (sell && !shouldBuy))
        {
            if (buy)
                _score.purchases += 1;
            else
                _score.sells += 1;
        }
        else
            _score.mistakes += 1;
    }

    _feed.append(_score.purchases + _score.sells - _score.mistakes);
    _history.append(todayPrice);
}
