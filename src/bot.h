#ifndef BOT_H
#define BOT_H
#include "gamestate.h"
class Bot
{
private:
    Gamestate baseGamestate;
    Gamestate tempGamestate;
    short chosenSingleTarget = -1;
    short n_choices;
    short tested;
    bool testing;
public:
    Bot();
    void generateBaseGamestate(Duel* duel);
    void generateTempGamestate(Duel* duel);
    Gamestate* getBaseGamestate() {return &this->baseGamestate;}
    Gamestate* getTempGamestate() {return &this->tempGamestate;}
    void setChosenSingleTarget(short x) {this->chosenSingleTarget = x;}
    short getChosenSingleTarget() {return this->chosenSingleTarget;}
    void setTesting(bool t) {this->testing = t;}
    bool isTesting() {return this->testing;}
};
// steruj z poziomu tej klasy wyborami
//dla każdej karty trzymaj licznik, które opcje są już sprawdzone, funkcja CardBase::singleChoice() w fazie testowania zwróci kolejny niesprawdzony cel i aktywuje efekt na tym celu na tymczasowym gameState, dla którego zostanie wyliczony współczynnik. Bot będzie przechowywał najlepszą wartość współczynnika wsp = (evaluate(temp) - evaluate(base)) i dla jakiej kominacji karta - cel został uzyskany. Po sprawdzeniu wszystkich opcji wywoła zwróci najlepszą wybraną opcję do Duel i aktywuje efekt na głównym kontrolerze gry
#endif // BOT_H
