#include <QDebug>
#include "bollingers.h"

Bollingers::Bollingers(const AssetPrices& _assetPrices, double factor)
    : assetPrices(_assetPrices),
      decisionFactor(factor)
{
    int n;
    n = assetPrices.historicalPrices.size();
    upperBand.resize(n);
    lowerBand.resize(n);
    computeBands();
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

Action Bollingers::getNextAction(const Prices &prices)
{
    int n = assetPrices.historicalPrices.size();

    if (assetPrices.averages[n-1]>decisionFactor*upperBand[n-1])
        return Buy;

    if (decisionFactor*assetPrices.averages[n-1]<lowerBand[n-1])
        return Sell;

    return Nothing;
}
