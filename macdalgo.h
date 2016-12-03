#ifndef MACDALGO_H
#define MACDALGO_H

#include "algo.h"

class MacdAlgo : public Algo
{
public:
    MacdAlgo();
    virtual ~MacdAlgo();

    virtual bool shouldBuy(const Prices &prices);
};

#endif // MACDALGO_H
