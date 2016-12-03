#ifndef MACDALGO_H
#define MACDALGO_H

#include "algo.h"

class MacdAlgo : public Algo
{
public:
    MacdAlgo(bool random = false,
             int shortDuration = 12,
             int longDuration = 26,
             int signalMmeDuration = 9,
             int minimumDuration = 14);
    virtual ~MacdAlgo();

    virtual Action getNextAction(const Prices &prices);

private:
    Prices mma(const Prices &prices, int duration);
    Prices mme(const Prices &prices, int duration);
    Prices macd(const Prices &prices, int shortDuration, int longDuration);

private:
    int _shortDuration;
    int _longDuration;
    int _signalMmeDuration;
    int _minimumDuration;
};

#endif // MACDALGO_H
