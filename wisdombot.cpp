#include <numeric>
#include "wisdombot.h"

double sum(const QVector<Action> &array)
{
    return std::accumulate(array.begin(), array.end(), 0.0);
}

double mean(const QVector<Action> &array)
{
    return sum(array) / array.size();
}

double diversityTheorem(const QVector<Action> &predictions)
{
    return mean(predictions);
}

WisdomBot::WisdomBot(const Prices &history)
    : Bot(NULL, Wisdom, history)
{
}

void WisdomBot::registerAction(Action action)
{
    _pending.append(action);
}

Action WisdomBot::getNextAction(const Prices &history, Method method)
{
    Q_UNUSED(history);

    if (method != _method)
        return Nothing;

    Action action = qBound(-1, (int)qRound(diversityTheorem(_pending)), 1);
    return action;
}
