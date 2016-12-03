#include <QDebug>
#include "runner.h"
#include "Simplebot.h"

static const int Iterations = 50;

Runner::Runner(QObject *parent)
    : QObject(parent)
{
}

void Runner::start(const Prices &history)
{
    Prices oldTrades = history.mid(0, history.size() - Iterations);
    SimpleBot bot(oldTrades);

    for (int i = history.size() - Iterations; i < history.size(); ++i)
        bot.processPrice(history[i]);

    Method best = bot.getBest();
    switch (best)
    {
        case MACD:
            qDebug() << "MACD is the best";
            break;
        case Bollinger:
            qDebug() << "Bollinger is the best";
            break;
        case Trends:
            qDebug() << "Trends is the best";
            break;
        default:
            qDebug() << "Bots are shy today";
            break;
    }
}
