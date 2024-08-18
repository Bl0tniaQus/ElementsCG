#include "card.h"
#include "globals.h"
#include "zone.h"
#include "player.h"
Card::Card()
{

}
Card::Card(int entryId)
{
    this->cardName = this->getCardNameById(entryId);
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
}
void Card::getValuesFromId(int entryId)
{
    this->cardName = this->getCardNameById(entryId);
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
    this->cardName = card->getCardNameById(card->getCardId());
    this->cardName->bindCard(this);
    this->barrier = card->getBarrier();
    this->isNegated = card->getIsNegated();
    this->isSpellImmune = card->getIsSpellImmune();
}
CardBase* Card::getCardNameById(int id)
{
    CardBase* cardbase;
    switch (id)
    {
        case 1: cardbase = new CopperWorm;break;
        case 2: cardbase = new SilverWolf;break;
        case 3: cardbase = new DragonoidWarrior;break;
        case 4: cardbase = new Whirlwind;break;
        case 5: cardbase = new DragonoidSage;break;
        case 6: cardbase = new TungstenFirefly;break;
        case 7: cardbase = new DragonoidScout;break;
        case 8: cardbase = new BrassBeetle;break;
        case 9: cardbase = new TempestWyvern;break;
        case 10: cardbase = new HappyCumulus;break;
        case 11: cardbase = new SadNimbus;break;
        case 12: cardbase = new YoungWyvern;break;
        case 13: cardbase = new Lightning;break;
        case 14: cardbase = new DragonoidCall;break;
        case 15: cardbase = new Extraction; break;
        case 16: cardbase = new Excavation; break;
        case 17: cardbase = new AluminiumSerpent; break;
        case 18: cardbase = new LithiumLizard; break;
        case 19: cardbase = new DragonoidStormChaser; break;
        case 20: cardbase = new AmberTreant; break;
        case 21: cardbase = new SteelCentipede; break;
        case 22: cardbase = new TopazMantis; break;
        case 23: cardbase = new AngryCumulonimbus; break;
        case 24: cardbase = new Breeze; break;
        case 25: cardbase = new WyvernHatchling; break;
        case 26: cardbase = new ShieldBash; break;
        case 27: cardbase = new Magnetize; break;
        case 28: cardbase = new TopazAmberFossil; break;
        case 29: cardbase = new Earthquake; break;
        case 30: cardbase = new Recycle; break;
        case 31: cardbase = new SupplyDrop; break;
    }
    return cardbase;
}
Card::~Card()
{
    this->owner = nullptr;
    this->originalOwner = nullptr;
    this->zone = nullptr;
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
