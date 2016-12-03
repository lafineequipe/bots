#ifndef ASSETPRICES_H
#define ASSETPRICES_H

#include <vector>
#include "algo.h"

class AssetPrices
{
    Prices historicalPrices;
    Prices averages;
    Prices stdDeviations;

public:
    friend class Bollingers;
    AssetPrices(const Prices& _historicalPrices);

    void ComputeAveragesAndStdDeviations();

};

#endif // ASSETPRICES_H
