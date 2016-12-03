#include "assetprices.h"
#include <vector>
#include <algorithm>

using namespace std;

AssetPrices::AssetPrices(const Prices& _historicalPrices)
    : historicalPrices(_historicalPrices),
      averages(_historicalPrices.size()),
      stdDeviations(_historicalPrices.size())
{
}

void AssetPrices::ComputeAveragesAndStdDeviations()
{
    int n = historicalPrices.size();
    double sum;
    double sq_sum(n);

    //compute averages
    averages[0] = historicalPrices[0];
    stdDeviations[0] = 0.0;
    for(int i = 1; i<n; i++)
    {
        sum = std::accumulate(historicalPrices.begin(), historicalPrices.begin()+i, 0.0);
        averages[i] = sum/(i+1);

        for(int j=0; j<i; j++)
        {
            sq_sum = (historicalPrices[j]-averages[j])*(historicalPrices[j]-averages[j]);
        }

        stdDeviations[i] = sq_sum/(i+1);
    }
}

