#ifndef BOLLINGERS_H
#define BOLLINGERS_H

#include "assetprices.h"

class Bollingers
{
    AssetPrices assetPrices;
    std::vector<double> upperBand;
    std::vector<double> lowerBand;
    double decisionFactor;

public:
    Bollingers(const AssetPrices&, double factor);
    void computeBands();

    bool shouldBuy();
    bool shouldSell();
};

#endif // BOLLINGERS_H
