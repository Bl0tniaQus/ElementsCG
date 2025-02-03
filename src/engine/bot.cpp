#include "bot.h"
#include "card.h"
#include <iostream>
#include <QDebug>

Option Option::combine(Option& op1, Option& op2)
{
    op1.setValue(op2.getValue());
    op1.getCardIds()->push_back(op2.getCardIds()->at(0));
    op1.getTargets()->push_back(op2.getTargets()->at(0));
    return op1;
}


Bot::Bot()
{
    this->options = {};
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
Option Bot::testCardFromHand(int c, Duel* duel)
{
    Option option;
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
        if (card->getCardType()==1 && !this->tempGamestate->canSummon(player)) {return option;}
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
                    option.setValue(value - bValue);
                    option.getCardIds()->push_back(c);
                    option.getTargets()->push_back({i});
                }
            }
        }
        else
        {
            value = this->tempGamestate->evaluate();
            option.getCardIds()->push_back(c);
            option.getTargets()->push_back({-1});
            option.setValue(value - bValue);
        }
    }
    this->testing = false;
    this->testingTargets = false;
    return option;
}
Option Bot::testSpecialMinion(int c, Duel* duel)
{
    Option option;
    Player* player;
    Card* card;
    Card* material1 = nullptr;
    Card* material2 = nullptr;
    Card* material3 = nullptr;
    this->generateTempGamestate(duel);
    this->testing = true;
    float value;
    float bValue = this->baseGamestate->evaluate();
    player = this->tempGamestate->getPlayer(this->tempGamestate->getTurnPlayer());
    card = this->tempGamestate->getCardFromCopyId(c);
    CardBase* cardBase = card->getCardName();

    if (!cardBase->checkSummoningConditions2(this->tempGamestate,card) && !cardBase->checkSummoningConditions3(this->tempGamestate,card)) {this->testing = false; return option;}


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
    if (cardBase->getRequiredMaterialsNumber()==2)
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
                    option.setValue(value-bValue);
                    option.getTargets()->push_back({firstIds[i],secondIds[j]});
                    option.getCardIds()->push_back(c);
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
    return option;
}
void Bot::saveOption(Option& option)
{
    if (option.getCardIds()->size()>0)
        this->options.push_back(option);
}
void Bot::saveAttackOption(short card, short target, float val)
{
    Option option;
    option.getCardIds()->push_back(card);
    option.getTargets()->push_back({target});
    option.setValue(val);
    this->options.push_back(option);
}
int Bot::getBestOption()
{
    int n = this->options.size();
    int bestOption = -1;
    if (n>0)
    {
        float bestValue = this->options[0].getValue();
        bestOption = 0;
        for (int i=1;i<n;i++)
        {
            if (this->options[i].getValue()>bestValue)
            {
                bestValue = this->options[i].getValue();
                bestOption = i;
            }
        }
    }
    return bestOption;
}
int Bot::getBestSingleTarget(Duel* duel)
{
    int option = this->getBestOption();
    if (option!=-1)
    {
        int cardId = this->options[option].getCardIds()->at(0);
        Card* card;
        card = duel->getCardFromCopyId(cardId);
        short place = card->getPlace();
        if (place==1)
        {
            return this->options[option].getTargets()->at(0)[0];
        }
    }
    return -1;
}

void Bot::endTesting()
{
    this->options.clear();
    this->n_choices = 0;
    this->testing = false;
    this->testingTargets = false;
    this->tested = -1;
    this->material1 = nullptr;
    this->material2 = nullptr;
    this->material3 = nullptr;
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
        this->saveAttackOption(attacker->getCopyId(),defender->getCopyId(),v-bv);
    }
    if (n_defenders == 0)
    {
        this->generateTempGamestate(duel);
        Card* attacker = this->tempGamestate->getAttackersList()->getTargetList()->at(c);
        this->tempGamestate->directAttack(attacker);
        float v = this->tempGamestate->evaluate();
        this->saveAttackOption(attacker->getCopyId(),-1,v-bv);
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
        int n_options = this->getOptionsNumber();
        if (n_options==0) { this->endTesting(); break;}
        else
        {
            int option = this->getBestOption();
            float val = this->options[option].getValue();
            int cardId = this->options[option].getCardIds()->at(0);
            int target = this->options[option].getTargets()->at(0)[0];
            if (val<=0) {break;}
            duel->generateAttackersList();
            duel->generateDefendersList();
            Card* attacker = duel->getCardFromCopyId(cardId);
            if (target!=-1)
            {
                Card* defender = duel->getCardFromCopyId(target);
                duel->combat(attacker,defender);
            }
            else
            {
                duel->directAttack(attacker);
            }
            duel->botDelay(600);
        }
        this->endTesting();
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
        Option option = this->testCardFromHand(player->getHand()->at(z)->getCopyId(), duel);
        this->saveOption(option);
    }
}
void Bot::testSpecialMinions(Duel* duel)
{
    this->generateBaseGamestate(duel);
    Player* player = duel->getPlayer(duel->getTurnPlayer());
    short n_special = player->getSpecialDeckSize();
    for (int z = 0;z<n_special;z++)
    {
        Option option = this->testSpecialMinion(player->getSpecialDeck()->at(z)->getCopyId(), duel);
        this->saveOption(option);
    }
}
void Bot::playTurn(Duel* duel)
{
            while (true)
            {
                Player* player = duel->getPlayer(duel->getTurnPlayer());
                this->testHand(duel);
                this->testSpecialMinions(duel);
                int n_options = this->getOptionsNumber();
                if (n_options==0) { this->endTesting(); break;}
                int option = this->getBestOption();
                float val = this->options[option].getValue();
                int cardId = this->options[option].getCardIds()->at(0);
                if (val<=0) {this->endTesting(); break;}
                Card* card;
                card = duel->getCardFromCopyId(cardId);
                short place = card->getPlace();
                if (place == 4)
                {
                    card = duel->getCardFromCopyId(cardId);
                    this->testing = false;
                    this->testingTargets = false;
                    std::vector<int> materials(this->options[option].getTargets()->at(0));
                    Card* a = duel->getCardFromCopyId(materials[0]);
                    Card* b = duel->getCardFromCopyId(materials[1]);
                    Card* c = nullptr;
                    if (materials.size()==3)
                    { c = duel->getCardFromCopyId(materials[2]);}
                    this->material1 = a; this->material2 = b; this->material3 = c;
                    duel->summonSpecialMinion(card);
                    duel->botDelay(600);
                    this->material1 = nullptr; this->material2 = nullptr; this->material3 = nullptr;

                }
                else
                {
                    card = duel->getCardFromCopyId(cardId);
                    if (card->getPlace()==1) {
                    this->testing = false;
                    this->testingTargets = false;
                    duel->playFromHand(card);
                    duel->botDelay(600);
                }
                }
                this->endTesting();
                if (duel->getDuelEnded())
                {
                    return;
                }
            }
            if (duel->getTurnCount()>1){this->conductBattlePhase(duel);}
            if (!duel->getDuelEnded()){duel->passTurn();}

}



