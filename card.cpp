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
    this->setCost(entry->getCost());
    this->setCardType(entry->getType());
    this->attacks=1;
    if (this->cardType==2) {this->setPlace(4);}
    else {this->setPlace(0);}
    this->setAttack(entry->getAttack());
    this->setDefence(entry->getDefence());
    this->setElement(entry->getElement());
    this->setName(entry->getName());
    this->setCardId(entry->getId());
    this->setOriginalAttack(this->attack);
    this->setOriginalDefence(this->defence);
    this->setOriginalLevel(this->level);
    this->zone = nullptr;
}}
