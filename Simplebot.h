#ifndef SIMPLEBOT_H
#define SIMPLEBOT_H

#include <vector>
#include "Bot.h"

using namespace std;

class SimpleBot : public Bot
{
public:
    SimpleBot(vector<method> methods);
};

#endif // SIMPLEBOT_H
