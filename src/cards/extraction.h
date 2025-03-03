#ifndef EXTRACTION_H
#define EXTRACTION_H
#include "cardbase.h"
class Extraction : public CardBase
{
public:
    Extraction():CardBase(
        1011, //card id
        5, //cost
        0, //card type (0 - spell, 1 - minion, 2 - spminion)
        -1, //level
        -1, //attack
        -1, //defence
        "Earth", //element
        "Extraction", //name
        "Extraction",
        ""
    ) {this->setHasOnSpell(1);};
    bool onSpell(Duel* duel, Card* card) override;

};

#endif
