#ifndef BOT_H
#define BOT_H
#include "gamestate.h"
class Bot
{
private:
    Gamestate* baseGamestate;
    Gamestate* tempGamestate;
    short chosenSingleTarget = -1;
    short n_choices;
    short tested;
    short testedHand;
    bool testing;
    float baseGameStatevalue;
    bool testingTargets;
    short* handOptions;
    short* targetsForOptions;
    float* handValues;
    short* battleOptions;
    short* targetsForBattleOptions;
    float* battleValues;

    short* specialMinionOptions;
    short** specialMinionMaterials;


    int testedOptions;
    int testedBattleOptions;
    int testedSpecialMinionOptions;
    int bestOption;
    int bestAttackOption;
    int bestSpecialMinionOption;
public:
    Bot();
    ~Bot();
    void generateBaseGamestate(Duel* duel);
    void generateTempGamestate(Duel* duel);
    Gamestate* getBaseGamestate() {return this->baseGamestate;}
    Gamestate* getTempGamestate() {return this->tempGamestate;}
    short* getHandOptions() {return this->handOptions;}
    float* getHandValues() {return this->handValues;}
    short* getTargetsForOptions() {return this->targetsForOptions;}
    void setChosenSingleTarget(short x) {this->chosenSingleTarget = x;}
    short getChosenSingleTarget() {return this->chosenSingleTarget;}
    void setChoicesNumber(short n) {this->n_choices = n;}
    short getChoicesNumber() {return this->n_choices;}
    void setTestedNumber(short n) {this->tested = n;}
    short getTestedNumber() {return this->tested;}
    void setTestedHandNumber(short n) {this->testedHand = n;}
    short getTestedHandNumber() {return this->testedHand;}
    void setTesting(bool t) {this->testing = t;}
    bool isTesting() {return this->testing;}
    void setTargetTesting(bool tt) {this->testingTargets = tt;}
    bool isTestingTargets() {return this->testingTargets;}
    short getOptionsNumber() {return this->testedOptions;}
    void testCardFromHand(short c, Duel* duel);
    void testCardBattle(short c, Duel* duel);
    void testHand(Duel* duel);
    void testSpecialMinions();
    void testBattlePhase(Duel* duel);
    void conductBattlePhase(Duel* duel);
    void saveHandOption(short card, short target, float val);
    void saveAttackOption(short card, short target, float val);
    short getBestTarget() {return this->targetsForOptions[this->bestOption];}
    short getBestCard() {return this->handOptions[this->bestOption];}
    float getBestHandValue() {return this->handValues[this->bestOption];}
    short getBestAttacker() {return this->battleOptions[this->bestAttackOption];};
    short getBestAttackTarget() {return this->targetsForBattleOptions[this->bestAttackOption];};
    float getBestAttackValue() {return this->battleValues[this->bestAttackOption];}
    void getBestOption();
    void getBestAttackOption();
    void endHandTesting();
    void endBattleTesting();
    void playTurn(Duel* duel);
};
#endif // BOT_H
