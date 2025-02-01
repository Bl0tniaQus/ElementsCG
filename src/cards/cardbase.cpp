#include "cardbase.h"
#include <cstring>
#include "../engine/targetlist.h"
#include "../engine/zone.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/bot.h"
#include <iostream>
#include <QDebug>
CardBase::CardBase(short cid, short c, short ct, short l, short a, short d, std::string el, std::string n, std::string i, std::string ctx)
{
    this->cardId = cid;
    this->cost = c;
    this->cardType = ct;
    this->level = l;
    this->attack = a;
    this->defence = d;
    this->targetList = new TargetList;
    this->element = el;
    this->usedMaterials = new Card* [0];
    this->name = n;
    this->image = i;
    this->cardText = ctx;
}
CardBase::~CardBase()
{
    delete this->targetList;
    delete [] this->usedMaterials;
}
void CardBase::setTargetList(std::vector<Card*>* tl)
{
    this->targetList->setTargetList(tl);
}
void CardBase::onTurnStart(Duel* duel, Card* card)
{
    if (card->getCardType()!=0&&card->getPlace()==2)
    {
        card->setAttacks(1);
    }
}
void CardBase::setTwoMaterials(Card* material1, Card* material2)
{
    delete this->usedMaterials;

    this->usedMaterials = new Card* [2];

    this->usedMaterials[0] = material1;
    this->usedMaterials[1] = material2;

}
void CardBase::setThreeMaterials(Card* material1, Card* material2, Card* material3)
{
    delete this->usedMaterials;

    this->usedMaterials = new Card* [3];

    this->usedMaterials[0] = material1;
    this->usedMaterials[1] = material2;
    this->usedMaterials[2] = material3;

}
short CardBase::singleChoice(Duel* duel, Card* card)
{
    std::vector<Card*>* targets = this->getTargetList()->getTargetList();
    short nt = this->getTargetList()->getTargetsNumber();
    Player* owner = card->getOwner();
    Bot* bot = owner->getBot();
    if (bot!=nullptr&&!bot->isTestingTargets()&&bot->isTesting())
    {
        if (bot->getTestedNumber()==-1)
        {
            bot->setChoicesNumber(nt);
            bot->setTargetTesting(true);
            return -1;
        }

    }
    if (nt>0)
    {
        if (owner->getBot()==nullptr)
        {
                return duel->makeSpellChoice(card);
        }
        else
        {
            if (bot->isTesting())
            {
                return bot->getTestedNumber();
            }
            else
            {
                return bot->getBestTarget();
            }
        }
    }
    return -1;
}
void CardBase::allMinionsOnField(Duel* duel, Card* card)
{
    this->setTargetList(nullptr);
    std::vector<Card*>* targets = new std::vector<Card*>;
    Zone* zone;
    Player* player;
    player = duel->getPlayer(duel->getTurnPlayer())->getOpponent();
    for (int i=0;i<5;i++)
        {
            zone = &player->getMinionField()[i];
            Card *cardd = zone->getCard();

            if (cardd!=nullptr)
            {
            targets->push_back(cardd);
            }
        }
        player = duel->getPlayer(duel->getTurnPlayer());
        for (int i=0;i<5;i++)
        {
            zone = &player->getMinionField()[i];
            Card *cardd = zone->getCard();
            if (cardd!=nullptr)
            {
            targets->push_back(cardd);
            }
        }
        this->setTargetList(targets);
}
void CardBase::minionsOnYourFieldWithSameElement(Duel* duel, Card* card, const std::string& element)
{
    this->setTargetList(nullptr);
    std::vector<Card*>* targets = new std::vector<Card*>;
    Zone* zone;
    Player* player;
        player = card->getOwner();
        for (int i=0;i<5;i++)
        {
            zone = &player->getMinionField()[i];
            Card *cardd = zone->getCard();
            if (cardd!=nullptr)
            {
                if (element == cardd->getElement())
                {
                    targets->push_back(cardd);
                }
            }
        }
        this->setTargetList(targets);
}
void CardBase::cardsWithSameElementInTargetList(const std::string& element)
{
    std::vector<Card*>* targets = new std::vector<Card*>;
    std::vector<Card*>* targetList = this->getTargetList()->getTargetList();
    short n = this->getTargetList()->getTargetsNumber();
    for (int i=0; i<n;i++)
    {
        Card* cardd = targetList->at(i);
        if (element == cardd->getElement())
        {
                    targets->push_back(cardd);
                }
    }
    this->setTargetList(targets);
}

