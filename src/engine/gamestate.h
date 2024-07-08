#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "duel.h"
class Gamestate : public Duel
{
private:
public:
    Gamestate();
    Gamestate(Duel* duel);
    bool isCopy() override {return true;}
    float evaluate();
    float resourceFactor();
    float cardAdvantageFactor();
    float fieldPresenceFactor();
};

#endif // GAMESTATE_H
