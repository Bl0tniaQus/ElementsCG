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
    int* handOptions;
    int* targetsForOptions;
    float* handValues;
    int* battleOptions;
    int* targetsForBattleOptions;
    float* battleValues;
    float* specialMinionValues;
    int* specialMinionOptions;
    int** specialMinionMaterials;
    short* materialNumbers;
    Card* material1;
    Card* material2;
    Card* material3;

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
    int* getHandOptions() {return this->handOptions;}
    float* getHandValues() {return this->handValues;}
    int* getTargetsForOptions() {return this->targetsForOptions;}
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
    short getSpecialMinionOptionsNumber() {return this->testedSpecialMinionOptions;}
    void testCardFromHand(int c, Duel* duel);
    void testCardBattle(short c, Duel* duel);
    void testHand(Duel* duel);
    void testSpecialMinions(Duel* duel);
    void testSpecialMinion(int c, Duel* duel);
    void testBattlePhase(Duel* duel);
    void conductBattlePhase(Duel* duel);
    void saveHandOption(int card, short target, float val);
    void saveSpecialMinionOption(int card, int material1, int material2, int material3, float val);
    void saveAttackOption(short card, short target, float val);
    short getBestTarget() {return this->targetsForOptions[this->bestOption];}
    short getBestCard() {return this->handOptions[this->bestOption];}
    short getBestSpecialMinion() {return this->specialMinionOptions[this->bestSpecialMinionOption];}
    float getBestHandValue() {return this->handValues[this->bestOption];}
    short getBestAttacker() {return this->battleOptions[this->bestAttackOption];};
    short getBestAttackTarget() {return this->targetsForBattleOptions[this->bestAttackOption];};
    float getBestAttackValue() {return this->battleValues[this->bestAttackOption];}
    void getBestOption();
    void getBestSpecialMinionOption();
    int* getBestMaterials();
    short getBestMaterialsNumber() {return this->materialNumbers[this->bestSpecialMinionOption];}
    float getBestSpecialMinionValue() {return this->specialMinionValues[this->bestSpecialMinionOption];}
    void getBestAttackOption();
    void endHandTesting();
    void endSpecialMinionTesting();
    void endBattleTesting();
    void playTurn(Duel* duel);
    Card* getFirstMaterial() {return this->material1;}
    Card* getSecondMaterial() {return this->material2;}
    Card* getThirdMaterial() {return this->material3;}
    //entity ids instead of array indices, test two card combos instead of single cards, do nothing if second card failed to find it's target
};
#endif // BOT_H
