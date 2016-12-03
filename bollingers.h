#ifndef BOLLINGERS_H
#define BOLLINGERS_H

#include "assetprices.h"

class Bollingers
{
    AssetPrices& assetPrices;
    std::vector<double> upperBand;
    std::vector<double> lowerBand;

public:
    Bollingers(AssetPrices&);
    void computeBands();

    bool shouldBuy(double tresholdFactor);
    bool shouldSell(double tresholdFactor);
};

#endif // BOLLINGERS_H
