#include "gamestate.h"
#include "zone.h"
#include "card.h"
#include <iostream>
Gamestate::Gamestate()
{

}
Gamestate::Gamestate(Duel* duel):Duel()
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
        if (player->getBot()!=nullptr) {player_new->setBot(player->getBot());}
        //player_new->setOpponent(this->getPlayer(!i));

        short handSize = player->getHandSize();
        int* cardsInHand = new int [handSize];
        Card** hand = player->getHand();
        for (int i=0;i<handSize;i++)
        {cardsInHand[i] = hand[i]->getCopyId();}

        short cardsOnField = 0;
        short* usedZones = new short[0];
        int* fieldCards = new int[0];
        Zone *field;
        for (int j=0;j<5;j++)
        {
            field = &player->getMinionField()[j];
            if (field->getUsed())
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
        int* cardsInGraveyard = new int [graveyardSize];
        Card** graveyard = player->getGraveyard();
        for (int j=0;j<graveyardSize;j++){cardsInGraveyard[j] = graveyard[j]->getCopyId();}

        short deckSize = player->getDeckSize();
        int* cardsInDeck = new int [deckSize];
        Card** deck = player->getDeck();
        for (int j=0;j<deckSize;j++){cardsInDeck[j] = deck[j]->getCopyId();}

        short specialDeckSize = player->getSpecialDeckSize();
        int* cardsInSpecialDeck = new int [specialDeckSize];
        Card** specialDeck = player->getSpecialDeck();
        for (int j=0;j<specialDeckSize;j++){cardsInSpecialDeck[j] = specialDeck[j]->getCopyId();}

        short originalDeckSize = player->getOriginalDeckSize();
        short originalSpecialDeckSize = player->getOriginalSpecialDeckSize();
        Card* originalDeck = player->getOriginalDeck();
        Card* originalSpecialDeck = player->getOriginalSpecialDeck();
        player_new->setOriginalDeck(originalDeck, originalDeckSize);
        player_new->setOriginalSpecialDeck(originalSpecialDeck,originalSpecialDeckSize);
        Card* originalDeckCopy = player_new->getOriginalDeck();

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
        Card* originalSpecialDeckCopy = player_new->getOriginalSpecialDeck();
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
        player_new->setSpecialDeck(specialDeckCopy,specialDeckSize);
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
                    handCopy[j] = &originalDeckCopy[k];
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
                    graveyardCopy[j] = &originalDeckCopy[k];
                    break;
                }
            }
        }

        player_new->setHand(handCopy,handSize);
        player_new->setGraveyard(graveyardCopy,graveyardSize);

        usedZonesArr[i] = usedZones;
        cardsOnFieldArr[i] = cardsOnField;
        fieldCardsArr[i] = fieldCards;
        player = nullptr;
        player_new = nullptr;
        delete[] cardsInHand;
        delete[] cardsInGraveyard;
        delete[] cardsInDeck;
        delete[] cardsInSpecialDeck;
        delete[] handCopy;
        delete[] graveyardCopy;
        delete[] deckCopy;
        delete[] specialDeckCopy;
    }
    for (int i=0;i<2;i++)
    {
        Card* originalDeck = this->getPlayer(i)->getOriginalDeck();
        short originalDeckSize = this->getPlayer(i)->getOriginalDeckSize();
        Card* originalSpecialDeck =  this->getPlayer(i)->getOriginalSpecialDeck();
        short originalSpecialDeckSize = this->getPlayer(i)->getOriginalSpecialDeckSize();
        Card* originalDeckOpp = this->getPlayer(!i)->getOriginalDeck();
        short originalDeckSizeOpp = this->getPlayer(!i)->getOriginalDeckSize();
        Card* originalSpecialDeckOpp =  this->getPlayer(!i)->getOriginalSpecialDeck();
        short originalSpecialDeckSizeOpp = this->getPlayer(!i)->getOriginalSpecialDeckSize();
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
            if (found) {continue;}
            for (int k = 0; k<originalSpecialDeckSize;k++)
            {
                int originalId = originalSpecialDeck[k].getCopyId();
                if (id==originalId)
                {
                    this->getPlayer(i)->getMinionField()[zone].bindCard(&originalSpecialDeck[k]);
                    this->getPlayer(i)->getMinionField()[zone].setUsed(true);
                    found = true;
                    break;
                }
            }
            if (found) {continue;}
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
            if (found) {continue;}
            for (int k = 0; k<originalSpecialDeckSizeOpp;k++)
            {
                int originalId = originalSpecialDeckOpp[k].getCopyId();
                if (id==originalId)
                {
                    originalSpecialDeckOpp[k].setOwner(this->getPlayer(i));
                    this->getPlayer(i)->getMinionField()[zone].bindCard(&originalSpecialDeckOpp[k]);
                    found = true;
                    break;
                }
            }
        }

    }
}
float Gamestate::evaluate()
{
    return (float)(rand()%10 + 0);
}

