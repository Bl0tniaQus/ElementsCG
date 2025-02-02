#include "bot.h"
#include "card.h"
#include <iostream>
#include <QDebug>
Bot::Bot()
{
    this->testedOptions = 0;
    this->testedSpecialMinionOptions = 0;
    this->handOptions = new int [0];
    this->targetsForOptions = new int [0];
    this->handValues = new float [0];
    this->battleOptions = new int [0];
    this->specialMinionMaterials = new int*[0];
    this->specialMinionOptions = new int[0];
    this->specialMinionValues = new float[0];
    this->materialNumbers = new short[0];
    this->targetsForBattleOptions = new int [0];
    this->battleValues = new float [0];
    this->baseGamestate = new Gamestate;
    this->tempGamestate = new Gamestate;
    this->material1 = nullptr;
    this->material2 = nullptr;
    this->material3 = nullptr;
}
Bot::~Bot()
{
    delete baseGamestate;
    delete tempGamestate;
    delete [] handOptions;
    delete [] targetsForOptions;
    delete [] handValues;
    delete [] this->battleValues;
    delete [] this->battleOptions;
    delete [] this->targetsForBattleOptions;
    delete[] this->specialMinionOptions;
    delete[] this->materialNumbers;
    delete[] this->specialMinionValues;
    for (int i=0; i<this->testedSpecialMinionOptions-1;i++)
    {
        delete[] this->specialMinionMaterials[i];
    }
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
void Bot::testCardFromHand(int c, Duel* duel)
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
    card = this->tempGamestate->getCardFromCopyId(c);
    if (card->getCost()<=player->getMana())
    {
        if (card->getCardType()==1 && !this->tempGamestate->canSummon(player)) {return;}
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
                    card = this->tempGamestate->getCardFromCopyId(c);
                    this->tempGamestate->playFromHand(card);
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
void Bot::testSpecialMinion(int c, Duel* duel)
{
    Player* player;
    Card* card;
    this->material1 = nullptr;
    this->material2 = nullptr;
    this->material3 = nullptr;
    this->generateTempGamestate(duel);
    this->testing = true;
    float value;
    float bValue = this->baseGamestate->evaluate();
    player = this->tempGamestate->getPlayer(this->tempGamestate->getTurnPlayer());
    card = this->tempGamestate->getCardFromCopyId(c);
    CardBase* cardBase = card->getCardName();

    if (!cardBase->checkSummoningConditions2(this->tempGamestate,card) && !cardBase->checkSummoningConditions3(this->tempGamestate,card)) {this->testing = false; return;}


    cardBase->getFirstMaterialList(this->tempGamestate,card);
    std::vector<Card*>* firstList = cardBase->getTargetList()->getTargetList();
    short firstN = cardBase->getTargetList()->getTargetsNumber();
    int* firstIds = new int[firstN];
    for (short i=0;i<firstN;i++)
    {
        firstIds[i] = firstList->at(i)->getCopyId();
    }


    cardBase->getSecondMaterialList(this->tempGamestate,card);
    std::vector<Card*>* secondList = cardBase->getTargetList()->getTargetList();
    short secondN = cardBase->getTargetList()->getTargetsNumber();
    int* secondIds = new int[secondN];
    for (short i=0;i<secondN;i++)
    {
        secondIds[i] = secondList->at(i)->getCopyId();
    }

    cardBase->getThirdMaterialList(this->tempGamestate,card);
    std::vector<Card*>* thirdList = cardBase->getTargetList()->getTargetList();
    short thirdN = cardBase->getTargetList()->getTargetsNumber();
    int* thirdIds = new int[thirdN];
    for (short i=0;i<thirdN;i++)
    {
        thirdIds[i] = thirdList->at(i)->getCopyId();
    }



    Card* cardA; Card* cardB; Card* cardC;
    if (cardBase->getMaterialNumber()==2)
    {

        for (short i = 0; i<firstN; i++)
        {
            for (short j = 0;j<secondN; j++)
            {
                this->generateTempGamestate(duel);
                cardA = this->tempGamestate->getCardFromCopyId(firstIds[i]);
                cardB = this->tempGamestate->getCardFromCopyId(secondIds[j]);

                if (cardA!=cardB)
                {
                    this->material1 = cardA;
                    this->material2 = cardB;
                    this->tempGamestate->summonSpecialMinion(this->tempGamestate->getCardFromCopyId(c));
                    value = this->tempGamestate->evaluate();
                    this->saveSpecialMinionOption(c,firstIds[i],secondIds[j],-1,value-bValue);
                }

            }
        }
    }
    delete[] firstIds;
    delete[] secondIds;
    delete[] thirdIds;
    this->material1 = nullptr;
    this->material2 = nullptr;
    this->material3 = nullptr;
}
void Bot::saveHandOption(int card, short target, float val)
{

    this->testedOptions++;
    int *newHandOptions = new int[this->testedOptions];
    int *newTargets = new int[this->testedOptions];
    float *newValues = new float[this->testedOptions];
    if (this->testedOptions>1)
    {
        for (int i=0;i<this->testedOptions-1;i++)
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
void Bot::saveSpecialMinionOption(int card, int material1, int material2, int material3, float val)
{

    this->testedSpecialMinionOptions++;
    short n_materials;
    if (material3==-1) {n_materials = 2;} else {n_materials = 3;}
    int *newSpecialMinionOptions = new int[this->testedSpecialMinionOptions];
    short *newMaterialNumbers = new short[this->testedSpecialMinionOptions];
    int **newMaterials = new int*[this->testedSpecialMinionOptions];
    float *newSpecialMinionValues = new float[this->testedSpecialMinionOptions];
    if (this->testedSpecialMinionOptions>1)
    {
        for (int i=0;i<this->testedSpecialMinionOptions-1;i++)
        {
            newSpecialMinionOptions[i] = this->specialMinionOptions[i];
            newMaterialNumbers[i] = this->materialNumbers[i];
            newMaterials[i] = new int[3];
            for (int j=0;j<3;j++)
            {
                newMaterials[i][j] = this->specialMinionMaterials[i][j];
            }
            newSpecialMinionValues[i] = this->specialMinionValues[i];
        }
            newSpecialMinionOptions[this->testedSpecialMinionOptions-1] = card;
            newMaterialNumbers[this->testedSpecialMinionOptions-1] = n_materials;
            newMaterials[this->testedSpecialMinionOptions-1] = new int[3];
            newMaterials[testedSpecialMinionOptions-1][0] = material1;
            newMaterials[testedSpecialMinionOptions-1][1] = material2;
            newMaterials[testedSpecialMinionOptions-1][2] = material3;
            newSpecialMinionValues[this->testedSpecialMinionOptions-1] = val;
    }
    else
    {
            newSpecialMinionOptions[0] = card;
            newMaterialNumbers[0] = n_materials;
            newMaterials[0] = new int[3];
            newMaterials[0][0] = material1;
            newMaterials[0][1] = material2;
            newMaterials[0][2] = material3;
            newSpecialMinionValues[0] = val;
    }
    delete[] this->specialMinionOptions;
    delete[] this->materialNumbers;
    delete[] this->specialMinionValues;
    for (int i=0; i<this->testedSpecialMinionOptions-1;i++)

    {
        delete[] this->specialMinionMaterials[i];
    }
    delete[] this->specialMinionMaterials;
    this->specialMinionOptions = newSpecialMinionOptions;
    this->materialNumbers = newMaterialNumbers;
    this->specialMinionMaterials = newMaterials;
    this->specialMinionValues = newSpecialMinionValues;
}
void Bot::saveAttackOption(short card, short target, float val)
{

    this->testedBattleOptions++;
    int *newBattleOptions = new int[this->testedBattleOptions];
    int *newBattleTargets = new int[this->testedBattleOptions];
    float *newBattleValues = new float[this->testedBattleOptions];
    if (this->testedBattleOptions>1)
    {
        for (int i=0;i<this->testedBattleOptions-1;i++)
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
void Bot::getBestSpecialMinionOption()
{
    if (this->testedSpecialMinionOptions>0)
    {
        float bestValue = this->specialMinionValues[0];
        int bestOption = 0;
        for (int i=1;i<this->testedSpecialMinionOptions;i++)
        {
            if (this->specialMinionValues[i]>bestValue)
            {
                bestValue = this->specialMinionValues[i];
                bestOption = i;
            }
        }
        this->bestSpecialMinionOption = bestOption;
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
    this->handOptions = new int [0];
    this->targetsForOptions = new int [0];
    this->handValues = new float [0];
    this->n_choices = 0;
    this->testing = false;
    this->testingTargets = false;
    this->testedOptions = 0;
    this->tested = -1;
}
void Bot::endSpecialMinionTesting()
{
    delete[] this->specialMinionOptions;
    delete[] this->materialNumbers;
    delete[] this->specialMinionValues;
    for (int i=0; i<this->testedSpecialMinionOptions-1;i++)

    {
        delete[] this->specialMinionMaterials[i];
    }
    delete[] this->specialMinionMaterials;
    this->specialMinionMaterials = new int*[0];
    this->specialMinionOptions = new int[0];
    this->specialMinionValues = new float[0];
    this->materialNumbers = new short[0];
    this->testing = false;
    this->testedSpecialMinionOptions=0;
}
void Bot::endBattleTesting()
{
    delete [] this->battleValues;
    delete [] this->battleOptions;
    delete [] this->targetsForBattleOptions;
    this->battleOptions = new int [0];
    this->targetsForBattleOptions = new int [0];
    this->battleValues = new float [0];
    this->testedBattleOptions = 0;
}
void Bot::testCardBattle(short c, Duel* duel)
{
    float bv = this->baseGamestate->evaluate();
    short n_defenders = this->baseGamestate->getDefendersList()->getTargetsNumber();
    for (int i=0;i<n_defenders;i++)
    {
        this->generateTempGamestate(duel);
        Card* attacker = this->tempGamestate->getAttackersList()->getTargetList()->at(c);
        Card* defender = this->tempGamestate->getDefendersList()->getTargetList()->at(i);

        this->tempGamestate->combat(attacker,defender);
        float v = this->tempGamestate->evaluate();
        this->saveAttackOption(c,i,v-bv);
    }
    if (n_defenders == 0)
    {
        this->generateTempGamestate(duel);
        Card* attacker = this->tempGamestate->getAttackersList()->getTargetList()->at(c);
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
        this->generateBaseGamestate(duel);
        this->testBattlePhase(duel);
        if (this->testedBattleOptions==0) { this->endBattleTesting(); break;}
        else
        {
            this->getBestAttackOption();
            short atk = this->getBestAttacker();
            short target = this->getBestAttackTarget();
            float val = this->getBestAttackValue();
            if (val<=0) {break;}
            duel->generateAttackersList();
            duel->generateDefendersList();
            Card* attacker = duel->getAttackersList()->getTargetList()->at(atk);
            if (target!=-1)
            {
                Card* defender = duel->getDefendersList()->getTargetList()->at(target);
                duel->combat(attacker,defender);
            }
            else
            {
                duel->directAttack(attacker);
            }
            duel->botDelay(600);
        }
        this->endBattleTesting();
        if (duel->getDuelEnded()) {return;}
    }
}
void Bot::testHand(Duel* duel)
{
    this->generateBaseGamestate(duel);
    Player* player = duel->getPlayer(duel->getTurnPlayer());
    short n_hand = player->getHandSize();
    for (int z = 0;z<n_hand;z++)
    {
        this->testCardFromHand(player->getHand()->at(z)->getCopyId(), duel);
    }
}
void Bot::testSpecialMinions(Duel* duel)
{
    this->generateBaseGamestate(duel);
    Player* player = duel->getPlayer(duel->getTurnPlayer());
    short n_special = player->getSpecialDeckSize();
    for (int z = 0;z<n_special;z++)
    {
        this->testSpecialMinion(player->getSpecialDeck()->at(z)->getCopyId(), duel);
    }
}
int* Bot::getBestMaterials()
{
    return this->specialMinionMaterials[this->bestSpecialMinionOption];
}
void Bot::playTurn(Duel* duel)
{
            int option,optionS;
            short n_hand;
            while (true)
            {
                Player* player = duel->getPlayer(duel->getTurnPlayer());
                this->testHand(duel);
                this->testSpecialMinions(duel);
                this->getBestOption();
                this->getBestSpecialMinionOption();
                n_hand = player->getHandSize();
                option = this->getBestCard();
                optionS = this->getBestSpecialMinion();
                if (this->getOptionsNumber()==0 && this->getSpecialMinionOptionsNumber()==0) { this->endHandTesting(); this->endSpecialMinionTesting(); break;}
                float val = this->getBestHandValue();
                float valS = this->getBestSpecialMinionValue();
                if (this->getOptionsNumber()==0)
                {
                    val = -100;
                }
                if (this->getSpecialMinionOptionsNumber()==0)
                {
                    valS = -100;
                }

                if (val<=0 && valS<=0) {this->endHandTesting(); break;}
                Card* card;
                if (valS >= val)
                {
                    card = duel->getCardFromCopyId(optionS);
                    this->testing = false;
                    this->testingTargets = false;
                    int* mats = this->getBestMaterials();
                    Card* a = duel->getCardFromCopyId(mats[0]);
                    Card* b = duel->getCardFromCopyId(mats[1]);
                    Card* c = nullptr;
                    if (this->getBestMaterialsNumber()==3)
                    { c = duel->getCardFromCopyId(mats[2]);}
                    this->material1 = a; this->material2 = b; this->material3 = c;
                    duel->summonSpecialMinion(card);
                    duel->botDelay(600);
                    this->material1 = nullptr; this->material2 = nullptr; this->material3 = nullptr;

                }
                else
                {
                    card = duel->getCardFromCopyId(option);
                    if (card->getPlace()==1) {
                    this->testing = false;
                    this->testingTargets = false;
                    duel->playFromHand(duel->getCardFromCopyId(option));
                    duel->botDelay(600);
                }
                }
                this->endHandTesting();
                this->endSpecialMinionTesting();
                if (duel->getDuelEnded())
                {
                    return;
                }
            }
            if (duel->getTurnCount()>1){this->conductBattlePhase(duel);}
            if (!duel->getDuelEnded()){duel->passTurn();}

}



