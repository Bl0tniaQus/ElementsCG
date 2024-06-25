#ifndef BOT_H
#define BOT_H
#include "gamestate.h"
class Bot
{
private:
    Gamestate gamestate;
public:
    Bot();
    void generateGamestate(Duel* duel);
};

#endif // BOT_H
