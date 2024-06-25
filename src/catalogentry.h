#ifndef CATALOGENTRY_H
#define CATALOGENTRY_H
#include <cstring>
class CatalogEntry
{
private:
    int cardId;
    char* cardName;
    char* cardElement;
    short cardCost;
    char cardType;
    short level;
    short attack;
    short defence;
public:
    CatalogEntry();
    CatalogEntry(int id, char const* cardName, char const* cardElement, short cardCost, char cardType, short level, short attack, short defence);
    int getId() {return this->cardId;}
    char* getName() {return this->cardName;}
    char* getElement() {return this->cardElement;}
    short getCost() {return this->cardCost;}
    char getType() {return this->cardType;}
    short getAttack() {return this->attack;}
    short getLevel() {return this->level;}
    short getDefence() {return this->defence;}
};

#endif // CATALOGENTRY_H
