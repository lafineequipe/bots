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
    Prices d = prices;

    for (int i = 0; i < _minimumDuration; ++i)
    {
        if (macd(d, _shortDuration, _longDuration) <= mme(prices, _signalMmeDuration))
            return false;
        d.removeLast();
    }

    return true;
}