void CardBase::cardsInHandWithTheSameName(Duel* duel, Card* card)
{
    this->setTargetList(nullptr);
    short handSize = card->getOwner()->getHandSize();
    std::vector<Card*>* targets = new std::vector<Card*>;
    for (int i=0;i<handSize;i++)
        {
            Card *target = card->getOwner()->getHand()[i];
            if ((target!=nullptr)&&(target->getCardId() == card->getCardId())&&(card!=target))
            {
            targets->push_back(target);
            }

    }
    this->setTargetList(targets);
}
void CardBase::cardsInHandWithCommonNamePart(Duel* duel, Card* card, const std::string& namePart)
{
    this->setTargetList(nullptr);
    short handSize = card->getOwner()->getHandSize();
    std::vector<Card*>* targets = new std::vector<Card*>;
    for (int i=0;i<handSize;i++)
        {
            Card *target = card->getOwner()->getHand()[i];
            if ((target!=nullptr)&&(target->getName().find(namePart)!=std::string::npos)&&(card!=target))
            {
            targets->push_back(target);
            }

    }
    this->setTargetList(targets);
}
void CardBase::cardsInDeckWithCommonNamePart(Duel* duel, Card* card, const std::string& namePart)
{
    this->setTargetList(nullptr);
    short deckSize = card->getOwner()->getDeckSize();
    std::vector<Card*>* targets = new std::vector<Card*>;
    for (int i=0;i<deckSize;i++)
        {
            Card *target = card->getOwner()->getDeck()[i];
            if ((target!=nullptr)&&(target->getName().find(namePart)!=std::string::npos)&&(card!=target))
            {
            targets->push_back(target);
            }

    }
    this->setTargetList(targets);
}
void CardBase::nTopCardsFromDeck(Duel* duel, Card* card, short n)
{
    this->setTargetList(nullptr);
    short deckSize = card->getOwner()->getDeckSize();
    if (deckSize<n) {return;}
    std::vector<Card*>* targets = new std::vector<Card*>;
    for (int i=0;i<n;i++)
        {
            Card *target = card->getOwner()->getDeck()[deckSize-(i+1)];
            targets->push_back(target);

    }
    this->setTargetList(targets);
}

