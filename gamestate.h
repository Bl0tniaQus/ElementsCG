#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "duel.h"

class Gamestate : Duel
{
public:
    Gamestate();
    Gamestate(Duel* duel);
};

#endif // GAMESTATE_H
