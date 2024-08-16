#ifndef ANGRYCUMULONIMBUS_H
#define ANGRYCUMULONIMBUS_H
#include "cardbase.h"
class AngryCumulonimbus : public CardBase
{
public:
    AngryCumulonimbus():CardBase(
        23, //card id
        5, //cost
        2, //card type (0 - spell, 1 - minion, 2 - spminion)
        5, //level
        1, //attack
        3, //defence
        "Air", //element
        "Angry Cumulonimbus", //name
        "angrycumulonimbus",
        "[\"Happy Cumulus\" + \"Sad Nimbus\"]\nWhen this card is summoned: gain 1 attack for every 4 mana points you have."
    ) {this->setMaterialNumber(2);};
    bool specialSummon(Duel* duel, Card* card) override;
    void getFirstMaterialList(Duel * duel, Card * card) override;
    void getSecondMaterialList(Duel* duel, Card* card) override;
    void onSummon(Duel* duel, Card* card) override;
};

#endif
