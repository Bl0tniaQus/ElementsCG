#ifndef ZONE_H
#define ZONE_H
class Card;

class Zone
{
private:
    short id;
    char zoneType; //0 - spell, 1 - minion
    Card* card;
    bool used;
public:
    Zone() {this->used=false; this->card=nullptr;};
    short getId() {return id;};
    void setId(short id) {this->id = id;}
    void setZoneType(int type) {this->zoneType = type;}
    void bindCard(Card* card);
    void destroyCard();
    Card* getCard() {return this->card;}
    bool getUsed() {return this->used;}
    void setUsed(bool u) {this->used = u;}
};

#endif // ZONE_H
