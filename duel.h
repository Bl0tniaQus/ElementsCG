#ifndef DUEL_H
#define DUEL_H
#include "player.h"
#include "deck.h"
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
    void setTurnCount(short turnCount) {this->turnCount=turnCount;}
    char getTurnPlayer() {return this->turnPlayer;}
    void setTurnPlayer(char turnPlayer) {this->turnPlayer=turnPlayer;}
    Player* getPlayer(char p) {return &this->players[p];}
    void passTurn();
    void drawField(char p);
    void drawCard(Player* player);
    void combat(Card* attacker, Card* defender);
    void directAttack(Card* attacker);
    void destruction(Card* card);
    void toHand(Card* card);
    void toSpecialDeck(Card* card);
    void toGraveyard(Card* card);
    void removeFromField(Card* card);
    void checkWinner();
    short getEmptyMinionZone(Player* player);
    void summonMinion(Card *minion, short zoneid);
    void activateSpell(Card* spell, short zoneid);
    void playFromHand(Card* card);
    void summonFromHand(Card* minion, short zoneid);
    void onSpell(Card* card, short zoneid);
    void onSummon(Card* card, short zoneid);
    void onTurnEnd(Card* card);
    void onDestroy(Card* card);
    void onCombat(Card* card);
    void applyContinuous();
    void generateTargetList(Card* effect);
    void generateSpecialMinionMaterialList(Card* servant, short n);
    void setTargetList(Card** targets, short n_targets);
    TargetList getTargetList() {return this->targetList;}
    bool checkEffectRequirements(Card* card);
    void summonSpecialMinion(Card *minion);
    void DuelControl(Deck *deck0, Deck* deck1);
    static Card* selectFieldTarget();
};

#endif // DUEL_H
