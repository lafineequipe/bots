#ifndef BOLLINGERS_H
#define BOLLINGERS_H

#include "assetprices.h"
#include "algo.h"

class Bollingers : Algo
{
    AssetPrices assetPrices;
    std::vector<double> upperBand;
    std::vector<double> lowerBand;
    double decisionFactor;

public:
    Bollingers(const AssetPrices&, double factor);
    void computeBands(int period);

    virtual Action getNextAction(const Prices &prices, int period);

    void updateAssetPrices(const Prices& prices);
};

#endif // BOLLINGERS_H
