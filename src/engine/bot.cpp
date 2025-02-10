#include "bot.h"
#include "card.h"
#include <iostream>
#include <QDebug>

Option::Option(Option& op1, Option& op2)
{
    this->cardIds = std::vector<int>(0);
    this->targets = std::vector<std::vector<int>>(0);
    for (int i : *op1.getCardIds())
    {
        this->cardIds.push_back(i);
    }
    for (int i : *op2.getCardIds())
    {
        this->cardIds.push_back(i);
    }
    for (short i = 0; i< op1.getTargets()->size(); i++)
    {
        std::vector<int>v = std::vector<int>(0);
        for (short j = 0; j<op1.getTargets()->at(i).size(); j++)
        {
            v.push_back(op1.getTargets()->at(i)[j]);
        }
        this->targets.push_back(v);
    }
    for (short i = 0; i< op2.getTargets()->size(); i++)
    {
        std::vector<int>v = std::vector<int>(0);
        for (short j = 0; j<op2.getTargets()->at(i).size(); j++)
        {
            v.push_back(op2.getTargets()->at(i)[j]);
        }
        this->targets.push_back(v);
    }
    this->value = op2.getValue();
}


Bot::Bot()
{
    this->options = {};
    this->baseGamestate = new Gamestate;
    this->tempGamestate = new Gamestate;
    this->testingGamestate = new Gamestate;
    this->material1 = nullptr;
    this->material2 = nullptr;
    this->material3 = nullptr;
}
Bot::~Bot()
{
    delete baseGamestate;
    delete tempGamestate;
    delete testingGamestate;
}
void Bot::generateBaseGamestate(Duel* duel)
{
    delete this->baseGamestate;
    this->baseGamestate = new Gamestate(duel);
    this->baseGameStatevalue = this->baseGamestate->evaluate(this->baseGamestate->getPlayer(this->baseGamestate->getTurnPlayer()));
}
void Bot::generateTestingGamestate(Duel* duel)
{
    delete this->testingGamestate;
    this->testingGamestate = new Gamestate(duel);
}
void Bot::generateTempGamestate(Duel* duel)
{
    delete this->tempGamestate;
    this->tempGamestate = new Gamestate(duel);

}
void Bot::testCardFromHand(int c, Duel* duel, Option& option)
{

    Player* player;
    Card* card;
    this->generateTempGamestate(duel);
    this->tested = -1;
    this->n_choices = 0;
    this->testing = true;
    this->testingTargets = false;
    float value;
    float bValue = this->baseGamestate->evaluate(this->baseGamestate->getPlayer(this->baseGamestate->getTurnPlayer()));
    player = this->tempGamestate->getPlayer(this->tempGamestate->getTurnPlayer());
    card = this->tempGamestate->getCardFromCopyId(c);
    if (card->getCost()<=player->getMana())
    {
        if (card->getCardType()==1 && !this->tempGamestate->canSummon(player)) {return;}
        this->tempGamestate->playFromHand(card);
        if (this->testingTargets)
        {
            if (this->n_choices>0)
            {
            for (int i=0;i<this->n_choices;i++)
                {
                    this->tested = i;
                    this->generateTempGamestate(duel);
                    player = this->tempGamestate->getPlayer(this->tempGamestate->getTurnPlayer());
                    card = this->tempGamestate->getCardFromCopyId(c);
                    this->tempGamestate->playFromHand(card);
                    this->tempGamestate->passTurn();
                    value = this->tempGamestate->evaluate(player);
                    if (this->targetId!=-1)
                    {
                        Option new_option;
                        new_option.setValue(value-bValue);
                        new_option.getTargets()->push_back({this->targetId});
                        new_option.getCardIds()->push_back(c);
                        if (option.getCardIds()->size()!=0)
                        {
                            Option op(option, new_option);
                            this->saveOption(op);
                        }
                        else
                        {
                            this->saveOption(new_option);
                        }
                    }

                }
            }
        }
        else
        {
            this->generateTempGamestate(duel);
            player = this->tempGamestate->getPlayer(this->tempGamestate->getTurnPlayer());
            card = this->tempGamestate->getCardFromCopyId(c);

            //qDebug()<<QString::fromStdString(card->getName());
            bool res = card->getCardName()->onSpell(this->tempGamestate, card);
            if (res)
            {
                this->tempGamestate->passTurn();
            value = this->tempGamestate->evaluate(player);
            Option new_option;
            new_option.setValue(value-bValue);
            new_option.getTargets()->push_back({-1});
            new_option.getCardIds()->push_back(c);
            if (option.getCardIds()->size()!=0)
            {
                Option op(option, new_option);
                this->saveOption(op);
            }
            else
            {
                this->saveOption(new_option);
            }
            }
        }
    }
    this->testing = false;
    this->testingTargets = false;
}
void Bot::testSpecialMinion(int c, Duel* duel, Option& option)
{
    Player* player;
    Card* card;
    this->material1 = nullptr;
    this->material2 = nullptr;
    this->material3 = nullptr;
    this->generateTempGamestate(duel);
    this->testing = true;
    float value;
    float bValue = this->baseGamestate->evaluate(duel->getPlayer(duel->getTurnPlayer()));
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
                    player = this->tempGamestate->getPlayer(this->tempGamestate->getTurnPlayer());
                    this->tempGamestate->summonSpecialMinion(this->tempGamestate->getCardFromCopyId(c));
                    this->tempGamestate->passTurn();
                    value = this->tempGamestate->evaluate(player);
                    Option new_option;
                    new_option.setValue(value-bValue);
                    new_option.getTargets()->push_back({firstIds[i],secondIds[j]});
                    new_option.getCardIds()->push_back(c);
                    if (option.getCardIds()->size()!=0)
                    {
                        Option op(option, new_option);
                        this->saveOption(op);
                    }
                    else
                    {
                        this->saveOption(new_option);
                    }
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
void Bot::saveOption(Option& option)
{
    if (option.getCardIds()->size()>0)
    {
        if (option.getCardIds()->at(0)<=20) {
            int breakpoint = 0;
        }
        this->options.push_back(option);

    }
}
void Bot::testOptionCombos(Duel* duel, short n)
{
    this->generateBaseGamestate(duel);
    this->options.clear();
    for (int i = 0; i<n; i++)
    {
        if (i == 0)
        {
            this->generateTestingGamestate(duel);
            Option o;
            this->generateOptions(this->testingGamestate, o);
        }

        if (i > 0)
        {
            std::vector<Option> new_options(this->options);
            int s = new_options.size();
            for (int j = 0; j < s; j++)
            {
                this->generateTestingGamestate(duel);
                this->performAction(this->testingGamestate, new_options[j]);
                this->generateOptions(this->testingGamestate, new_options[j]);
            }
        }
    }
}
void Bot::generateOptions(Duel* duel, Option& option)
{
    Player* player;
    player = duel->getPlayer(duel->getTurnPlayer());
    short n_hand = player->getHandSize();
    for (int z = 0;z<n_hand;z++)
    {
        this->testCardFromHand(player->getHand()->at(z)->getCopyId(), duel, option);
    }
    short n_special = player->getSpecialDeckSize();
    for (int z = 0;z<n_special;z++)
    {
        this->testSpecialMinion(player->getSpecialDeck()->at(z)->getCopyId(), duel, option);
    }

}
void Bot::performAction(Duel* duel, Option& option, bool display)
{
    for (int i = 0; i<option.getCardIds()->size(); i++)
    {
        int id = option.getCardIds()->at(i);
        Card* card = duel->getCardFromCopyId(id);
        short place = card->getPlace();
        std::string name = card->getName();

        if (place == 4)
            {
                card = duel->getCardFromCopyId(id);
                this->testing = false;
                this->testingTargets = false;
                std::vector<int> materials(option.getTargets()->at(i));
                Card* a = duel->getCardFromCopyId(materials[0]);
                Card* b = duel->getCardFromCopyId(materials[1]);
                Card* c = nullptr;
                if (materials.size()==3)
                { c = duel->getCardFromCopyId(materials[2]);}
                this->material1 = a; this->material2 = b; this->material3 = c;
                duel->summonSpecialMinion(card);
                this->material1 = nullptr; this->material2 = nullptr; this->material3 = nullptr;
                if (display) {duel->botDelay(600);}
            }
            else
            {
                card = duel->getCardFromCopyId(id);
                if (card->getPlace()==1) {
                this->testing = false;
                this->testingTargets = false;
                this->targetId = option.getTargets()->at(i).at(0);
                duel->playFromHand(card);
                if (display) {duel->botDelay(600);}
                    }
        }
    }
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
    float bv = this->baseGamestate->evaluate(this->baseGamestate->getPlayer(this->baseGamestate->getTurnPlayer()));
    short n_defenders = this->baseGamestate->getDefendersList()->getTargetsNumber();
    for (int i=0;i<n_defenders;i++)
    {
        this->generateTempGamestate(duel);
        Player* player = this->tempGamestate->getPlayer(this->tempGamestate->getTurnPlayer());
        this->tempGamestate->generateAttackersList(player);
        this->tempGamestate->generateDefendersList(player);
        Card* attacker = this->tempGamestate->getAttackersList()->getTargetList()->at(c);
        Card* defender = this->tempGamestate->getDefendersList()->getTargetList()->at(i);

        this->tempGamestate->combat(attacker,defender);
        float v = this->tempGamestate->evaluate(player);
        this->saveAttackOption(attacker->getCopyId(),defender->getCopyId(),v-bv);
    }
    if (n_defenders == 0)
    {
        this->generateTempGamestate(duel);
        Player* player = this->tempGamestate->getPlayer(this->tempGamestate->getTurnPlayer());
        this->tempGamestate->generateAttackersList(player);
        Card* attacker = this->tempGamestate->getAttackersList()->getTargetList()->at(c);
        this->tempGamestate->directAttack(attacker);
        float v = this->tempGamestate->evaluate(player);
        this->saveAttackOption(attacker->getCopyId(),-1,v-bv);
    }
}
void Bot::testBattlePhase(Duel* duel)
{
    this->generateBaseGamestate(duel);
    Player* player = this->baseGamestate->getPlayer(this->baseGamestate->getTurnPlayer());
    this->baseGamestate->generateAttackersList(player);
    this->baseGamestate->generateDefendersList(player);
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

            Player* player = duel->getPlayer(duel->getTurnPlayer());
            duel->generateAttackersList(player);
            duel->generateDefendersList(player);
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
    this->endTesting();
}
void Bot::playTurn(Duel* duel)
{
            while (true)
            {

                Player* player = duel->getPlayer(duel->getTurnPlayer());
                this->testOptionCombos(duel, 2);

                int n_options = this->getOptionsNumber();

                if (n_options==0) { this->endTesting(); break;}
                int option = this->getBestOption();
                Card* car = duel->getCardFromCopyId(this->options[option].getCardIds()->at(0));

                float val = this->options[option].getValue();
                qDebug()<<QString::fromStdString(car->getName())<<" "<<val<<" "<<n_options<<" "<<this->options[option].getCardIds()->at(0);
                if (val<=0) {
                    this->endTesting();

                    break;}

                this->performAction(duel, this->options[option], true);
                this->endTesting();
                if (duel->getDuelEnded())
                {
                    return;
                }
            }
            if (duel->getTurnCount()>1){this->conductBattlePhase(duel);}
            if (!duel->getDuelEnded()){duel->passTurn();}


}



