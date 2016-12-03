#ifndef WISDOMBOT_H
#define WISDOMBOT_H

#include "Bot.h"

class WisdomBot : public Bot
{
public:
    WisdomBot(const Prices &history);

    void registerAction(Action action);

    virtual Action getNextAction(const Prices& history, Method method);

private:
    QVector<Action> _pending;
};

#endif // WISDOMBOT_H
