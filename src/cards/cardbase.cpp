#include "cardbase.h"
#include <cstring>
#include "../engine/targetlist.h"
#include "../engine/zone.h"
#include "../engine/duel.h"
#include "../engine/card.h"
#include "../engine/bot.h"
#include "../engine/globals.h"
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
    this->usedMaterials = std::vector<Card*>(0);
    this->cardTargets = std::vector<Card*>(0);
    this->numericValues = std::vector<int>(0);
    this->booleanValues = std::vector<bool>(0);
    this->name = n;
    this->image = i;
    this->cardText = ctx;
}
CardBase::CardBase()
{
    this->usedMaterials = std::vector<Card*>(0);
    this->cardTargets = std::vector<Card*>(0);
    this->numericValues = std::vector<int>(0);
    this->booleanValues = std::vector<bool>(0);
    this->targetList = new TargetList;
}
CardBase::~CardBase()
{
    delete this->targetList;
}
void CardBase::copy(Duel* duel, CardBase* c)
{
    this->numericValues = std::vector<int>(*c->getNumericValues());
    this->booleanValues = std::vector<bool>(*c->getBooleanValues());
    this->usedMaterialsIds = std::vector<int>(*c->getUsedMaterialsIds());
    int nm = c->getUsedMaterials()->size();
    int nc = c->getCardTargets()->size();
    this->usedMaterials = std::vector<Card*>(nm);
    this->cardTargets = std::vector<Card*>(nc);
    Card* card;
    for (int i = 0; i<nm; i++)
    {
        card = c->getUsedMaterials()->at(i);
        if (card->isToken()){this->usedMaterials[i] = card;}
        else this->usedMaterials[i] = duel->getCardFromCopyId(card->getCopyId());
    }
    for (int i = 0; i<nc; i++)
    {
        card = c->getCardTargets()->at(i);
        if (card->isToken()){this->cardTargets[i] = card;}
        else this->cardTargets[i] = duel->getCardFromCopyId(card->getCopyId());
    }
}

