#include "assetprices.h"
#include <vector>
#include <algorithm>

using namespace std;

AssetPrices::AssetPrices()
{
}

AssetPrices::AssetPrices(const vector<double>& _historicalPrices)
{
    int n = historicalPrices.size();
    historicalPrices = _historicalPrices;

    averages.resize(n);
    stdDeviations.resize(n);
}

double AssetPrices::ComputeAveragesAndStdDeviations()
{
    int n = historicalValues.size();
    double sum;
    double sq_sum(n);

    //compute averages
    averages[0] = historicalValues[0];
    stdDeviations[0] = 0.0;
    for(int i = 1; i<n; i++)
    {
        sum = std::accumulate(historicalPrices.begin(), historicalValues.begin()+i, 0.0);
        averages[i] = sum/(i+1);

        for(int j=0; j<i; j++)
        {
            sq_sum = (historicalPrices[j]-averages[j])*(historicalPrices[j]-averages[j]);
        }

        stdDeviations[i] = sq_sum/(i+1);
    }
}

