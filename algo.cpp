#include "algo.h"

double Algo::mma(const Prices &prices, int duration)
{
    double value = 0;

    if (duration > 0)
    {
        duration = qMin<int>(prices.size(), duration);
        for (int i = 0; i < duration; ++i)
            value += prices[i];
        value = value / duration;
    }

    return value;
}

double Algo::mme(const Prices &prices, int duration)
{
    double value = prices[0];
    double lastValue = value;

    for (int i = 1; i < duration; ++i)
    {
        value = lastValue + (2 / (duration + 1)) * (prices[i] - lastValue);
        lastValue = value;
    }

    return value;
}

double Algo::macd(const Prices &prices, int shortDuration, int longDuration)
{
    return mme(prices, shortDuration) - mme(prices, longDuration);
}
