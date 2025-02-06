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
    float evaluate(Player* player);
    float resourceFactor(Player* player);
    float cardAdvantageFactor(Player* player);
    float fieldPresenceFactor(Player* player);
    void appendLog(std::string log, short log_source) override {};
};

#endif // GAMESTATE_H
