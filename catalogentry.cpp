#include "catalogentry.h"

CatalogEntry::CatalogEntry()
{

}
CatalogEntry::CatalogEntry(int id, char const* cardName, char const* cardElement, short cardCost, char cardType, short level, short attack, short defence)
{
    this->cardId=id;
    this->cardName = new char[strlen(cardName)+1];
    strcpy(this->cardName, cardName);
    this->cardElement = new char[strlen(cardElement)+1];
    strcpy(this->cardElement,cardElement);
    this->level=level;
    this->attack = attack;
    this->defence = defence;
    this->cardCost=cardCost;
    this->cardType=cardType;
}
