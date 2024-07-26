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
    unsigned char lastSource;
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
    void combat(Card* attacker, Card* defender);
    void directAttack(Card* attacker);
    void destruction(Card* card);
    void toHand(Card* card);
    void toSpecialDeck(Card* card);
    void toGraveyard(Card* card);
    void removeFromField(Card* card);
    void checkWinner();
    void setUiBridge(DuelUiBridge* bridge) {this->uiBridge = bridge;}
    short getEmptyMinionZone(Player* player);
    void summonMinion(Card *minion, short zoneid);
    bool activateSpell(Card* spell);
    void playFromHand(Card* card);
    void summonFromHand(Card* minion, short zoneid);
    bool onSpell(Card* card);
    void onSummon(Card* card);
    void onTurnEnd(Card* card);
    void onTurnStart(Card* card);
    void turnEndEffects();
    void turnStartEffects();
    void onDestroy(Card* card);
    void onCombat(Card* card);
    void summonSpecialMinion(Card *minion);
    void DuelControl(Deck *deck0, Deck* deck1);
    void generateAttackersList();
    void generateDefendersList();

    void startDuel(Deck *deck0, Deck* deck1);
    short makeSpellChoice(Card* card);
    short makeSpecialMinionMaterialChoice(Card* card);

    virtual void appendLog(std::string log, short log_source);
    void turnStartLog();
    std::string* getLogs() {return this->logs;}
    short* getLogSources() {return this->logsSource;}
    int getLogsNumber() {return this->n_logs;}
    std::string cardFromHandLog(Card* card);
    std::string manaChangeLog(Player* player, short value);
    std::string lifeChangeLog(Player* player, short value);
    std::string drawCardLog(Player* player, short n);
    std::string summonLog(Card* card);
    std::string returnToHandLog(Card* card);
    std::string attackLog(Card* attacker, Card* defender);
    std::string directAttackLog(Card* attacker);
    void turnEndLog();
    unsigned char getLastSource() {return this->lastSource;}
    void setLastSource(unsigned char s) {this->lastSource = s;}


    TargetList* getAttackersList() {return this->attackersTargetList;}
    TargetList* getDefendersList() {return this->defendersTargetList;}
    virtual bool isCopy() {return false;}
};

#endif // DUEL_H
