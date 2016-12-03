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
    int period;

public:
    Bollingers(double factor, int period);
    void computeBands(int period);

    virtual Action getNextAction(const Prices &prices);

    void updateAssetPrices(const Prices& prices);
};

#endif // BOLLINGERS_H
