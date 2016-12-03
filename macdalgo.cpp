#include "macdalgo.h"

MacdAlgo::MacdAlgo()
{
}

MacdAlgo::~MacdAlgo()
{
}

bool MacdAlgo::shouldBuy(const Prices &prices)
{
    return macd(prices, 12, 26) > mme(prices, 9) * 1.1;
}
