#include "card.h"
#include "globals.h"
Card::Card()
{
    this->cost = 10;
}
Card::Card(int entryId)
{
CatalogEntry* entry = catalog.getEntryByCardId(entryId);
if (entry!=nullptr)
{
    this->setCost(entry->getCost());
    this->setCardType(entry->getType());
    this->setAttack(entry->getAttack());
    this->setDefence(entry->getDefence());
    this->setName(entry->getName());
    this->setCardId(entry->getId());
}}
