#include "algo.h"

double Algo::mma(const Prices &prices, int duration)
{
    int last = prices.size() - 1;
    double value = 0;

    if (duration > 0)
    {
        duration = qMin<int>(prices.size(), duration);
        for (int i = 0; i < duration; ++i)
            value += prices[last - i];
        value = value / duration;
    }

    return value;
}

double Algo::mme(const Prices &prices, int duration)
{
    int last = prices.size() - 1;
    double value = prices[last];
    double lastValue = value;

    for (int i = 1; i < duration; ++i)
    {
        value = lastValue + (2 / (duration + 1)) * (prices[last - i] - lastValue);
        lastValue = value;
    }

    return value;
}

double Algo::macd(const Prices &prices, int shortDuration, int longDuration)
{
    return mme(prices, shortDuration) - mme(prices, longDuration);
}
