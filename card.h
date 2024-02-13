#ifndef CARD_H
#define CARD_H
#include "cardcatalog.h"
#include <cstring>
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
short place; //0 - deck, 1 - hand, 2 - field, 3 - GY, 4 - special deck
short cardType; //0 - spell, 1 - minion, 2 - special minion
short cardId;
int copyId;
short cost;
char* element; char* originalElement;
char* name;
short level; short originalLevel;
short attack; short originalAttack;
short defence; short originalDefence;
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
    short getOriginalAttack() {return this->originalAttack;}
    void setOriginalAttack(short atk) {this->originalAttack = atk;}
    short getOriginalDefence() {return this->originalDefence;}
    void setOriginalDefence(short def) {this->originalDefence = def;}
    short getLevel() {return this->level;}
    void setLevel(short lvl) {this->level = lvl;}
    short getOriginalLevel() {return this->originalLevel;}
    void setOriginalLevel(short lvl) {this->originalLevel = lvl;}
    void setAttacks(short atk) {this->attacks=atk;}
    short getAttacks() {return this->attacks;}
    int getCopyId() {return this->copyId;}
    void setCopyId(int id) {this->copyId = id;}
    void copyProperties(Card* card);
};
#endif // CARD_H
