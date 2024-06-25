#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "duel.h"
class Gamestate : public Duel
{
private:
    Player players[2]; //0 - player 1, 1 - player2
    short turnCount;
    char turnPlayer;
    TargetList targetList;
public:
    Gamestate();
    Gamestate(Duel* duel);
};

#endif // GAMESTATE_H
