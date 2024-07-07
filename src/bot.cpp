#include "bot.h"
#include "card.h"
#include <iostream>
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
    this->baseGamestate->generateAttackersList();
    this->baseGamestate->generateDefendersList();
    this->baseGameStatevalue = this->baseGamestate->evaluate();
}
void Bot::generateTempGamestate(Duel* duel)
{
    delete this->tempGamestate;
    this->tempGamestate = new Gamestate(duel);
    this->tempGamestate->generateAttackersList();
    this->tempGamestate->generateDefendersList();
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
    float bValue = this->baseGamestate->evaluate();
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
                    std::cout<<"Whirlwind"<<std::endl;
                    value = this->tempGamestate->evaluate();
                    this->saveHandOption(c,i,value-bValue);
                }
            }
        }
        else
        {
            value = this->tempGamestate->evaluate();
            this->saveHandOption(c,-1,value-bValue);
        }
    }
    this->testing = false;
    this->testingTargets = false;
}
void Bot::saveHandOption(short card, short target, float val)
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
void Bot::saveAttackOption(short card, short target, float val)
{

    this->testedBattleOptions++;
    short *newBattleOptions = new short[this->testedBattleOptions];
    short *newBattleTargets = new short[this->testedBattleOptions];
    float *newBattleValues = new float[this->testedBattleOptions];
    if (this->testedBattleOptions>1)
    {
        for (int i=0;i<this->testedBattleOptions;i++)
        {
            newBattleOptions[i] = this->battleOptions[i];
            newBattleTargets[i] = this->targetsForBattleOptions[i];
            newBattleValues[i] = this->battleValues[i];
        }
            newBattleOptions[this->testedBattleOptions-1] = card;
            newBattleTargets[this->testedBattleOptions-1] = target;
            newBattleValues[this->testedBattleOptions-1] = val;
    }
    else
    {
            newBattleOptions[0] = card;
            newBattleTargets[0] = target;
            newBattleValues[0] = val;
    }
    delete[] this->battleOptions;
    delete[] this->targetsForBattleOptions;
    delete[] this->battleValues;
    this->battleOptions = newBattleOptions;
    this->targetsForBattleOptions = newBattleTargets;
    this->battleValues = newBattleValues;
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
void Bot::getBestAttackOption()
{
    if (this->testedBattleOptions>0)
    {
        float bestValue = this->battleValues[0];
        int bestOption = 0;
        for (int i=1;i<this->testedBattleOptions;i++)
        {
            if (this->battleValues[i]>bestValue)
            {
                bestValue = this->battleValues[i];
                bestOption = i;
            }
        }
        this->bestAttackOption = bestOption;
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
void Bot::endBattleTesting()
{
    delete [] this->battleValues;
    delete [] this->battleOptions;
    delete [] this->targetsForBattleOptions;
    this->battleOptions = new short [0];
    this->targetsForBattleOptions = new short [0];
    this->battleValues = new float [0];
    this->testedBattleOptions = 0;
}
void Bot::testCardBattle(short c, Duel* duel)
{
    std::cout<<"BATTLE BASE"<<std::endl;
    float bv = this->baseGamestate->evaluate();
    std::cout<<"BATTLE BASE END"<<std::endl;
    short n_defenders = this->baseGamestate->getDefendersList()->getTargetsNumber();
    for (int i=0;i<n_defenders;i++)
    {
        this->generateTempGamestate(duel);
        Card* attacker = this->tempGamestate->getAttackersList()->getTargetList()[c];
        Card* defender = this->tempGamestate->getDefendersList()->getTargetList()[i];

        this->tempGamestate->combat(attacker,defender);
        std::cout<<"BATTLE TEMP"<<std::endl;
        float v = this->tempGamestate->evaluate();
        std::cout<<"BATTLE TEMP END"<<std::endl;
        this->saveAttackOption(c,i,v-bv);
    }
    if (n_defenders == 0)
    {
        this->generateTempGamestate(duel);
        Card* attacker = this->tempGamestate->getAttackersList()->getTargetList()[c];
        this->tempGamestate->directAttack(attacker);
        float v = this->tempGamestate->evaluate();
        this->saveAttackOption(c,-1,v-bv);
    }
}
void Bot::testBattlePhase(Duel* duel)
{

    this->generateBaseGamestate(duel);

    short n_attackers = this->baseGamestate->getAttackersList()->getTargetsNumber();
    for (int i=0;i<n_attackers;i++)
    {
        this->testCardBattle(i, duel);
    }
}
void Bot::conductBattlePhase(Duel* duel)
{
    while(true)
    {
        std::cout<<"BATTLE"<<std::endl;
        this->generateBaseGamestate(duel);
        this->testBattlePhase(duel);
        if (this->testedBattleOptions==0) {this->endBattleTesting(); break;}
        else
        {
            this->getBestAttackOption();
            short atk = this->getBestAttacker();
            short target = this->getBestAttackTarget();
            float val = this->getBestAttackValue();
            if (val<0) {break;}
            duel->generateAttackersList();
            duel->generateDefendersList();
            Card* attacker = duel->getAttackersList()->getTargetList()[atk];
            if (target!=-1)
            {
                Card* defender = duel->getDefendersList()->getTargetList()[target];
                duel->combat(attacker,defender);
            }
            else
            {
                duel->directAttack(attacker);
            }
        }
        this->endBattleTesting();
    }
    std::cout<<"END_BATTLE"<<std::endl;
}




