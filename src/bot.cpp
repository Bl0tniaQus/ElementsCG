#include "bot.h"

Bot::Bot()
{
    this->testedOptions = 0;
    this->handOptions = new short [0];
    this->targetsForOptions = new short [0];
    this->handValues = new float [0];
}
void Bot::generateBaseGamestate(Duel* duel)
{
    this->baseGamestate = Gamestate(duel);
    this->baseGameStatevalue = this->baseGamestate.evaluate();
}
void Bot::generateTempGamestate(Duel* duel)
{
    this->tempGamestate = Gamestate(duel);
}
void Bot::testCardFromHand(short c)
{

    Gamestate* bGamestate = this->getBaseGamestate();
    this->generateTempGamestate(bGamestate);
    Gamestate* tGamestate = this->getTempGamestate();
    Player* player;
    Card* card;
    this->tested = -1;
    this->testing = true;
    this->generateTempGamestate(bGamestate);
    float value;
    float bValue = this->baseGameStatevalue;
    player = tGamestate->getPlayer(tGamestate->getTurnPlayer());
    card = player->getHand()[c];
    tGamestate->playFromHand(card);
    if (this->tested>0)
    {
        for (int i=0;i<this->n_choices;i++)
            {
                this->generateTempGamestate(bGamestate);
                player = tGamestate->getPlayer(tGamestate->getTurnPlayer());
                tGamestate->playFromHand(player->getHand()[c]);
                value = tGamestate->evaluate();
                this->saveOption(c,i,value);
            }
    }
    else
    {
        value = tGamestate->evaluate();
        this->saveOption(c,-1,value);
    }
    this->testing = false;
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


