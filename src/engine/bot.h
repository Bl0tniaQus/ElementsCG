#ifndef BOT_H
#define BOT_H
#include "gamestate.h"

class Option
{
private:
    std::vector<int> cardIds;
    std::vector<std::vector<int>> targets;
    float value;
public:
    void setValue(float v) {this->value = v;}
    float getValue() {return this->value;}
    std::vector<int>* getCardIds(){return &this->cardIds;}
    std::vector<std::vector<int>>* getTargets(){return &this->targets;}
    Option() {this->cardIds = {}; this->targets = {}; this->value = 0;}
};


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
    std::vector<Option> options;
    Card* material1;
    Card* material2;
    Card* material3;
public:
    Bot();
    ~Bot();
    void generateBaseGamestate(Duel* duel);
    void generateTempGamestate(Duel* duel);
    Gamestate* getBaseGamestate() {return this->baseGamestate;}
    Gamestate* getTempGamestate() {return this->tempGamestate;}
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
    int getBestOption();
    int getOptionsNumber() {return this->options.size();}
    int getBestSingleTarget(Duel* duel);
    void endTesting();
    void playTurn(Duel* duel);
    Card* getFirstMaterial() {return this->material1;}
    Card* getSecondMaterial() {return this->material2;}
    Card* getThirdMaterial() {return this->material3;}
    //entity ids instead of array indices, test two card combos instead of single cards, do nothing if second card failed to find it's target
};
#endif // BOT_H
