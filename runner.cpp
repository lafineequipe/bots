#include <QDebug>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QFile>
#include "runner.h"
#include "Simplebot.h"

static const int Iterations = 200;

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
    QVector<SimpleBot *> bots;

    bots.push_back(new SimpleBot(Bollinger, oldTrades));
    bots.push_back(new SimpleBot(MACD, oldTrades));

    for (int i = 0; i < 50; ++i)
        bots.push_back(new SimpleBot(MACD, oldTrades, true));

    for (int i = history.size() - Iterations; i < history.size(); ++i)
        for (SimpleBot *bot : bots)
            bot->processPrice(history[i]);

    QJsonArray tradesArray;

    for (double price : history)
        tradesArray.append(price);

    QJsonObject trades;
    trades.insert("name", _feeder.getName());
    trades.insert("feed", tradesArray);

    QJsonArray root;
    root.append(trades);

    for (SimpleBot *bot : bots)
        root.append(bot->toJson());

    QJsonDocument document(root);
    QFile file(qApp->applicationDirPath() + "/demos/data.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        file.write(document.toJson());
    else
        qWarning() << file.errorString();

    qDebug() << "Done";
}
