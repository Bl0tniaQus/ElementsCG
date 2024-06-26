#include "cardbase.h"
#include <cstring>
CardBase::CardBase(short cid, short c, short ct, short l, short a, short d, const char* el, const char* n)
{
    this->cardId = cid;
    this->cost = c;
    this->cardType = ct;
    this->attack = a;
    this->defence = d;
    this->element = new char[strlen(el)+1];
    strcpy(this->element, el);
    this->name = new char[strlen(n)+1];
    strcpy(this->name, n);
}
