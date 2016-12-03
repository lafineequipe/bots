#ifndef ALGO_H
#define ALGO_H

#include <list>

typedef std::list<double> Prices;

class Algo
{
public:
    virtual bool shouldBuy(const Prices &prices) = 0;
};

#endif // ALGO_H
