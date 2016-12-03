#include <QDebug>
#include "macdalgo.h"

static const int shortDurationMin = 3;
static const int shortDurationRange = 25;
static const int longDurationMin = 5;
static const int longDurationRange = 60;
static const int signalMmeDurationMin = 2;
static const int signalMmeDurationRange = 50;
static const int minimumDurationMin = 50;
static const int minimumDurationRange = 50;

MacdAlgo::MacdAlgo(bool random,
                   int shortDuration,
                   int longDuration,
                   int signalMmeDuration,
                   int minimumDuration)
    : _shortDuration(shortDuration),
      _longDuration(longDuration),
      _signalMmeDuration(signalMmeDuration),
      _minimumDuration(minimumDuration)
{
    if (random)
    {
        _shortDuration = qrand() % shortDurationRange + shortDurationMin;
        _longDuration = qrand() % longDurationRange + longDurationMin;

        if (_longDuration <= _shortDuration)
            _longDuration = _shortDuration + _longDuration;

        _signalMmeDuration = qrand() % signalMmeDurationRange + signalMmeDurationMin;
        _minimumDuration = qrand() % minimumDurationRange + minimumDurationMin;
    }
}

MacdAlgo::~MacdAlgo()
{
}

Action MacdAlgo::getNextAction(const Prices &prices)
{
    Prices macds = macd(prices, _shortDuration, _longDuration);
    Prices signalMacds = mme(macds, _signalMmeDuration);

    bool shouldBuy = true;
    bool shouldSell = true;

    for (int i = 0; i < _minimumDuration; ++i)
        if (macds[macds.size() - i - 1] <= signalMacds[macds.size() - i - 1])
        {
            shouldBuy = false;
            break;
        }

    for (int i = 0; i < _minimumDuration; ++i)
        if (macds[macds.size() - i - 1] >= signalMacds[macds.size() - i - 1])
        {
            shouldSell = false;
            break;
        }

    if (shouldBuy)
        return Buy;
    if (shouldSell)
        return Sell;
    return Nothing;
}

Prices MacdAlgo::mma(const Prices &prices, int duration)
{
    Prices values(prices.size());

    for (int i = 0; i < prices.size(); ++i)
        values[i] = 0;

    for (int i = 0; i < prices.size() - duration; ++i)
    {
        double sum = std::accumulate(prices.begin() + i, prices.begin() + i + duration, 0.0);
        values[i + duration] = sum / static_cast<double>(duration);
    }

    return values;
}

Prices MacdAlgo::mme(const Prices &prices, int duration)
{
    Prices values(prices.size());

    for (int i = 0; i < prices.size(); ++i)
        values[i] = 0;

    double lastValue = prices[0];
    values[0] = lastValue;

    for (int i = 1; i < prices.size(); ++i)
    {
        int currentDuration = i + 1 < duration ? i + 1 : duration;
        double currentMME = lastValue + (2.0 / (currentDuration + 1)) * (prices[i] - lastValue);
        values[i] = currentMME;
        lastValue = currentMME;
    }

    return values;
}

Prices MacdAlgo::macd(const Prices &prices, int shortDuration, int longDuration)
{
    Prices longValues;
    Prices shortValues;
    Prices values(prices.size());

    for (int i = 0; i < prices.size(); ++i)
        values[i] = 0;

    shortValues = mme(prices, shortDuration);
    longValues = mme(prices, longDuration);

    for (int i = longDuration; i < prices.size(); ++i)
        values[i] = shortValues[i] - longValues[i];

    return values;
}

/*

=> Using MMA and not MME

Prices Algo::macd(const Prices &prices, int shortDuration, int longDuration)
{
    Prices longValues;
    Prices shortValues;
    Prices values(prices.size());

    for (int i = 0; i < prices.size(); ++i)
        values[i] = 0;

    shortValues = mma(prices, shortDuration);
    longValues = mma(prices, longDuration);

    for (int i = longDuration; i < prices.size(); ++i)
    {
        values[i] = shortValues[i] - longValues[i];
    }

    return values;
}

*/


/*

=> Using MMA and not MME

bool MacdAlgo::shouldBuy(const Prices &prices)
{
    Prices signalMacds(prices.size());
    Prices macds = macd(prices, _shortDuration, _longDuration);

    for (int i = 0; i < prices.size(); ++i)
        signalMacds[i] = 0;

    for (int i = _longDuration; i < prices.size() - _signalMmeDuration + 1; ++i)
    {
        double value = std::accumulate(macds.begin() + i, macds.begin() + i + _signalMmeDuration, 0.0);
        signalMacds[i + _signalMmeDuration - 1] = value / static_cast<double>(_signalMmeDuration);
    }

    for (int i = 0; i < _minimumDuration; ++i)
        if (macds[macds.size() - i - 1] <= signalMacds[macds.size() - i - 1])
            return false;

    return true;
}

bool MacdAlgo::shouldSell(const Prices &prices)
{
    Prices signalMacds(prices.size());
    Prices macds = macd(prices, _shortDuration, _longDuration);

    for (int i = 0; i < prices.size(); ++i)
        signalMacds[i] = 0;

    for (int i = _longDuration; i < prices.size() - _signalMmeDuration + 1; ++i)
    {
        double value = std::accumulate(macds.begin() + i, macds.begin() + i + _signalMmeDuration, 0.0);
        signalMacds[i + _signalMmeDuration - 1] = value / static_cast<double>(_signalMmeDuration);
    }

    for (int i = 0; i < _minimumDuration; ++i)
        if (macds[macds.size() - i - 1] > signalMacds[macds.size() - i - 1])
            return false;

    return true;
}

*/
