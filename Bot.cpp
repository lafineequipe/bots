#include "Bot.h"

Bot::Bot(vector<method> methods)
{
    int i;
    int n = methods.size();

    for(i = 0; i< n; i++)
    {
        scores[methods[i]] = 0;
    }
}
