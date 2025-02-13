#include "card.h"
#include "globals.h"
#include "zone.h"
#include "player.h"
Card::Card()
{
    this->cardName = new CardBase;
}
Card::Card(int entryId)
{
    delete this->cardName;
    this->cardName = getCardNameById(entryId);
    this->cardName->bindCard(this);
    this->copyId = ++Card::COPYID;
    this->attacks = 1;
    if (this->getCardType()==2) {this->place = 4;}
    else {this->place = 0;}
    this->cost = this->cardName->getCost();
    this->attack = this->cardName->getAttack();
    this->defence = this->cardName->getDefence();
    this->level = this->cardName->getLevel();
    this->barrier = 0;
    this->isNegated = false;
    this->isSpellImmune = false;
    this->zone = nullptr;
    this->turnPlayed = -1;
}
void Card::getValuesFromId(int entryId, bool noCopyId)
{
    if (!noCopyId) {this->copyId = ++Card::COPYID;}
    delete this->cardName;
    this->cardName = getCardNameById(entryId);
    this->cardName->bindCard(this);
    this->attacks = 1;
    if (this->getCardType()==2) {this->place = 4;}
    else {this->place = 0;}
    this->cost = this->cardName->getCost();
    this->attack = this->cardName->getAttack();
    this->defence = this->cardName->getDefence();
    this->level = this->cardName->getLevel();
    this->barrier = 0;
    this->isNegated = false;
    this->isSpellImmune = false;
    this->zone = nullptr;
    this->turnPlayed = -1;
}
void Card::copyProperties(Card* card)
{
    this->copyId = card->getCopyId();
    this->cost = card->getCost();
    this->attacks = card->attacks;
    this->place = card->place;
    this->attack = card->getAttack();
    this->defence = card->getDefence();
    this->level = card->getLevel();
    delete this->cardName;
    this->cardName = getCardNameById(card->getCardId());
    this->cardName->bindCard(this);
    this->barrier = card->getBarrier();
    this->isNegated = card->getIsNegated();
    this->isSpellImmune = card->getIsSpellImmune();
    this->turnPlayed = card->getTurnPlayed();
}
void Card::copyCardName(CardBase* c)
{
    this->cardName->copy(this->getOwner()->getDuel(), c);
}

CardBase* Card::getCardNameById(int id)
{
    CardBase* cardbase;
    switch (id)
    {
        case 0: cardbase = new GearToken; break;

        case 1000: cardbase = new CopperWorm;break;
        case 1001: cardbase = new SilverWolf;break;
        case 1002: cardbase = new TungstenFirefly;break;
        case 1003: cardbase = new Excavation;break;
        case 1004: cardbase = new AluminiumSerpent;break;
        case 1005: cardbase = new LithiumLizard;break;
        case 1006: cardbase = new Magnetize;break;
        case 1007: cardbase = new TopazAmberFossil;break;
        case 1008: cardbase = new Earthquake;break;
        case 1009: cardbase = new Recycle;break;
        case 1010: cardbase = new Disassembly;break;
        case 1011: cardbase = new Extraction;break;
        case 1012: cardbase = new ShieldBash;break;
        case 1013: cardbase = new IrisVersicolor;break;

        case 1500: cardbase = new BrassBeetle;break;
        case 1501: cardbase = new AmberTreant;break;
        case 1502: cardbase = new SteelCentipede;break;
        case 1503: cardbase = new TopazMantis;break;

        case 2000: cardbase = new DragonoidWarrior;break;
        case 2001: cardbase = new Whirlwind;break;
        case 2002: cardbase = new DragonoidSage;break;
        case 2003: cardbase = new DragonoidScout;break;
        case 2004: cardbase = new HappyCumulus;break;
        case 2005: cardbase = new SadNimbus;break;
        case 2006: cardbase = new Lightning;break;
        case 2007: cardbase = new DragonoidCall;break;
        case 2008: cardbase = new Breeze;break;
        case 2009: cardbase = new WyvernHatchling;break;
        case 2010: cardbase = new SupplyDrop;break;
        case 2011: cardbase = new PaperAirplane;break;
        case 2012: cardbase = new BarrelRoll;break;
        case 2013: cardbase = new WindUpCopter;break;
        case 2014: cardbase = new Nailpecker;break;
        case 2015: cardbase = new WindUpOverload;break;
        case 2016: cardbase = new FlyingLizard;break;
        case 2017: cardbase = new WindUpRestart;break;
        case 2018: cardbase = new SupplyBaloon;break;

        case 2500: cardbase = new TempestWyvern;break;
        case 2501: cardbase = new YoungWyvern;break;
        case 2502: cardbase = new DragonoidStormChaser;break;
        case 2503: cardbase = new AngryCumulonimbus;break;
        case 2504: cardbase = new DrillDragon;break;
        case 2505: cardbase = new WindUpAirplane;break;
        case 2506: cardbase = new WindUpBiplane;break;

        default: cardbase = new CardBase; break;
    }
    return cardbase;
}
Card::~Card()
{
    this->owner = nullptr;
    this->originalOwner = nullptr;
    this->zone = nullptr;
 //if (this->cardName !=nullptr) {delete this->cardName;}
    delete this->cardName;
}
void Card::returnToOriginal()
{
this->attack = this->cardName->getAttack();
this->defence = this->cardName->getDefence();
this->level = this->cardName->getLevel();
this->owner = this->originalOwner;
this->barrier = 0;
this->isNegated = false;
this->isSpellImmune = false;
this->cost = this->cardName->getCost();
}
void Card::resetCardName()
{
    delete this->cardName;
    this->cardName = new CardBase;
}
