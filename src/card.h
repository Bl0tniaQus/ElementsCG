#ifndef CARD_H
#define CARD_H
#include <cstring>
#include "cards/cardbase.h"
#include "cards/allcardsinclude.h"
class Zone;
class Player;
class Card
{
protected:

private:
static int COPYID;
Zone* zone;
Player* owner;
Player* originalOwner;
CardBase* cardName; //name of the card in database
short place; //0 - deck, 1 - hand, 2 - field, 3 - GY, 4 - special deck
int copyId;
short cost;
short level;
short attack;
short defence;
short attacks;
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
    short getCardId() {return this->cardName->getCardId();}
    void setPlace(short place) {this->place = place;}
    char getCardType() {return this->cardName->getCardType();}
    char getPlace() {return this->place;}
    const char* getElement() {return this->cardName->getElement();}
    const char* getName() {return this->cardName->getName();}
    short getAttack() {return this->attack;}
    void setAttack(short atk) {this->attack = atk;}
    short getDefence() {return this->defence;}
    void setDefence(short def) {this->defence = def;}
    short getOriginalAttack() {return this->cardName->getAttack();}
    short getOriginalDefence() {return this->cardName->getDefence();}
    short getLevel() {return this->level;}
    void setLevel(short lvl) {this->level = lvl;}
    short getOriginalLevel() {return this->cardName->getLevel();}
    void setAttacks(short atk) {this->attacks=atk;}
    short getAttacks() {return this->attacks;}
    int getCopyId() {return this->copyId;}
    void setCopyId(int id) {this->copyId = id;}
    void copyProperties(Card* card);
    CardBase* getCardName() {return this->cardName;}
    CardBase* getCardNameById(int id);
};
#endif // CARD_H
