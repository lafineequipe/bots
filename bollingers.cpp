#include <QDebug>
#include "bollingers.h"

Bollingers::Bollingers(const AssetPrices& _assetPrices, double factor)
    : assetPrices(_assetPrices),
      decisionFactor(factor)
{
}

void Bollingers::updateAssetPrices(const Prices& prices)
{
    assetPrices = AssetPrices(prices);
}

void Bollingers::computeBands(int period)
{
    assetPrices.ComputeAveragesAndStdDeviations(period);
    int n = assetPrices.historicalPrices.size();
    for(int i=0; i<n; i++)
    {
        double diff = 2*assetPrices.stdDeviations[i];
        upperBand[i] = assetPrices.averages[i]+diff;
        lowerBand[i] = assetPrices.averages[i]-diff;
    }
}

Action Bollingers::getNextAction(const Prices &prices, int period)
{
    int n;
    n = prices.size();

    upperBand.resize(n);
    lowerBand.resize(n);
    computeBands(period);
    n = assetPrices.historicalPrices.size();

    if (assetPrices.averages[n-1]>decisionFactor*upperBand[n-1])
        return Buy;

    if (decisionFactor*assetPrices.averages[n-1]<lowerBand[n-1])
        return Sell;

    return Nothing;
}
