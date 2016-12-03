#ifndef ASSETPRICES_H
#define ASSETPRICES_H

#include <vector>

class AssetPrices
{
    std::vector<double> historicalPrices;
    std::vector<double> averages;
    std::vector<double> stdDeviations;

public:
    friend class Bollingers;
    AssetPrices();
    AssetPrices(const std::vector<double>& _historicalPrices);

    void ComputeAveragesAndStdDeviations();

};

#endif // ASSETPRICES_H
