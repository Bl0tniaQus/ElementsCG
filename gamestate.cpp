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
        for (int j=0;j<5;j++)
        {
            if (field[j].getUsed())
            {
                cardsOnField++;
                short *new_usedZones = new short[cardsOnField];
                int *new_fieldCards = new int[cardsOnField];
                if (cardsOnField>1)
                {
                    for (int k=0;k<cardsOnField-1;k++)
                    {
                        new_usedZones[k] = usedZones[k];
                        new_fieldCards[k] = fieldCards[k];
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
        for (int j=0;j<graveyardSize;j++){cardsInGraveyard[j] = graveyard[j]->getCopyId();}

        short deckSize = player->getDeckSize();
        this->players[i].setDeckSize(deckSize);
        int* cardsInDeck = new int [deckSize];
        Card** deck = player->getDeck();
        for (int j=0;j<deckSize;j++){cardsInDeck[j] = deck[j]->getCopyId();}

        short specialDeckSize = player->getSpecialDeckSize();
        this->players[i].setSpecialDeckSize(specialDeckSize);
        int* cardsInSpecialDeck = new int [specialDeckSize];
        Card** specialDeck = player->getSpecialDeck();
        for (int j=0;j<specialDeckSize;j++){cardsInSpecialDeck[j] = specialDeck[j]->getCopyId();}
        short originalDeckSize = player->getOriginalDeckSize();
        this->players[i].setOriginalDeckSize(originalDeckSize);
        short originalSpecialDeckSize = player->getOriginalSpecialDeckSize();
        this->players[i].setOriginalDeckSize(originalSpecialDeckSize);

        Card* originalDeck = player->getOriginalDeck();
        Card* originalSpecialDeck = player->getOriginalSpecialDeck();

        this->players[i].setOriginalDeck(new Card [originalDeckSize],originalDeckSize);
        Card* originalDeckCopy = this->players[i].getOriginalDeck();
        for (int j=0;j<originalDeckSize;j++)
        {
            originalDeckCopy[j].copyProperties(&originalDeck[j]);
        }

        this->players[i].setOriginalSpecialDeck(new Card [originalSpecialDeckSize],originalSpecialDeckSize);
        Card* originalSpecialDeckCopy = this->players[i].getOriginalSpecialDeck();
        for (int j=0;j<originalSpecialDeckSize;j++)
        {
            originalSpecialDeckCopy[j].copyProperties(&originalSpecialDeck[j]);
        }
        Card** deckCopy = new Card* [deckSize];
        for (int j=0;j<deckSize;j++)
        {
            int id = cardsInDeck[j];
            for (int k=0;k<originalDeckSize;k++)
            {
                int originalId = originalDeckCopy[k].getCopyId();
                if (id==originalId)
                {
                    deckCopy[j] = &originalDeckCopy[k]; break;
                }
            }
        }
        this->players[i].setDeck(deckCopy,deckSize);
        this->players[i].setDeckOwnership();
        //ownerzy kart do poprawy, potem zrobić kopie GY, handu, pola i sp decku i powinno być wszystko
    }
}
