#include <QDebug>
#include "macdalgo.h"

MacdAlgo::MacdAlgo(int shortDuration,
                   int longDuration,
                   int signalMmeDuration,
                   int minimumDuration)
    : _shortDuration(shortDuration),
      _longDuration(longDuration),
      _signalMmeDuration(signalMmeDuration),
      _minimumDuration(minimumDuration)
{
}

MacdAlgo::~MacdAlgo()
{
}

bool MacdAlgo::shouldBuy(const Prices &prices)
{
    Prices macds = macd(prices, _shortDuration, _longDuration);
    Prices signalMacds = mme(macds, _signalMmeDuration);

    for (int i = 0; i < _minimumDuration; ++i)
        if (macds[macds.size() - i - 1] <= signalMacds[macds.size() - i - 1])
            return false;

    return true;
}

bool MacdAlgo::shouldSell(const Prices &prices)
{
    Prices macds = macd(prices, _shortDuration, _longDuration);
    Prices signalMacds = mme(macds, _signalMmeDuration);

    for (int i = 0; i < _minimumDuration; ++i)
        if (macds[macds.size() - i - 1] >= signalMacds[macds.size() - i - 1])
            return false;

    return true;
}

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