void CardBase::minionsOnYourFieldWithCommonNamePart(Duel* duel, Card* card, const std::string& namePart)
{
    this->setTargetList(nullptr);
    std::vector<Card*>* targets = new std::vector<Card*>;
    Player* player = card->getOwner();
    Zone* zone;
    for (int i=0;i<5;i++)
        {
            zone = &player->getMinionField()[i];
            Card *cardd = zone->getCard();
            if (cardd!=nullptr)
            {
                if (cardd->getName().find(namePart)!=std::string::npos)
                {
                    targets->push_back(cardd);
                }
            }
        }
    this->setTargetList(targets);
}
bool CardBase::checkSummoningConditions2(Duel* duel, Card* card)
{
        if (card->getCardName()->getMaterialNumber()!=2) {return false;}
        bool result = true;
        this->getFirstMaterialList(duel, card);
        short n_targets1 = this->getTargetList()->getTargetsNumber();
        std::vector<Card*>* temp_targets = this->getTargetList()->getTargetList();
        std::vector<Card*>* targets1 = new std::vector<Card*>(n_targets1);
        for (int i=0;i<n_targets1;i++)
        {
            targets1->at(i) = temp_targets->at(i);
        }
        this->getSecondMaterialList(duel, card);
        short n_targets2 = this->getTargetList()->getTargetsNumber();
        temp_targets = this->getTargetList()->getTargetList();
        std::vector<Card*>* targets2 = new std::vector<Card*>(n_targets2);
        for (int i=0;i<n_targets2;i++)
        {
            targets2->at(i) = temp_targets->at(i);
        }

        if ((n_targets1==0)||(n_targets2==0)) {result = false;}
        else if ((n_targets1==1)&&(n_targets2==1))
        {
            if (targets1->at(0)==targets2->at(0)) {result = false;}
        }
        else if ((n_targets1==1)&&(n_targets2==1))
        {
            for (int i=0;i<n_targets2;i++)
            {
                if (targets2->at(i)==targets1->at(0)) {result = false;}
            }
        }
    delete targets1;
    delete targets2;
    return result;
}
bool CardBase::checkSummoningConditions3(Duel* duel, Card* card)
{
        if (card->getCardName()->getMaterialNumber()!=3) {return false;}
        bool result = false;
        this->getFirstMaterialList(duel, card);
        short n_targets1 = this->getTargetList()->getTargetsNumber();
        std::vector<Card*>* temp_targets = this->getTargetList()->getTargetList();
        std::vector<Card*>* targets1 = new std::vector<Card*>(n_targets1);
        for (int i=0;i<n_targets1;i++)
        {
            targets1->at(i) = temp_targets->at(i);
        }
        this->getSecondMaterialList(duel, card);
        short n_targets2 = this->getTargetList()->getTargetsNumber();
        temp_targets = this->getTargetList()->getTargetList();
        std::vector<Card*>* targets2 = new std::vector<Card*>(n_targets2);
        for (int i=0;i<n_targets2;i++)
        {
            targets2->at(i) = temp_targets->at(i);
        }
        this->getThirdMaterialList(duel, card);
        short n_targets3 = this->getTargetList()->getTargetsNumber();
        temp_targets = this->getTargetList()->getTargetList();
        std::vector<Card*>* targets3 = new std::vector<Card*>(n_targets3);
        for (int i=0;i<n_targets3;i++)
        {
            targets3->at(i) = temp_targets->at(i);
        }
        if ((n_targets1==0)||(n_targets2==0)||n_targets3==0) {result = false;}
        else if ((n_targets1==3)&&(n_targets2==3)&&n_targets3==3) {result = true;}
        else
        {
            Card* card1;
            Card* card2;
            Card* card3;
            for (short i1=0;i1<n_targets1;i1++)
            {
                card1 = targets1->at(i1);
                if (result) break;
                for (short i2=0;i2<n_targets2;i2++)
                {
                    card2 = targets2->at(i2);
                    if (result) break;
                    for (short i3=0;i3<n_targets3;i3++)
                    {
                        card3 = targets3->at(i3);
                        if (card1 == card2 || card1 == card3 || card2 == card3) {result = false;}
                        else if (card1 != card2 && card1 != card3 && card2 != card3) {result = true;}
                        if (result) break;
                    }
                }
            }
        }
    delete targets1;
    delete targets2;
    delete targets3;
    return result;
}
bool CardBase::specialSummon2(Duel* duel, Card* card)
{
    if (checkSummoningConditions2(duel,card))
    {
        Card* targetCard;
        Card* targetCard2;
        if (card->getOwner()->getBot()==nullptr)
        {
        this->getFirstMaterialList(duel, card);
        std::vector<Card*>* targets1 = this->getTargetList()->getTargetList();
        int target;
        target = duel->makeSpecialMinionMaterialChoice(card);
        if (target==-1) {return false;}
        targetCard = targets1->at(target);
        this->getSecondMaterialList(duel, card);
        short n_targets2 = this->getTargetList()->getTargetsNumber();
        std::vector<Card*>* targets2 = this->getTargetList()->getTargetList();
        std::vector<Card*>* new_targets2;
        short n_targets2New = n_targets2;
        bool duplicate = 0;
        for (int i=0;i<n_targets2;i++)
        {
            if (targets2->at(i)==targetCard) {duplicate = true;}
        }
        if (duplicate)
            {
                new_targets2 = new std::vector<Card*>(n_targets2-1);
                short bias=0;
                for (int j=0;j<n_targets2;j++)
                {
                   if (targets2->at(j)==targetCard) {bias=1; n_targets2New = n_targets2-1; continue;}
                   new_targets2->at(j-bias)=targets2->at(j);
                }
            }
            else
            {
                new_targets2 = new std::vector<Card*>(n_targets2);
                for (int j=0;j<n_targets2;j++)
                {
                   new_targets2->at(j)=targets2->at(j);
                }
            }
        card->getCardName()->setTargetList(new_targets2);
        target = duel->makeSpecialMinionMaterialChoice(card);
        if (target==-1) {return false;}
        targetCard2 = new_targets2->at(target);
        }
        else
        {
            targetCard = card->getOwner()->getBot()->getFirstMaterial();
            targetCard2 = card->getOwner()->getBot()->getSecondMaterial();
        }
        this->release2Log(targetCard,targetCard2, duel);
        this->setTwoMaterials(targetCard, targetCard2);
        duel->releaseForSpecialSummon(targetCard, card);
        duel->releaseForSpecialSummon(targetCard2, card);
        return true;
    }
    return false;
}
bool CardBase::specialSummon3(Duel* duel, Card* card)
{
    if (checkSummoningConditions3(duel,card))
    {
        Card* targetCard;
        Card* targetCard2;
        Card* targetCard3;
        if (card->getOwner()->getBot()==nullptr)
        {
        this->getFirstMaterialList(duel, card);
        std::vector<Card*>* targets1 = this->getTargetList()->getTargetList();
        int target;
        target = duel->makeSpecialMinionMaterialChoice(card);
        if (target==-1) {return false;}
        targetCard = targets1->at(target);
        this->getSecondMaterialList(duel, card);
        short n_targets2 = this->getTargetList()->getTargetsNumber();
        std::vector<Card*>* targets2 = this->getTargetList()->getTargetList();
        std::vector<Card*>* new_targets2;
        short n_targets2New = n_targets2;
        bool duplicate = 0;
        for (int i=0;i<n_targets2;i++)
        {
            if (targets2->at(i)==targetCard) {duplicate = true;}
        }
        if (duplicate)
            {
                new_targets2 = new std::vector<Card*>(n_targets2-1);
                short bias=0;
                for (int j=0;j<n_targets2;j++)
                {
                   if (targets2->at(j)==targetCard) {bias=1; n_targets2New = n_targets2-1; continue;}
                   new_targets2->at(j-bias)=targets2->at(j);
                }
            }
            else
            {
                new_targets2 = new std::vector<Card*> [n_targets2];
                for (int j=0;j<n_targets2;j++)
                {
                   new_targets2->at(j)=targets2->at(j);
                }
            }
        card->getCardName()->setTargetList(new_targets2);
        target = duel->makeSpecialMinionMaterialChoice(card);
        if (target==-1) {return false;}
        targetCard2 = new_targets2->at(target);

        short duplicates = 0;
        this->getThirdMaterialList(duel, card);
        short n_targets3 = this->getTargetList()->getTargetsNumber();
        std::vector<Card*>* targets3 = this->getTargetList()->getTargetList();
        std::vector<Card*>* new_targets3;
        short n_targets3New = n_targets3;

        for (int i=0;i<n_targets3;i++)
        {
            if (targets3->at(i)==targetCard) {duplicates++;}
            if (targets3->at(i)==targetCard2) {duplicates++;}
        }
        if (duplicates)
            {
                new_targets3 = new std::vector<Card*> [n_targets3-duplicates];
                short bias=0;
                for (int j=0;j<n_targets3;j++)
                {
                   if (targets3->at(j)==targetCard || targets3->at(j)==targetCard2) {bias++; n_targets3New--; continue;}
                   new_targets3->at(j-bias)=targets3->at(j);
                }
            }
            else
            {
                new_targets3 = new std::vector<Card*> [n_targets3];
                for (int j=0;j<n_targets3;j++)
                {
                   new_targets3->at(j)=targets3->at(j);
                }
            }
        card->getCardName()->setTargetList(new_targets3);
        target = duel->makeSpecialMinionMaterialChoice(card);
        if (target==-1) {return false;}
        targetCard3 = new_targets3->at(target);
        }
        else
        {
            targetCard = card->getOwner()->getBot()->getFirstMaterial();
            targetCard2 = card->getOwner()->getBot()->getSecondMaterial();
            targetCard3 = card->getOwner()->getBot()->getThirdMaterial();
        }
        this->release3Log(targetCard,targetCard2,targetCard3, duel);
        this->setThreeMaterials(targetCard, targetCard2, targetCard3);
        duel->releaseForSpecialSummon(targetCard, card);
        duel->releaseForSpecialSummon(targetCard2, card);
        duel->releaseForSpecialSummon(targetCard3, card);
        return true;
    }
    return false;
}
void CardBase::minionsOnYourFieldWithSameElementAndMinimumLevel(Duel* duel, Card* card, const std::string& element, short lvl)
{
    this->setTargetList(nullptr);
    std::vector<Card*>* targets = new std::vector<Card*>;
    Player* owner = card->getOriginalOwner();
        for (int i=0;i<5;i++)
        {
            Card* cardd = owner->getMinionField()[i].getCard();
            if (cardd!=nullptr)
            {
                if (element == cardd->getElement()&&cardd->getLevel()>=lvl)
                {
                   targets->push_back(cardd);
                }
            }
        }

    this->setTargetList(targets);
}
void CardBase::minionsOnYourFieldWithSameElementAndMaximumLevel(Duel* duel, Card* card, const std::string& element, short lvl)
{
    this->setTargetList(nullptr);
    std::vector<Card*>* targets = new std::vector<Card*>;
    Player* owner = card->getOriginalOwner();
        for (int i=0;i<5;i++)
        {
            Card* cardd = owner->getMinionField()[i].getCard();
            if (cardd!=nullptr)
            {
                if (element == cardd->getElement()&&cardd->getLevel()<=lvl)
                {
                    targets->push_back(cardd);
                }
            }
        }

    this->setTargetList(targets);
}

