#include "assetprices.h"
#include <vector>
#include <algorithm>

using namespace std;

AssetPrices::AssetPrices()
{
}

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
    for(int i = 0; i<period; i++)
    {
        averages[i] = 0.0;
        stdDeviations[i] = 0.0;
    }

    // compute at time >= period
    for(int i = 0; i < n-period; i++)
    {
        sum = std::accumulate(historicalPrices.begin()+ i, historicalPrices.begin()+i+period, 0.0);
        averages[i+period] = sum/period;

        sq_sum = 0.0;

        for(int j=i; j<i+period; j++)
        {
            sq_sum += (historicalPrices[j]-averages[i+period])*(historicalPrices[j]-averages[i+period]);
        }

        stdDeviations[i+period] = std::sqrt(sq_sum/period);
    }
}

