#include "bollingers.h"

Bollingers::Bollingers(AssetPrices& _assetPrices)
{
    int n;
    assetPrices = _assetPrices;
    n = AssetPrices.size();
    upperBand.resize(n);
    lowerBand.resize(n);
}

void Bollingers::computeBands()
{
    assetPrices.ComputeAveragesAndStdDeviations();
    int n = AssetPrices.size();
    for(int i=0; i<n; i++)
    {
        double diff = 2*AssetPrices.stdDeviations[i];
        upperBand[i] = AssetPrices.averages[i]+diff;
        lowerBand[i] = AssetPrices.averages[i]-diff;
    }
}


bool Bollingers::shouldBuy(int observationPeriod, double factor)
{
    int n = assetPrices.size();
    bool crossCondition = assetPrices.averages[n-1]>factor*upperBand[n-1];

    return crossCondition;
}

bool Bollingers::shouldSell(int observationPeriod, double treshold)
{
    int n = assetPrices.size();
    bool crossCondition = assetPrices.averages[n-1]<factor*upperBand[n-1];

    return crossCondition;
}
