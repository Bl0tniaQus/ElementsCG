#ifndef DUEL_H
#define DUEL_H
#include "player.h"
#include "deck.h"
#include "targetlist.h"
#include "../ui/dueluibridge.h"

class Duel
{
private:
    Player players[2]; //0 - player 1, 1 - player2
    TargetList* attackersTargetList;
    TargetList* defendersTargetList;
    DuelUiBridge* uiBridge;
    short turnCount;
    unsigned char turnPlayer;
    short* logsSource;
    std::string* logs;
    int n_logs;
    bool duelEnded = false;
    Card** turnEndLingeringEffects;
    short n_lingering_end;
    Card** turnStartLingeringEffects;
    short n_lingering_start;
public:
    Duel();
    virtual ~Duel();
    short getTurnCount() {return this->turnCount;}
    void setTurnCount(short turnCount) {this->turnCount=turnCount;}
    unsigned char getTurnPlayer() {return this->turnPlayer;}
    void setTurnPlayer(char turnPlayer) {this->turnPlayer=turnPlayer;}
    Player* getPlayer(unsigned char p) {return &this->players[p];}
    void passTurn();
    short getPlayerId(Player* player);
    void drawField(char p);
    void drawCard(Player* player);
    void drawCardNoLog(Player* player);
    void combat(Card* attacker, Card* defender);
    void directAttack(Card* attacker);
    void destruction(Card* card);
    void releaseForSpecialSummon(Card* card, Card* sp_minion);
    void toHand(Card* card);
    void searchCard(Card* card);
    void toSpecialDeck(Card* card);
    void toGraveyard(Card* card);
    void removeFromField(Card* card);
    void checkWinner();
    bool getDuelEnded() {return this->duelEnded;}
    Card* getCardFromCopyId(int id);
    void setUiBridge(DuelUiBridge* bridge) {this->uiBridge = bridge;}
    DuelUiBridge* getUiBridge() {return this->uiBridge;}
    short getEmptyMinionZone(Player* player);
    void summonMinion(Card *minion, short zoneid);
    bool activateSpell(Card* spell);
    void playFromHand(Card* card);
    void summonFromHand(Card* minion, short zoneid);
    void summonFromGraveyard(Card* minion, short zoneid);
    void removeFromGraveyard(Card* card);
    void removeFromDeck(Card* card);
    bool onSpell(Card* card);
    void onSummon(Card* card);
    void onTurnEnd(Card* card);
    void onTurnStart(Card* card);
    void turnEndEffects();
    void turnStartEffects();
    void onDestroy(Card* card);
    void onCombat(Card* card);
    void updateBoard();
    void summonSpecialMinion(Card *minion);
    void DuelControl(Deck *deck0, Deck* deck1);
    void generateAttackersList();
    void generateDefendersList();
    bool canSummon(Player* player);
    void changeStats(Card* card, short a, short d);
    void changeLevel(Card* card, short l);
    void changeBarrier(Card* card, short b);
    void changeSpellImmunity(Card* card, bool si);
    void excavateCard(Card* card);
    void startDuel(Deck *deck0, Deck* deck1);
    short makeSpellChoice(Card* card);
    short makeSpecialMinionMaterialChoice(Card* card);
    void addTurnEndLingeringEffect(Card* card);
    void clearTurnEndLingeringEffects();
    void addTurnStartLingeringEffect(Card* card);
    void clearTurnStartLingeringEffects();
    virtual void appendLog(std::string log, short log_source);
    void turnStartLog();
    std::string* getLogs() {return this->logs;}
    short* getLogSources() {return this->logsSource;}
    int getLogsNumber() {return this->n_logs;}
    void botDelay(int ms);
    std::string cardFromHandLog(Card* card);
    std::string manaChangeLog(Player* player, short value);
    std::string lifeChangeLog(Player* player, short value);
    std::string drawCardLog(Player* player, short n);
    std::string barrierChangeLog(Card* card, short b);
    std::string destructionLog(Card* card);
    std::string summonLog(Card* card);
    std::string returnToHandLog(Card* card);
    std::string addToHandLog(Card* card);
    std::string attackLog(Card* attacker, Card* defender);
    std::string directAttackLog(Card* attacker);
    std::string statChangeLog(Card* card, short a_new, short d_new);
    std::string levelChangeLog(Card* card, short l);
    std::string excavateCardLog(Card* card);
    std::string spellImmunityChangeLog(Card* card, bool change);
    std::string spellImmunityMessageLog(Card* effect, Card* minion);
    std::string duelResultLog(short res);
    void appendSILog(Card* effect, Card* minion);
    void turnEndLog();
    TargetList* getAttackersList() {return this->attackersTargetList;}
    TargetList* getDefendersList() {return this->defendersTargetList;}
    virtual bool isCopy() {return false;}
    short getTurnStartLingeringEffectsNumber() {return this->n_lingering_start;}
    short getTurnEndLingeringEffectsNumber() {return this->n_lingering_end;}
    Card** getTurnEndLingeringEffects() {return this->turnEndLingeringEffects;}
    Card** getTurnStartLingeringEffects() {return this->turnStartLingeringEffects;}
};

#endif // DUEL_H
