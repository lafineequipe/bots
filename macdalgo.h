#ifndef MACDALGO_H
#define MACDALGO_H

#include "algo.h"

class MacdAlgo : public Algo
{
public:
    MacdAlgo(int shortDuration = 12,
             int longDuration = 26,
             int signalMmeDuration = 9,
             int minimumDuration = 14);
    virtual ~MacdAlgo();

    virtual bool shouldBuy(const Prices &prices);
    virtual bool shouldSell(const Prices &prices);

private:
    int _shortDuration;
    int _longDuration;
    int _signalMmeDuration;
    int _minimumDuration;
};

#endif // MACDALGO_H