void CardBase::minionsInYourGraveyardWithSameElementAndMaximumLevel(Duel* duel, Card* card, const std::string& element, short lvl)
{
    this->setTargetList(nullptr);
    std::vector<Card*>* targets = new std::vector<Card*>;
    Card** graveyard = card->getOwner()->getGraveyard();
    short n_graveyard = card->getOwner()->getGraveyardSize();
        for (int i=0;i<n_graveyard;i++)
        {
            Card* cardd = graveyard[i];
            if (element == cardd->getElement()&&cardd->getLevel()<=lvl&&cardd->getCardType()==1)
            {
                targets->push_back(cardd);
            }

        }
    this->setTargetList(targets);
}
void CardBase::cardsInYourGraveyardWithSameElement(Duel* duel, Card* card, const std::string& element)
{
    this->setTargetList(nullptr);
    std::vector<Card*>* targets = new std::vector<Card*>;
    Card** graveyard = card->getOwner()->getGraveyard();
    short n_graveyard = card->getOwner()->getGraveyardSize();
        for (int i=0;i<n_graveyard;i++)
        {
            Card* cardd = graveyard[i];
            if (element == cardd->getElement())
            {
                targets->push_back(cardd);
            }

        }
    this->setTargetList(targets);
}
void CardBase::cardsInYourGraveyardWithExactName(Duel* duel, Card* card, const std::string& name)
{
    this->setTargetList(nullptr);
    std::vector<Card*>* targets = new std::vector<Card*>;
    Card** graveyard = card->getOwner()->getGraveyard();
    short n_graveyard = card->getOwner()->getGraveyardSize();
        for (int i=0;i<n_graveyard;i++)
        {
            Card* cardd = graveyard[i];
            if (name == cardd->getName())
            {
                targets->push_back(cardd);
            }

        }
    this->setTargetList(targets);
}

