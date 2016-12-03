#include <numeric>
#include <QDebug>
#include "algo.h"

Prices Algo::mma(const Prices &prices, int duration)
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

Prices Algo::mme(const Prices &prices, int duration)
{
    Prices values(prices.size());

    for (int i = 0; i < prices.size(); ++i)
        values[i] = 0;

    double lastValue = prices[0];

    for (int i = 0; i < prices.size() - duration; ++i)
    {
        double sum = lastValue + (2.0 / (duration + 1)) * (prices[i] - lastValue);
        values[i + duration] = sum / static_cast<double>(duration);
    }

    return values;
}

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
