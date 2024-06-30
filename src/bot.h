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
    Gamestate* getGamestate() {return &this->gamestate;}
};

#endif // BOT_H
