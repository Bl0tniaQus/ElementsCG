#include "card.h"
#include "globals.h"
Card::Card()
{

}
Card::Card(int entryId)
{
CatalogEntry* entry = catalog.getEntryByCardId(entryId);
if (entry!=nullptr)
{
    this->copyId = ++Card::COPYID;
    this->cost = entry->getCost();
    this->cardType=entry->getType();
    this->attacks = 1;
    if (this->cardType==2) {this->place = 4;}
    else {this->place = 0;}
    this->attack = entry->getAttack();
    this->defence = entry->getDefence();
    this->level = entry->getLevel();
    this->setElement(entry->getElement());
    this->setName(entry->getName());
    this->cardId = entry->getId();
    this->originalAttack = this->attack;
    this->originalDefence = this->defence;
    this->originalLevel = this->level;
    this->zone = nullptr;
}}
void Card::copyProperties(Card* card)
{
    this->copyId = card->getCopyId();
    this->cost = card->getCost();
    this->cardType = card->getCardType();
    this->attacks = card->attacks;
    this->place = card->place;
    this->attack = card->getAttack();
    this->defence = card->getDefence();
    this->level = card->getLevel();
    this->setElement(card->getElement());
    this->setName(card->getName());
    this->cardId = card->getCardId();
    this->originalAttack = card->getOriginalAttack();
    this->originalDefence = card->getOriginalDefence();
    this->originalLevel = card->getOriginalLevel();
    this->owner = card->getOwner();
    this->originalOwner = card->getOriginalOwner();
    //this->zone = card->getZone();
}