void CardBase::setTargetList(std::vector<Card*>& tl)
{
    this->targetList->setTargetList(tl);
}
void CardBase::clearTargetList()
{
    this->targetList->clearTargetList();
}
void CardBase::onTurnStart(Duel* duel, Card* card)
{
    if (card->getCardType()!=0&&card->getPlace()==2)
    {
        card->setAttacks(1);
    }
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
void CardBase::setMaterials(std::vector<Card *>& mats)
{
    this->usedMaterials = std::vector<Card*>(mats);
    this->usedMaterialsIds = std::vector<int>(0);
    for (Card* card : this->usedMaterials)
    {
        if (card->isToken()) {this->usedMaterialsIds.push_back(-1);}
        else
        {
            this->usedMaterialsIds.push_back(card->getCopyId());
        }
    }
}
int CardBase::singleChoice(Duel* duel, Card* card)
{
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
                bot->setTargetId(this->getTargetList()->getTargetList()->at(bot->getTestedNumber())->getCopyId());
                return this->getTargetList()->getTargetList()->at(bot->getTestedNumber())->getCopyId();
            }
            else
            {
                //return bot->getBestSingleTarget(duel);
                return bot->getTargetId();
            }
        }
    }
    return -1;
}
bool CardBase::checkSummoningConditions2(Duel* duel, Card* card)
{
        if (card==nullptr) {return false;}
        short n = card->getCardName()->getRequiredMaterialsNumber();
        if (n!=2) {return false;}
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
        if (card==nullptr) {return false;}
        short n = card->getCardName()->getRequiredMaterialsNumber();
        if (n!=3) {return false;}
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
        card->getCardName()->setTargetList(*new_targets2);
        target = duel->makeSpecialMinionMaterialChoice(card);
        if (target==-1) {return false;}
        targetCard2 = new_targets2->at(target);
        }
        else
        {
            targetCard = card->getOwner()->getBot()->getFirstMaterial();
            targetCard2 = card->getOwner()->getBot()->getSecondMaterial();
            this->getFirstMaterialList(duel, card);
            bool b1 = this->getTargetList()->isPresent(targetCard);
            this->getSecondMaterialList(duel, card);
            bool b2 = this->getTargetList()->isPresent(targetCard2);
            if (!b1 || !b2) {return false;}
        }
        this->release2Log(targetCard,targetCard2, duel);

        std::vector<Card*> mats = std::vector<Card*>(0);
        if (!targetCard->isToken()){mats.push_back(targetCard);}
        else{mats.push_back(&tokenCatalog[targetCard->getCardId()]);}
        if (!targetCard2->isToken()){mats.push_back(targetCard2);}
        else{mats.push_back(&tokenCatalog[targetCard2->getCardId()]);}
        this->setMaterials(mats);
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
        card->getCardName()->setTargetList(*new_targets2);
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
        card->getCardName()->setTargetList(*new_targets3);
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
        std::vector<Card*> mats = std::vector<Card*>(0);
        if (!targetCard->isToken()){mats.push_back(targetCard);}
        else{mats.push_back(&tokenCatalog[targetCard->getCardId()]);}
        if (!targetCard2->isToken()){mats.push_back(targetCard2);}
        else{mats.push_back(&tokenCatalog[targetCard2->getCardId()]);}
        if (!targetCard3->isToken()){mats.push_back(targetCard3);}
        else{mats.push_back(&tokenCatalog[targetCard3->getCardId()]);}
        this->setMaterials(mats);
        duel->releaseForSpecialSummon(targetCard, card);
        duel->releaseForSpecialSummon(targetCard2, card);
        duel->releaseForSpecialSummon(targetCard3, card);
        return true;
    }
    return false;
}
void CardBase::allMinionsOnField(Duel* duel)
{
    std::vector<Card*> targets = TargetList::allMinionsOnField(duel);
    this->setTargetList(targets);
}
void CardBase::cardsInHandWithTheSameName(Player* player, const std::string& name)
{
    std::vector<Card*> targets = TargetList::cardsInHand(player);
    targets = TargetList::filterCardName(targets, name);
    this->setTargetList(targets);
}
void CardBase::cardsWithSameElementInTargetList(const std::string& element)
{
    std::vector<Card*> targets(*this->targetList->getTargetList());
    targets = TargetList::filterOneElement(targets, element);
    this->setTargetList(targets);
}
void CardBase::cardsInHandWithCommonNamePart(Player* player, const std::string& namePart)
{
    std::vector<Card*> targets = TargetList::cardsInHand(player);
    targets = TargetList::filterNamePart(targets, namePart);
    this->setTargetList(targets);
}
void CardBase::cardsInDeckWithCommonNamePart(Player* player, const std::string& namePart)
{
    std::vector<Card*> targets = TargetList::cardsInDeck(player);
    targets = TargetList::filterNamePart(targets, namePart);
    this->setTargetList(targets);
}
void CardBase::minionsInYourGraveyardWithSameElementAndMaximumLevel(Player* player, const std::string& element, short lvl)
{
    std::vector<Card*> targets = TargetList::cardsInGraveyard(player);
    targets = TargetList::filterOutCardType(targets, 0);
    targets = TargetList::filterOneElement(targets, element);
    targets = TargetList::filterLevelRange(targets, 0, lvl);
    this->setTargetList(targets);
}
void CardBase::cardsInYourGraveyardWithSameElement(Player* player, const std::string& element)
{
    std::vector<Card*> targets = TargetList::cardsInGraveyard(player);
    targets = TargetList::filterOneElement(targets, element);
    this->setTargetList(targets);
}
void CardBase::cardsInYourGraveyardWithExactName(Player* player, const std::string& name)
{
    std::vector<Card*> targets = TargetList::cardsInGraveyard(player);
    targets = TargetList::filterCardName(targets, name);
    this->setTargetList(targets);
}
void CardBase::specialMinionsInYourGraveyardWithSameElement(Player* player, const std::string& element)
{
    std::vector<Card*> targets = TargetList::cardsInGraveyard(player);
    targets = TargetList::filterCardType(targets, 2);
    targets = TargetList::filterOneElement(targets, element);
    this->setTargetList(targets);
}
void CardBase::specialMinionsOnYourFieldWithSameElement(Duel* duel, Player* player, const std::string& element)
{
    std::vector<Card*> targets = TargetList::allMinionsOnField(duel);
    targets = TargetList::filterPlayer(targets, player);
    targets = TargetList::filterCardType(targets, 2);
    targets = TargetList::filterOneElement(targets, element);
    this->setTargetList(targets);
}
void CardBase::minionsInHandWithMaximumLevel(Player* player, short level)
{
    std::vector<Card*> targets = TargetList::cardsInHand(player);
    targets = TargetList::filterCardType(targets, 1);
    targets = TargetList::filterLevelRange(targets, 0, level);
    this->setTargetList(targets);
}
void CardBase::minionsOnYourFieldWithCommonNamePart(Duel* duel, Player* player, const std::string& namePart)
{
    std::vector<Card*> targets = TargetList::allMinionsOnField(duel);
    targets = TargetList::filterPlayer(targets, player);
    targets = TargetList::filterOutCardType(targets, 0);
    targets = TargetList::filterNamePart(targets, namePart);
    this->setTargetList(targets);
}
void CardBase::minionsOnYourFieldWithSameElement(Duel* duel, Player* player, const std::string& element)
{
    std::vector<Card*> targets = TargetList::allMinionsOnField(duel);
    targets = TargetList::filterPlayer(targets, player);
    targets = TargetList::filterOutCardType(targets, 0);
    targets = TargetList::filterOneElement(targets, element);
    this->setTargetList(targets);
}
void CardBase::minionsOnYourFieldWithSameElementAndMinimumLevel(Duel* duel, Player* player, const std::string& element, short lvl)
{
    std::vector<Card*> targets = TargetList::allMinionsOnField(duel);
    targets = TargetList::filterPlayer(targets, player);
    targets = TargetList::filterOutCardType(targets, 0);
    targets = TargetList::filterOneElement(targets, element);
    targets = TargetList::filterLevelRange(targets, lvl, 100);
    this->setTargetList(targets);
}
void CardBase::minionsOnYourFieldWithSameElementAndMaximumLevel(Duel* duel, Player* player, const std::string& element, short lvl)
{
    std::vector<Card*> targets = TargetList::allMinionsOnField(duel);
    targets = TargetList::filterPlayer(targets, player);
    targets = TargetList::filterOutCardType(targets, 0);
    targets = TargetList::filterOneElement(targets, element);
    targets = TargetList::filterLevelRange(targets, 0, lvl);
    this->setTargetList(targets);
}
void CardBase::minionsOnYourFieldWithExactName(Duel* duel, Player* player, const std::string& name)
{
    std::vector<Card*> targets = TargetList::allMinionsOnField(duel);
    targets = TargetList::filterPlayer(targets, player);
    targets = TargetList::filterOutCardType(targets, 0);
    targets = TargetList::filterCardName(targets, name);
    this->setTargetList(targets);
}
void CardBase::minionsOnYourFieldWithOneOfTwoElementsAndMinimumLevel(Duel* duel, Player* player, const std::string& element1, const std::string& element2, short lvl)
{
    std::vector<Card*> targets = TargetList::allMinionsOnField(duel);
    targets = TargetList::filterPlayer(targets, player);
    targets = TargetList::filterOutCardType(targets, 0);
    targets = TargetList::filterTwoElements(targets, element1, element2);
    targets = TargetList::filterLevelRange(targets, lvl, 100);
    this->setTargetList(targets);
}
void CardBase::minionsOnYourFieldWithOneOfTwoElements(Duel* duel, Player* player, const std::string& element1, const std::string& element2)
{
    std::vector<Card*> targets = TargetList::allMinionsOnField(duel);
    targets = TargetList::filterPlayer(targets, player);
    targets = TargetList::filterOutCardType(targets, 0);
    targets = TargetList::filterTwoElements(targets, element1, element2);
    this->setTargetList(targets);
}
void CardBase::nTopCardsFromDeck(Player* player, short n)
{
    std::vector<Card*> targets = TargetList::cardsInDeck(player);
    targets = TargetList::nTopCards(targets, n);
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
short CardBase::highestOriginalLevelInTargetList()
{
    short lvl = -1;
    short nt = this->getTargetList()->getTargetsNumber();
    std::vector<Card*>* targets = this->getTargetList()->getTargetList();

    for (short i = 0; i<nt; i++)
    {
        short card_lvl = targets->at(i)->getOriginalLevel();
        if (card_lvl>lvl) {lvl = card_lvl;}
    }
    return lvl;
}
void CardBase::specialMinionsOnYourFieldSpecialSummonedWithElement(Duel* duel, Player* player, const std::string& element)
{
    std::vector<Card*> targets = TargetList::allMinionsOnField(duel);
    targets = TargetList::filterPlayer(targets, player);
    targets = TargetList::filterCardType(targets, 2);
    targets = TargetList::filterHavingElementInMaterialList(targets, element);
    this->setTargetList(targets);
}








