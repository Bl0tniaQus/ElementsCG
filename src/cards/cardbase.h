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
    short cardType; //(0 - spell, 1 - minion, 2 - spminion)
    short level;
    short attack;
    short defence;
    short materials = 0;
    char* element;
    char* name;
    char* image;
    char* cardText;
    Card* cardEntity;
    TargetList* targetList;
public:
    CardBase() {};
    virtual ~CardBase() {}
    CardBase(short cid, short c, short ct, short l, short a, short d, const char* el, const char* n, const char* i, const char* ctx);
    void bindCard(Card* card) {this->cardEntity = card;}
    short getCardId() {return this->cardId;}
    short getCost() {return this->cost;}
    short getCardType() {return this->cardType;}
    short getLevel() {return this->level;}
    short getAttack() {return this->attack;}
    char* getCardText() {return this->cardText;}
    void setMaterialNumber(short n) {this->materials = n;}
    short getMaterialNumber() {return this->materials;}
    short getDefence() {return this->defence;}
    char* getElement() {return this->element;}
    char* getName() {return this->name;}
    char* getImage() {return this->image;}
    Card* getCardEntity() {return this->cardEntity;}
    TargetList* getTargetList() {return this->targetList;}
    void setTargetList(Card** tl, short n);
    void spellCost(Card* card);
    void effectLog(Duel* duel, Card* card);
    void firstEffectLog(Duel* duel, Card* card);
    void secondEffectLog(Duel* duel, Card* card);
    void thirdEffectLog(Duel* duel, Card* card);
    void spellCostLog(Duel* duel, Card* card);

    void release2Log(Card* c1, Card* c2, Duel* duel);
    void release3Log(Card* c1, Card* c2, Card* c3, Duel* duel);

    virtual void onSummon(Duel* duel, Card* card) {};
    virtual bool onSpell(Duel* duel, Card* card) {return false;};
    virtual void onDestroy(Duel* duel, Card* card) {};
    virtual void onAttack(Duel* duel, Card* card, Card* target) {};
    virtual void afterAttack(Duel* duel, Card* card, Card* target, short damage) {};
    virtual void onDefence(Duel* duel, Card* card, Card* attacker) {};
    virtual void afterDefence(Duel* duel, Card* card, Card* attacker, short damage) {};
    virtual void onTurnEnd(Duel* duel, Card* card) {};
    virtual void onTurnStart(Duel* duel, Card* card);
    virtual void getOnSummonTargetList(Duel* duel, Card* card) {};
    virtual void getOnSpellTargetList(Duel* duel, Card* card) {};
    virtual void getOnAttackTargetList(Duel* duel, Card* card) {};
    virtual void getAfterAttackTargetList(Duel* duel, Card* card) {};
    virtual void getOnDefenceTargetList(Duel* duel, Card* card) {};
    virtual void getOnDestroyTargetList(Duel* duel, Card* card) {};
    virtual void getOnTurnEndTargetList(Duel* duel, Card* card) {};

    short singleChoice(Duel* duel, Card* card);
    //common effect targets
    void allMinionsOnField(Duel* duel, Card* card);
    void cardsInHandWithTheSameName(Duel* duel, Card* card);
    void cardsInHandWithCommonNamePart(Duel* duel, Card* card, const char* namePart);
    void cardsInDeckWithCommonNamePart(Duel* duel, Card* card, const char* namePart);
    void minionsInYourGraveyardWithSameElementAndMaximumLevel(Duel* duel, Card* card, const char* element, short lvl);
    void specialMinionsInYourGraveyardWithSameElement(Duel* duel, Card* card, const char* element);
    void minionsOnYourFieldWithCommonNamePart(Duel* duel, Card* card, const char* namePart);
    void minionsOnYourFieldWithSameElement(Duel* duel, Card* card, const char* element);
    void minionsOnYourFieldWithSameElementAndMinimumLevel(Duel* duel, Card* card, const char* element, short lvl);
    void minionsOnYourFieldWithSameElementAndMaximumLevel(Duel* duel, Card* card, const char* element, short lvl);
    void minionsOnYourFieldWithExactName(Duel* duel, Card* card, const char* name);


    bool checkSummoningConditions2(Duel* duel, Card* card);
    bool checkSummoningConditions3(Duel* duel, Card* card);
    virtual bool specialSummon(Duel* duel, Card* card) {return false;};
    bool specialSummon2(Duel* duel, Card* card);
    bool specialSummon3(Duel* duel, Card* card) {return false;};
    virtual void getFirstMaterialList(Duel* duel, Card* card) {};
    virtual void getSecondMaterialList(Duel* duel, Card* card) {};
    virtual void getThirdMaterialList(Duel* duel, Card* card) {};



};

#endif