void CardBase::specialMinionsInYourGraveyardWithSameElement(Duel* duel, Card* card, const std::string& element)
{
    this->setTargetList(nullptr);
    std::vector<Card*>* targets = new std::vector<Card*>;
    Card** graveyard = card->getOwner()->getGraveyard();
    short n_graveyard = card->getOwner()->getGraveyardSize();
        for (int i=0;i<n_graveyard;i++)
        {
            Card* cardd = graveyard[i];
            if (element == cardd->getElement()&&cardd->getCardType()==2)
            {
                targets->push_back(cardd);
            }

        }
    this->setTargetList(targets);
}
void CardBase::minionsOnYourFieldWithExactName(Duel* duel, Card* card, const std::string& name)
{
    this->setTargetList(nullptr);
    std::vector<Card*>* targets = new std::vector<Card*>;
    Player* owner = card->getOriginalOwner();
    Zone* zone;
    Card* cardd;
        for (int i=0;i<5;i++)
        {
            zone = &owner->getMinionField()[i];
            cardd = zone->getCard();

            if (cardd!=nullptr)
            {
                if (name == cardd->getName())
                {
                    targets->push_back(cardd);
                }
            }
        }

    this->setTargetList(targets);
}
void CardBase::specialMinionsOnYourFieldWithSameAttribute(Duel* duel, Card* card, const std::string& element)
{
    this->setTargetList(nullptr);
    std::vector<Card*>* targets = new std::vector<Card*>;
    Zone* zone;
    Player* player;
        player = card->getOwner();
        for (int i=0;i<5;i++)
        {
            zone = &player->getMinionField()[i];
            Card *cardd = zone->getCard();
            if (cardd!=nullptr)
            {
                if (cardd->getCardType()==2&&element == cardd->getElement())
                {
                    targets->push_back(cardd);
                }
            }
        }
        this->setTargetList(targets);
}
void CardBase::minionsInHandWithMaximumLevel(Duel* duel, Card* card, short level)
{
    this->setTargetList(nullptr);
    short handSize = card->getOwner()->getHandSize();
    std::vector<Card*>* targets = new std::vector<Card*>;
    for (int i=0;i<handSize;i++)
        {
            Card *target = card->getOwner()->getHand()[i];
            if (target!=nullptr&&target->getLevel()<=level&&target->getCardType()==1)
            {
            targets->push_back(target);
            }

    }
    this->setTargetList(targets);
}
void CardBase::minionsOnYourFieldWithOneOfTwoElementsAndMinimumLevel(Duel* duel, Card* card, const std::string& element1, const std::string& element2, short lvl)
{
    this->setTargetList(nullptr);
    std::vector<Card*>* targets = new std::vector<Card*>;
    Zone* zone;
    Player* player;
        player = card->getOwner();
        for (int i=0;i<5;i++)
        {
            zone = &player->getMinionField()[i];
            Card *cardd = zone->getCard();
            if (cardd!=nullptr)
            {
                if ((element1 == cardd->getElement()||element2 == cardd->getElement())&&cardd->getLevel()>=lvl)
                {
                    targets->push_back(cardd);
                }
            }
        }
        this->setTargetList(targets);
}

