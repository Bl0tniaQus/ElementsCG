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
    Option() {this->cardIds = std::vector<int>(0); this->targets = std::vector<std::vector<int>>(0); this->value = 0;}
    Option (Option& op1, Option& op2);
};


class Bot
{
private:
    short difficulty = 2;
    Gamestate* baseGamestate;
    Gamestate* tempGamestate;
    Gamestate* testingGamestate;
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
    int targetId = -1;

public:
    Bot();
    ~Bot();
    void generateBaseGamestate(Duel* duel);
    void generateTempGamestate(Duel* duel);
    void generateTestingGamestate(Duel* duel);
    Gamestate* getBaseGamestate() {return this->baseGamestate;}
    Gamestate* getTempGamestate() {return this->tempGamestate;}
    Gamestate* getTestingGamestate() {return this->testingGamestate;}
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
    void testCardFromHand(int c, Duel* duel, Option& option);
    void testCardBattle(short c, Duel* duel);
    void testOptionCombos(Duel* duel, short n);
    void testHand(Duel* duel);
    void testSpecialMinions(Duel* duel);
    void testSpecialMinion(int c, Duel* duel, Option& option);
    void testBattlePhase(Duel* duel);
    void conductBattlePhase(Duel* duel);
    void saveOption(Option& option);
    void saveAttackOption(short card, short target, float val);
    int getBestOption();
    int getOptionsNumber() {return this->options.size();}
    int getBestSingleTarget(Duel* duel);
    void endTesting();
    void playTurn(Duel* duel);
    void generateOptions(Duel* duel, Option& option);
    void optionGenerationThread(Duel* duel, std::vector<Option>& opts);
    Card* getFirstMaterial() {return this->material1;}
    Card* getSecondMaterial() {return this->material2;}
    Card* getThirdMaterial() {return this->material3;}
    int getTargetId() {return this->targetId;}
    void setTargetId(int id) {this->targetId = id;}
    void performAction(Duel* duel, Option& option, bool display = false);
    void toggleThinking(Duel* duel, bool v);
    void setDifficulty(short v) {this->difficulty = v;}
};
#endif // BOT_H
