#include <QDebug>
#include "bollingers.h"

Bollingers::Bollingers(double factor, int period)
    : decisionFactor(factor),
      period(period)
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
        double diff = 2.0 * assetPrices.stdDeviations[i];
        upperBand[i] = assetPrices.averages[i]+diff;
        lowerBand[i] = assetPrices.averages[i]-diff;
    }
}

Action Bollingers::getNextAction(const Prices &prices)
{
    assetPrices = AssetPrices(prices);

    int n;
    n = prices.size();

    upperBand.resize(n);
    lowerBand.resize(n);
    computeBands(period);

    if (prices[n-1]>decisionFactor*upperBand[n-1])
        return Sell;

    if (decisionFactor*prices[n-1]<lowerBand[n-1])
        return Buy;

    return Nothing;
}
