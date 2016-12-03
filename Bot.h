#ifndef BOT_H
#define BOT_H

#include <vector>
#include <map>

using namespace std;

enum method{MACD, Bollinger, Trends};

class Bot
{
    map<method, int> scores;

public:
    Bot(vector<method> methods);

    virtual void computeScores(vector<double>& prices);
    virtual method getBest();
    virtual void updateBase(vector<double>& prices);
};

#endif // BOT_H
