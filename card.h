#ifndef CARD_H
#define CARD_H
#include "cardcatalog.h"
#include <cstring>
class Zone;
class Player;

class Card
{
private:
Zone* zone;
Player* owner;
Player* originalOwner;
short place; //0 - deck, 1 - hand, 2 - field, 3 - GY, 4 - servant deck
short cardType; //0 - spell, 1 - minion, 2 - servant
short cardId;
short cost;
char* element;
char* name;
short level;
short attack;
short defence;
public:
    Card();
    Card(int entryId);
    void setZone(Zone* zone){this->zone = zone;}
    Zone* getZone() {return this->zone;}
    void setOwner(Player* owner){this->owner = owner;}
    Player* getOwner() {return this->owner;}
    void setOriginalOwner(Player* owner){this->originalOwner = owner;}
    Player* getOriginalOwner() {return this->originalOwner;}
    short getCost() {return this->cost;}
    void setCost(short cost) {this->cost = cost;}
    short getCardId() {return this->cardId;}
    void setCardId(short id) {this->cardId = id;}
    void setPlace(short place) {this->place = place;}
    char getCardType() {return this->cardType;}
    void setCardType(short type) {this->cardType = type;}
    char getPlace() {return this->place;}
    char* getElement() {return this->element;}
    char* getName() {return this->name;}
    void setElement(char const* element) {this->element = new char[strlen(element)+1];strcpy(this->element,element);}
    void setName(char const* name) {this->name = new char[strlen(name)+1];strcpy(this->name,name);}
    short getAttack() {return this->attack;}
    void setAttack(short atk) {this->attack = atk;}
    short getDefence() {return this->defence;}
    void setDefence(short def) {this->defence = def;}
};
#endif // CARD_H
