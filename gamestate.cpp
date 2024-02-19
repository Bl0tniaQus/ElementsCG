#include "gamestate.h"
#include "zone.h"
#include "card.h"
Gamestate::Gamestate()
{

}
Gamestate::Gamestate(Duel* duel)
{
    this->turnCount = duel->getTurnCount();
    this->turnPlayer = duel->getTurnPlayer();
    for (int i=0;i<2;i++)
    {
        Player *player = duel->getPlayer(i);
        this->players[i].setHp(player->getHp());
        this->players[i].setMana(player->getMana());
        this->players[i].setName(player->getName());
        this->players[i].setOpponent(duel->getPlayer(!i));

        short handSize = player->getHandSize();
        this->players[i].setHandSize(handSize);
        int* cardsInHand = new int [handSize];
        Card** hand = player->getHand();
        for (int i=0;i<handSize;i++)
        {cardsInHand[i] = hand[i]->getCopyId();}

        short cardsOnField = 0;
        short* usedZones = new short[0];
        int* fieldCards = new int[0];
        Zone *field = player->getMinionField();
        for (int i=0;i<5;i++)
        {
            if (field[i].getUsed())
            {
                cardsOnField++;
                short *new_usedZones = new short[cardsOnField];
                int *new_fieldCards = new int[cardsOnField];
                if (cardsOnField>1)
                {
                    for (int j=0;j<cardsOnField-1;j++)
                    {
                        new_usedZones[j] = usedZones[j];
                        new_fieldCards[j] = fieldCards[j];
                    }
                    new_usedZones[cardsOnField] = field->getId();
                    new_fieldCards[cardsOnField] = field->getCard()->getCopyId();
                }
                else
                {
                    new_usedZones[0] = field->getId();
                    new_fieldCards[0] = field->getCard()->getCopyId();
                }
                delete[] usedZones;
                delete[] fieldCards;
                fieldCards = new_fieldCards;
                usedZones = new_usedZones;

            }
        }

        short graveyardSize = player->getGraveyardSize();
        this->players[i].setGraveyardSize(graveyardSize);
        int* cardsInGraveyard = new int [graveyardSize];
        Card** graveyard = player->getGraveyard();
        for (int i=0;i<graveyardSize;i++){cardsInGraveyard[i] = graveyard[i]->getCopyId();}

        short deckSize = player->getDeckSize();
        this->players[i].setDeckSize(deckSize);
        int* cardsInDeck = new int [deckSize];
        Card** deck = player->getDeck();
        for (int i=0;i<deckSize;i++){cardsInDeck[i] = deck[i]->getCopyId();}

        short specialDeckSize = player->getSpecialDeckSize();
        this->players[i].setSpecialDeckSize(specialDeckSize);
        int* cardsInSpecialDeck = new int [specialDeckSize];
        Card** specialDeck = player->getSpecialDeck();
        for (int i=0;i<specialDeckSize;i++){cardsInSpecialDeck[i] = specialDeck[i]->getCopyId();}
        short originalDeckSize = player->getOriginalDeckSize();
        this->players[i].setOriginalDeckSize(originalDeckSize);
        short originalSpecialDeckSize = player->getOriginalSpecialDeckSize();
        this->players[i].setOriginalDeckSize(originalSpecialDeckSize);

        Card* originalDeck = player->getOriginalDeck();
        Card* originalSpecialDeck = player->getOriginalSpecialDeck();

        this->players[i].setOriginalDeck(new Card [originalDeckSize],originalDeckSize);
        Card* originalDeckCopy = this->players[i].getOriginalDeck();
        for (int i=0;i<originalDeckSize;i++)
        {
            originalDeckCopy[i].copyProperties(&originalDeck[i]);
        }


        this->players[i].setOriginalSpecialDeck(new Card [originalSpecialDeckSize],originalSpecialDeckSize);

    }
}
