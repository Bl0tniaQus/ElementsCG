#ifndef CARDBASE_H
#define CARDBASE_H
class Card;
class Duel;
class TargetList;
class CardBase
{
private:
    short cardId;
    short cost;
    short cardType;
    short level;
    short attack;
    short defence;
    char* element;
    char* name;
    Card* cardEntity;
    TargetList* targetList;
protected:
    CardBase(short cid, short c, short ct, short l, short a, short d, const char* el, const char* n);
public:
    CardBase() {};
    void bindCard(Card* card) {this->cardEntity = card;}
    short getCardId() {return this->cardId;}
    short getCost() {return this->cost;}
    short getCardType() {return this->cardType;}
    short getLevel() {return this->level;}
    short getAttack() {return this->attack;}
    short getDefence() {return this->defence;}
    char* getElement() {return this->element;}
    char* getName() {return this->name;}
    Card* getCardEntity() {return this->cardEntity;}
    TargetList* getTargetList() {return this->targetList;}
    void setTargetList(Card** tl, short n);
    virtual void onSummon(Duel* duel, Card* card) {};
    virtual bool onSpell(Duel* duel, Card* card) {return false;};
    virtual void onDestroy(Duel* duel, Card* card) {};
    virtual void onAttack(Duel* duel, Card* card) {};
    virtual void onDefence(Duel* duel, Card* card) {};
    virtual void onTurnEnd(Duel* duel, Card* card) {};
    virtual void getOnSummonTargetList(Duel* duel, Card* card) {};
    virtual void getOnSpellTargetList(Duel* duel, Card* card) {};
    virtual void getOnAttackTargetList(Duel* duel, Card* card) {};
    virtual void getOnDefenceTargetList(Duel* duel, Card* card) {};
    virtual void getOnDestroyTargetList(Duel* duel, Card* card) {};
    virtual void getOnTurnEndTargetList(Duel* duel, Card* card) {};

    //common Targets
    void minionsOnField(Duel* duel, Card* card);
    void cardsInHandWithTheSameName(Duel* duel, Card* card);
};

#endif
