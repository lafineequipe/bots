#ifndef BOT_H
#define BOT_H

#include <vector>
#include <map>
#include "algo.h"

using namespace std;

enum method{MACD, Bollinger, Trends};

class Bot
{
    map<method, int> scores;
    virtual void computeScores(vector<double>& prices);

public:
    Bot(vector<method> methods);
    virtual method getBest();
    virtual void updateBase(const Prices& prices, double yesterdayPrice, double todayPrice);
};

#endif // BOT_H
