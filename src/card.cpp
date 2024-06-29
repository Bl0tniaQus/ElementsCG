#include "card.h"
#include "globals.h"
Card::Card()
{

}
Card::Card(int entryId)
{
    this->cardName = this->getCardNameById(entryId);
    this->cardName->bindCard(this);
    this->copyId = ++Card::COPYID;
    this->attacks = 1;
    if (this->getCardType()==2) {this->place = 4;}
    else {this->place = 0;}
    this->cost = this->cardName->getCost();
    this->attack = this->cardName->getAttack();
    this->defence = this->cardName->getDefence();
    this->level = this->cardName->getLevel();
    this->zone = nullptr;

}
void Card::copyProperties(Card* card)
{
    this->copyId = card->getCopyId();
    this->cost = card->getCost();
    //this->cardType = card->getCardType();
    this->attacks = card->attacks;
    this->place = card->place;
    this->attack = card->getAttack();
    this->defence = card->getDefence();
    this->level = card->getLevel();
    //this->setElement(card->getElement());
    //this->setName(card->getName());
    //this->cardId = card->getCardId();
    //this->originalAttack = card->getOriginalAttack();
    //this->originalDefence = card->getOriginalDefence();
    //this->originalLevel = card->getOriginalLevel();
    //this->owner = card->getOwner();
    //this->originalOwner = card->getOriginalOwner();
    //this->zone = card->getZone();
}
CardBase* Card::getCardNameById(int id)
{
    CardBase* cardbase;
    switch (id)
    {
        case 1: cardbase = new CopperWorm;break;
        case 2: cardbase = new SilverWolf;break;
        case 3: cardbase = new DragonoidWarrior;break;
        case 4: cardbase = new Whirlwind;break;
        case 5: cardbase = new DragonoidSage;break;
        case 6: cardbase = new TungstenFirefly;break;
        case 7: cardbase = new DragonoidScout;break;
        case 8: cardbase = new BrassBeetle;break;
    }
    return cardbase;
}
