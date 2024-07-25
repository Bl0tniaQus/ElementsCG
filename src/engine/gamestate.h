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
    void appendLog(std::string log, short log_source) override {};
};

#endif // GAMESTATE_H
