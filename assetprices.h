#ifndef ASSETPRICES_H
#define ASSETPRICES_H

class AssetPrices
{
    vector<double> historicalPrices;
    vector<double> averages;
    vector<double> stdDeviations;

public:
    friend class Bollingers;
    AssetPrices();
    AssetPrices(const vector<double>& _historicalPrices);

    double ComputeAveragesAndStdDeviations();

};

#endif // ASSETPRICES_H
