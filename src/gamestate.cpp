#include "gamestate.h"
#include "zone.h"
#include "card.h"
#include <iostream>
Gamestate::Gamestate()
{

}
Gamestate::Gamestate(Duel* duel)
{
    this->setTurnCount(duel->getTurnCount());
    this->setTurnPlayer(duel->getTurnPlayer());

    short** usedZonesArr = new short*[2];
    short* cardsOnFieldArr = new short[2];
    int** fieldCardsArr = new int*[2];
    Player* player;
    Player* player_new;
    for (int i=0;i<2;i++)
    {
        player = duel->getPlayer(i);
        player_new = this->getPlayer(i);
        player_new->setHp(player->getHp());
        player_new->setMana(player->getMana());
        player_new->setName(player->getName());
        player_new->setOpponent(this->getPlayer(!i));

        short handSize = player->getHandSize();
        player_new->setHandSize(handSize);
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
                    for (int k=0;k<cardsOnField;k++)
                    {
                        new_usedZones[k] = usedZones[k];
                        new_fieldCards[k] = fieldCards[k];
                    }
                    new_usedZones[cardsOnField-1] = field->getId();
                    new_fieldCards[cardsOnField-1] = field->getCard()->getCopyId();
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
                //delete[] new_fieldCards;
                //delete[] new_usedZones;
            }
        }

        short graveyardSize = player->getGraveyardSize();
        player_new->setGraveyardSize(graveyardSize);
        int* cardsInGraveyard = new int [graveyardSize];
        Card** graveyard = player->getGraveyard();
        for (int j=0;j<graveyardSize;j++){cardsInGraveyard[j] = graveyard[j]->getCopyId();}

        short deckSize = player->getDeckSize();
        player_new->setDeckSize(deckSize);
        int* cardsInDeck = new int [deckSize];
        Card** deck = player->getDeck();
        for (int j=0;j<deckSize;j++){cardsInDeck[j] = deck[j]->getCopyId();}

        short specialDeckSize = player->getSpecialDeckSize();
        player_new->setSpecialDeckSize(specialDeckSize);
        int* cardsInSpecialDeck = new int [specialDeckSize];
        Card** specialDeck = player->getSpecialDeck();
        for (int j=0;j<specialDeckSize;j++){cardsInSpecialDeck[j] = specialDeck[j]->getCopyId();}
        short originalDeckSize = player->getOriginalDeckSize();
        player_new->setOriginalDeckSize(originalDeckSize);
        short originalSpecialDeckSize = player->getOriginalSpecialDeckSize();
        player_new->setOriginalDeckSize(originalSpecialDeckSize);

        Card* originalDeck = player->getOriginalDeck();
        Card* originalSpecialDeck = player->getOriginalSpecialDeck();
        Card* d = new Card [originalDeckSize];
        player_new->setOriginalDeck(d, originalDeckSize);
        Card* originalDeckCopy = player_new->getOriginalDeck();
        for (int j=0;j<originalDeckSize;j++)
        {
            originalDeckCopy[j].copyProperties(&originalDeck[j]);
        }
        Card* sd = new Card [originalSpecialDeckSize];
        player_new->setOriginalSpecialDeck(sd,originalSpecialDeckSize);
        Card* originalSpecialDeckCopy = player_new->getOriginalSpecialDeck();
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
                    deckCopy[j] = &originalDeckCopy[k];
                    break;
                }
            }
        }
        Card** specialDeckCopy = new Card* [specialDeckSize];
        for (int j=0;j<specialDeckSize;j++)
        {
            int id = cardsInSpecialDeck[j];
            for (int k=0;k<originalSpecialDeckSize;k++)
            {
                int originalId = originalSpecialDeckCopy[k].getCopyId();
                if (id==originalId)
                {
                    specialDeckCopy[j] = &originalSpecialDeckCopy[k];
                    break;
                }
            }
        }
        player_new->setDeck(deckCopy,deckSize);
        player_new->setSpecialDeck(specialDeck,specialDeckSize);
        player_new->setDeckOwnership();
        Card** handCopy = new Card* [handSize];
        for (int j=0;j<handSize;j++)
        {
            int id = cardsInHand[j];
            for (int k=0;k<originalDeckSize;k++)
            {
                int originalId = originalDeckCopy[k].getCopyId();
                if (id==originalId)
                {
                    handCopy[j] = &originalDeck[k];
                    break;
                }
            }
        }
        Card** graveyardCopy = new Card* [graveyardSize];
        for (int j=0;j<graveyardSize;j++)
        {
            int id = cardsInGraveyard[j];
            for (int k=0;k<originalDeckSize;k++)
            {
                int originalId = originalDeckCopy[k].getCopyId();
                if (id==originalId)
                {
                    graveyardCopy[j] = &originalDeck[k];
                    break;
                }
            }
        }

        player_new->setHand(handCopy,handSize);
        player_new->setGraveyard(graveyardCopy,graveyardSize);

        usedZonesArr[i] = usedZones;
        cardsOnFieldArr[i] = cardsOnField;
        fieldCardsArr[i] = fieldCards;
        //delete[] d;
        //delete[] sd;
       // delete[] cardsInHand;
        //delete[] cardsInGraveyard;
       // delete[] cardsInDeck;
       // delete[] cardsInSpecialDeck;
       // delete[] handCopy;
       // delete[] graveyardCopy;
       // delete[] deckCopy;
       // delete[] specialDeckCopy;
    }
    for (int i=0;i<2;i++)
    {
        Card* originalDeck = this->getPlayer(i)->getOriginalDeck();
        short originalDeckSize = this->getPlayer(i)->getOriginalDeckSize();
        Card* originalDeckOpp = this->getPlayer(!i)->getOriginalDeck();
        short originalDeckSizeOpp = this->getPlayer(!i)->getOriginalDeckSize();
        for (int j = 0; j<cardsOnFieldArr[i];j++)
        {
            bool found = false;
            short zone = usedZonesArr[i][j];
            int id = fieldCardsArr[i][j];
            for (int k = 0; k<originalDeckSize;k++)
            {
                int originalId = originalDeck[k].getCopyId();
                if (id==originalId)
                {
                    this->getPlayer(i)->getMinionField()[zone].bindCard(&originalDeck[k]);
                    this->getPlayer(i)->getMinionField()[zone].setUsed(true);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                for (int k = 0; k<originalDeckSizeOpp;k++)
            {
                int originalId = originalDeckOpp[k].getCopyId();
                if (id==originalId)
                {
                    originalDeckOpp[k].setOwner(this->getPlayer(i));
                    this->getPlayer(i)->getMinionField()[zone].bindCard(&originalDeckOpp[k]);
                    found = true;
                    break;
                }
            }
            }
        }

    }
}
float Gamestate::evaluate()
{
    return (float)(rand()%10 + 0);
}

