#ifndef DUEL_H
#define DUEL_H
#include "player.h"
#include "targetlist.h"
class Duel
{
private:
    Player players[2]; //0 - player 1, 1 - player2
    short turnCount;
    char turnPlayer;
    TargetList targetList;
public:
    Duel();
    short getTurnCount() {return this->turnCount;}
    char getTurnPlayer() {return this->turnPlayer;}
    Player* getPlayer(char p) {return &this->players[p];}
    void passTurn() {this->turnPlayer = !this->turnPlayer;}
    void drawField(char p);
    void drawCard(char p);
    void combat(Card* attacker, Card* defender);
    void directAttack(Card* attacker);
    void destruction(Card* card);
    void toHand(Card* card);
    void checkWinner();
    short getEmptyMinionZone(Player* player);
    short getEmptySpellZone(Player* player);
    void summonMinion(Card *minion, short zoneid);
    void activateSpell(Card* spell, short zoneid);
    void playFromHand(Card* card);
    void summonFromhand(Card* minion, short zoneid);
    void onSpell(Card* card, short zoneid);
    void onSummon(Card* card) {};
    void onTurnEnd(Card* card);
    void onDestroy(Card* card);
    void onCombat(Card* card);
    void applyContinuous();
    void generateTargetList(Card* effect);
    void setTargetList(Card** targets, short n_targets);
    TargetList getTargetList() {return this->targetList;}
    bool checkEffectRequirements(Card* card);

    static Card* selectFieldTarget();
};

#endif // DUEL_H