short CardBase::highestLevelInTargetList()
{
    short lvl = -1;
    short nt = this->getTargetList()->getTargetsNumber();
    std::vector<Card*>* targets = this->getTargetList()->getTargetList();

    for (short i = 0; i<nt; i++)
    {
        short card_lvl = targets->at(i)->getLevel();
        if (card_lvl>lvl) {lvl = card_lvl;}
    }
    return lvl;
}

void CardBase::spellCost(Card* card)
{
    card->getOwner()->changeMana(-card->getCost());
}
void CardBase::effectLog(Duel* duel, Card* card)
{
    std::string cardName = this->getName();
    std::string str = "["+cardName+"]"+"'s effect activates";
    duel->appendLog(str,duel->getPlayerId(card->getOwner()));
}
void CardBase::firstEffectLog(Duel* duel, Card* card)
{
    std::string cardName = this->getName();
    std::string str = "["+cardName+"]"+"'s first effect activates";
    duel->appendLog(str,duel->getPlayerId(card->getOwner()));
}
void CardBase::secondEffectLog(Duel* duel, Card* card)
{
    std::string cardName = this->getName();
    std::string str = "["+cardName+"]"+"'s second effect activates";
    duel->appendLog(str,duel->getPlayerId(card->getOwner()));
}
void CardBase::thirdEffectLog(Duel* duel, Card* card)
{
    std::string cardName = this->getName();
    std::string str = "["+cardName+"]"+"'s third effect activates";
    duel->appendLog(str,duel->getPlayerId(card->getOwner()));
}
void CardBase::release2Log(Card* c1, Card* c2, Duel* duel)
{
    std::string playerName = std::string(c1->getOwner()->getName());
    std::string n1 = std::string(c1->getName());
    std::string n2 = std::string(c2->getName());
    std::string str = "[" + playerName + "] releases [" + n1 + "] and [" + n2 + "]";
    duel->appendLog(str,duel->getPlayerId(c1->getOwner()));
}
void CardBase::release3Log(Card* c1, Card* c2, Card* c3, Duel* duel)
{
    std::string playerName = std::string(c1->getOwner()->getName());
    std::string n1 = std::string(c1->getName());
    std::string n2 = std::string(c2->getName());
    std::string n3 = std::string(c3->getName());
    std::string str = "[" + playerName + "] releases [" + n1 + "], [" + n2 + "] and [" + n3 + "]";
    duel->appendLog(str,duel->getPlayerId(c1->getOwner()));
}
void CardBase::spellFromHandLog(Duel* duel, Card* card)
{
    duel->appendLog(duel->cardFromHandLog(card),duel->getPlayerId(card->getOwner()));
}


