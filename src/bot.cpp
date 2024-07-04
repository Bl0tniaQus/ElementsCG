#include "bot.h"
#include "card.h"
Bot::Bot()
{
    this->testedOptions = 0;
    this->handOptions = new short [0];
    this->targetsForOptions = new short [0];
    this->handValues = new float [0];
    this->battleOptions = new short [0];
    this->targetsForBattleOptions = new short [0];
    this->battleValues = new float [0];
    this->baseGamestate = new Gamestate;
    this->tempGamestate = new Gamestate;
}
Bot::~Bot()
{
    delete baseGamestate;
    delete tempGamestate;
    delete [] handOptions;
    delete [] targetsForOptions;
    delete [] handValues;
}
void Bot::generateBaseGamestate(Duel* duel)
{
    delete this->baseGamestate;
    this->baseGamestate = new Gamestate(duel);
    this->baseGameStatevalue = this->baseGamestate->evaluate();
}
void Bot::generateTempGamestate(Duel* duel)
{
    delete this->tempGamestate;
    this->tempGamestate = new Gamestate(duel);
}
void Bot::testCardFromHand(short c, Duel* duel)
{
    Player* player;
    Card* card;
    this->generateTempGamestate(duel);
    this->tested = -1;
    this->n_choices = 0;
    this->testing = true;
    this->testingTargets = false;
    float value;
    float bValue = this->baseGameStatevalue;
    player = this->tempGamestate->getPlayer(this->tempGamestate->getTurnPlayer());
    card = player->getHand()[c];
    if ((card->getCost()<=player->getMana())||(card->getCardType()==1&&this->tempGamestate->getEmptyMinionZone(player)!=-1)) {
        this->tempGamestate->playFromHand(card);
        if (this->testingTargets)
        {
            if (this->n_choices!=0)
            {
            for (int i=0;i<this->n_choices;i++)
                {
                    this->tested = i;
                    this->generateTempGamestate(duel);
                    player = this->tempGamestate->getPlayer(this->tempGamestate->getTurnPlayer());
                    this->tempGamestate->playFromHand(player->getHand()[c]);
                    value = this->tempGamestate->evaluate();
                    this->saveOption(c,i,value);
                }
            }
        }
        else
        {
            value = this->tempGamestate->evaluate();
            this->saveOption(c,-1,bValue-value);
        }
    }
    this->testing = false;
    this->testingTargets = false;
}
void Bot::saveOption(short card, short target, float val)
{

    this->testedOptions++;
    short *newHandOptions = new short[this->testedOptions];
    short *newTargets = new short[this->testedOptions];
    float *newValues = new float[this->testedOptions];
    if (this->testedOptions>1)
    {
        for (int i=0;i<this->testedOptions;i++)
        {
            newHandOptions[i] = this->handOptions[i];
            newTargets[i] = this->targetsForOptions[i];
            newValues[i] = this->handValues[i];
        }
            newHandOptions[this->testedOptions-1] = card;
            newTargets[this->testedOptions-1] = target;
            newValues[this->testedOptions-1] = val;
    }
    else
    {
            newHandOptions[0] = card;
            newTargets[0] = target;
            newValues[0] = val;
    }
    delete[] this->handOptions;
    delete[] this->targetsForOptions;
    delete[] this->handValues;
    this->handOptions = newHandOptions;
    this->targetsForOptions = newTargets;
    this->handValues = newValues;
}
void Bot::getBestOption()
{
    if (this->testedOptions>0)
    {
        float bestValue = this->handValues[0];
        int bestOption = 0;
        for (int i=1;i<this->testedOptions;i++)
        {
            if (this->handValues[i]>bestValue)
            {
                bestValue = this->handValues[i];
                bestOption = i;
            }
        }
        this->bestOption = bestOption;
    }
}
void Bot::endHandTesting()
{
    delete [] this->handValues;
    delete [] this->handOptions;
    delete [] this->targetsForOptions;
    this->handOptions = new short [0];
    this->targetsForOptions = new short [0];
    this->handValues = new float [0];
    this->n_choices = 0;
    this->testing = false;
    this->testingTargets = false;
    this->testedOptions = 0;
    this->tested = -1;
}
void Bot::testBattle(short c, Duel* duel)
{
    this->generateTempGamestate(duel);
    Player* attacker = this->tempGamestate->getPlayer(this->tempGamestate->getTurnPlayer());
    Player* defender = attacker->getOpponent();
    Card** attackers = this->tempGamestate->getAttackersList()->getTargetList();
    short n_attackers = this->tempGamestate->getAttackersList()->getTargetsNumber();
    Card** defenders = this->tempGamestate->getDefendersList()->getTargetList();
    short n_defenders = this->tempGamestate->getDefendersList()->getTargetsNumber();

}



