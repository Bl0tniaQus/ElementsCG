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
    Card** usedMaterials;
    TargetList* targetList;

    bool hasOnTurnStart = false;
    bool hasOnTurnEnd = false;
    bool hasOnSummon = false;
    bool hasOnSpecialSummon = false;
    bool hasOnAttack = false;
    bool hasAfterAttack = false;
    bool hasOnDefence = false;
    bool hasAfterDefence = false;
    bool hasOnSpecialSummonRelease = false;
    bool hasOnSpell = false;
    bool hasOnDestroy = false;
public:
    CardBase() {};
    virtual ~CardBase();
    CardBase(short cid, short c, short ct, short l, short a, short d, const char* el, const char* n, const char* i, const char* ctx);
    void bindCard(Card* card) {this->cardEntity = card;}
    short getCardId() {return this->cardId;}
    short getCost() {return this->cost;}
    short getCardType() {return this->cardType;}
    short getLevel() {return this->level;}
    short getAttack() {return this->attack;}
    char* getCardText() {return this->cardText;}
    void setMaterialNumber(short n) {this->materials = n;}
    void setTwoMaterials(Card* material1, Card* material2);
    void setThreeMaterials(Card* material1, Card* material2, Card* material3);
    short getMaterialNumber() {return this->materials;}
    short getDefence() {return this->defence;}
    char* getElement() {return this->element;}
    char* getName() {return this->name;}
    char* getImage() {return this->image;}
    Card* getCardEntity() {return this->cardEntity;}


    bool getHasOnTurnStart() {return this->hasOnTurnStart;}
    void setHasOnTurnStart(bool t) {this->hasOnTurnStart = t;}
    bool getHasOnTurnEnd() {return this->hasOnTurnEnd;}
    void setHasOnTurnEnd(bool t) {this->hasOnTurnEnd = t;}
    bool getHasOnSummon() {return this->hasOnSummon;}
    void setHasOnSummon(bool t) {this->hasOnSummon = t;}
    bool getHasOnSpecialSummon() {return this->hasOnSpecialSummon;}
    void setHasOnSpecialSummon(bool t) {this->hasOnSpecialSummon = t;}
    bool getHasOnAttack() {return this->hasOnAttack;}
    void setHasOnAttack(bool t) {this->hasOnAttack = t;}
    bool getHasOnDefence() {return this->hasOnDefence;}
    void setHasOnDefence(bool t) {this->hasOnDefence = t;}
    bool getHasAfterAttack() {return this->hasAfterAttack;}
    void setHasAfterAttack(bool t) {this->hasAfterAttack = t;}
    bool getHasAfterDefence() {return this->hasAfterDefence;}
    void setHasAfterDefence(bool t) {this->hasAfterDefence = t;}
    bool getHasOnDestroy() {return this->hasOnDestroy;}
    void setHasOnDestroy(bool t) {this->hasOnDestroy = t;}
    bool getHasOnSpecialSummonRelease() {return this->hasOnSpecialSummonRelease;}
    void setHasOnSpecialSummonRelease(bool t) {this->hasOnSpecialSummonRelease = t;}
    bool getHasOnSpell() {return this->hasOnSpell;}
    void setHasOnSpell(bool t) {this->hasOnSpell = t;}

    TargetList* getTargetList() {return this->targetList;}
    void setTargetList(Card** tl, short n);
    void clearTargetList();
    void spellCost(Card* card);
    void effectLog(Duel* duel, Card* card);
    void firstEffectLog(Duel* duel, Card* card);
    void secondEffectLog(Duel* duel, Card* card);
    void thirdEffectLog(Duel* duel, Card* card);
    void spellFromHandLog(Duel* duel, Card* card);

    void release2Log(Card* c1, Card* c2, Duel* duel);
    void release3Log(Card* c1, Card* c2, Card* c3, Duel* duel);

    virtual void onSummon(Duel* duel, Card* card) {};
    virtual void onSpecialSummon(Duel* duel, Card* card) {};
    virtual bool onSpell(Duel* duel, Card* card) {return false;};
    virtual void onDestroy(Duel* duel, Card* card) {};
    virtual void onAttack(Duel* duel, Card* card, Card* target) {};
    virtual void afterAttack(Duel* duel, Card* card, Card* target, short damage) {};
    virtual void onDefence(Duel* duel, Card* card, Card* attacker) {};
    virtual void afterDefence(Duel* duel, Card* card, Card* attacker, short damage) {};
    virtual void onTurnEnd(Duel* duel, Card* card) {};
    virtual void onTurnStart(Duel* duel, Card* card);
    virtual void onSpecialSummonRelease(Duel* duel, Card* card, Card* sp_minion) {};

    short singleChoice(Duel* duel, Card* card);
    //common effect targets
    void allMinionsOnField(Duel* duel, Card* card);
    void cardsInHandWithTheSameName(Duel* duel, Card* card);
    void nTopCardsFromDeck(Duel* duel, Card* card, short n);
    void cardsWithSameElementInTargetList(const char* element);
    void cardsInHandWithCommonNamePart(Duel* duel, Card* card, const char* namePart);
    void cardsInDeckWithCommonNamePart(Duel* duel, Card* card, const char* namePart);
    void minionsInYourGraveyardWithSameElementAndMaximumLevel(Duel* duel, Card* card, const char* element, short lvl);
    void cardsInYourGraveyardWithSameElement(Duel* duel, Card* card, const char* element);
    void cardsInYourGraveyardWithExactName(Duel* duel, Card* card, const char* name);
    void specialMinionsInYourGraveyardWithSameElement(Duel* duel, Card* card, const char* element);
    void specialMinionsOnYourFieldWithSameAttribute(Duel* duel, Card* card, const char* element);
    void minionsInHandWithMaximumLevel(Duel* duel, Card* card, short level);
    void minionsOnYourFieldWithCommonNamePart(Duel* duel, Card* card, const char* namePart);
    void minionsOnYourFieldWithSameElement(Duel* duel, Card* card, const char* element);
    void minionsOnYourFieldWithSameElementAndMinimumLevel(Duel* duel, Card* card, const char* element, short lvl);
    void minionsOnYourFieldWithSameElementAndMaximumLevel(Duel* duel, Card* card, const char* element, short lvl);
    void minionsOnYourFieldWithOneOfTwoElementsAndMinimumLevel(Duel* duel, Card* card, const char* element1, const char* element2, short lvl);
    void minionsOnYourFieldWithExactName(Duel* duel, Card* card, const char* name);

    short highestLevelInTargetList();

    bool checkSummoningConditions2(Duel* duel, Card* card);
    bool checkSummoningConditions3(Duel* duel, Card* card);
    virtual bool specialSummon(Duel* duel, Card* card) {return false;};
    bool specialSummon2(Duel* duel, Card* card);
    bool specialSummon3(Duel* duel, Card* card);
    virtual void getFirstMaterialList(Duel* duel, Card* card) {};
    virtual void getSecondMaterialList(Duel* duel, Card* card) {};
    virtual void getThirdMaterialList(Duel* duel, Card* card) {};

    virtual void copy(Duel* duel, CardBase* c) {};
    virtual short getShort(short n) {return -1;};
    virtual Card* getCard(short n) { return nullptr;};
    virtual bool getBool(short n) {return -1;};


};

#endif
