#include <QDebug>
#include "runner.h"
#include "Simplebot.h"

static const int Iterations = 100;

Runner::Runner(QObject *parent)
    : QObject(parent), _feeder("AAPL", 400)
{
    connect(&_feeder, SIGNAL(finished(const Prices &)), this, SLOT(start(const Prices &)));
}

void Runner::start(const Prices &history)
{
    if (history.size() < 2 * Iterations)
    {
        qDebug() << "Cannot process so few input";
        return;
    }

    Prices oldTrades = history.mid(0, history.size() - Iterations);
    SimpleBot bot(oldTrades);

    for (int i = history.size() - Iterations; i < history.size(); ++i)
        bot.processPrice(history[i]);

    bot.setBest();
    switch (bot.getMethod())
    {
        case MACD:
            qDebug() << bot << " is the best";
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
