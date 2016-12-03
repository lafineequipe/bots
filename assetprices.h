#ifndef ASSETPRICES_H
#define ASSETPRICES_H

#include <vector>
#include "algo.h"

class AssetPrices
{
    Prices averages;
    Prices stdDeviations;
    Prices historicalPrices;

public:
    friend class Bollingers;
    AssetPrices();
    AssetPrices(const Prices&);

    void ComputeAveragesAndStdDeviations(int period);

};

#endif // ASSETPRICES_H
