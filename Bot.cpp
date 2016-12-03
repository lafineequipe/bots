#include <QDebug>
#include "Bot.h"
#include "wisdombot.h"

Bot::Bot(WisdomBot *wisdom, Method method, const Prices &history)
    : _wisdom(wisdom), _method(method), _history(history)
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
    else if (_method == Bollinger)
        obj.insert("name", QString("Bot Bollinger %1").arg(++bollingerCount));
    else
        obj.insert("name", QString("Bot Wisdom"));

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

    if (_wisdom)
        _wisdom->registerAction(result);

    _feed.append(_score.purchases + _score.sells - _score.mistakes);
    _history.append(todayPrice);
}
