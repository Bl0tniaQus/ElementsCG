#ifndef EFFECTHANDLER_H
#define EFFECTHANDLER_H
#include "lingeringeffect.h"
#include "card.h"
class Duel;
class EffectHandler
{
private:
    LingeringEffect* lingeringEffects;
    short n_lingering;
public:
    EffectHandler();
    void onSpell(Card* card);
    void onSummon(Card* card);
    void onTurnEnd(Card* card);
    void onDestroy(Card* card);
    void onCombat(Card* card);
    void applyContinuous();

};

#endif // EFFECTHANDLER_H
