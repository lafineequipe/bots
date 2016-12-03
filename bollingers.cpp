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

bool Bollingers::shouldBuy()
{
    static int count = 0;

    int n = assetPrices.historicalPrices.size();
    bool crossCondition = assetPrices.averages[n-1]>decisionFactor*upperBand[n-1];

    if (crossCondition)
        qDebug() << "Buy";

    ++count;

    if (count == 200)
    {
        for (int i = 0; i < n; ++i)
            qDebug() << lowerBand[i] << assetPrices.averages[i] << upperBand[i];
    }

    return crossCondition;
}

bool Bollingers::shouldSell()
{
    int n = assetPrices.historicalPrices.size();
    bool crossCondition = decisionFactor*assetPrices.averages[n-1]<lowerBand[n-1];

    if (crossCondition)
        qDebug() << "Sell";

    return crossCondition;
}
