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
    int testedOptions;
    int bestOption;
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
    void saveOption(short card, short target, float val);
    short getBestTarget() {return this->targetsForOptions[this->bestOption];}
    short getBestCard() {return this->handOptions[this->bestOption];}
    void getBestOption();
};
// steruj z poziomu tej klasy wyborami
//dla każdej karty trzymaj licznik, które opcje są już sprawdzone, funkcja CardBase::singleChoice() w fazie testowania zwróci kolejny niesprawdzony cel i aktywuje efekt na tym celu na tymczasowym gameState, dla którego zostanie wyliczony współczynnik. Bot będzie przechowywał najlepszą wartość współczynnika wsp = (evaluate(temp) - evaluate(base)) i dla jakiej kominacji karta - cel został uzyskany. Po sprawdzeniu wszystkich opcji wywoła zwróci najlepszą wybraną opcję do Duel i aktywuje efekt na głównym kontrolerze gry
#endif // BOT_H
