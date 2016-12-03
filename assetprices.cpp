#include "assetprices.h"
#include <vector>
#include <algorithm>

using namespace std;

AssetPrices::AssetPrices(const Prices& _historicalPrices): historicalPrices(_historicalPrices)
{
}

void AssetPrices::ComputeAveragesAndStdDeviations(int period)
{
    int n = historicalPrices.size();
    averages.resize(n);
    stdDeviations.resize(n);
    double sum;
    double sq_sum(n);

    //compute for time t<period
    for(int i = 1; i<period; i++)
    {
        averages[i] = 0.0;
        stdDeviations[i] = 0.0;
    }

    // compute at time >= period
    for(int i = 1; i<n-1-period; i++)
    {
        sum = std::accumulate(historicalPrices.begin()+ i, historicalPrices.begin()+i+period-1, 0.0);
        averages[i+period-1] = sum/period;

        for(int j=i; j<i+period; j++)
        {
            sq_sum = (historicalPrices[j]-averages[i+period-1])*(historicalPrices[j]-averages[i+period-1]);
            stdDeviations[i+period-1] = sq_sum/period;
        }
    }
}

