#include "bollingers.h"

Bollingers::Bollingers(AssetPrices& _assetPrices)
    : assetPrices(_assetPrices)
{
    int n;
    n = assetPrices.historicalPrices.size();
    upperBand.resize(n);
    lowerBand.resize(n);
}

void Bollingers::computeBands()
{
    assetPrices.ComputeAveragesAndStdDeviations();
    int n = assetPrices.historicalPrices.size();
    for(int i=0; i<n; i++)
    {
        double diff = 2*assetPrices.stdDeviations[i];
        upperBand[i] = assetPrices.averages[i]+diff;
        lowerBand[i] = assetPrices.averages[i]-diff;
    }
}


bool Bollingers::shouldBuy(double factor)
{
    int n = assetPrices.historicalPrices.size();
    bool crossCondition = assetPrices.averages[n-1]>factor*upperBand[n-1];

    return crossCondition;
}

bool Bollingers::shouldSell(double factor)
{
    int n = assetPrices.historicalPrices.size();
    bool crossCondition = assetPrices.averages[n-1]<factor*upperBand[n-1];

    return crossCondition;
}
