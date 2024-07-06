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
float Gamestate::resourceFactor()
{
    Player* player = this->getPlayer(this->getTurnPlayer());
    Player* opponent = player->getOpponent();

    short playerHp = player->getHp();
    short playerMana = player->getMana();
    short opponentHp = opponent->getHp();
    short opponentMana = opponent->getMana();

    if (opponentHp<=0) {return 99999;}

    float f_oppHp = 1 + (30/(opponentHp))/100;
    float f_pHp = 1 + playerHp/100;
    float f_oppMana = 1 + (15/(opponentMana+0.01) * 2)/20;
    float f_pMana = 1 + (playerMana * 0.7)/30;
    float f_hpDiff = 1 + ((playerHp - opponentHp) * 1.2) / 50;
    float f_manaDiff = 1 + ((playerMana - opponentMana) * 0.3) / 70;
    float factor = f_oppHp * f_pHp * f_oppMana * f_pMana * f_hpDiff * f_manaDiff;

    return factor;

}
float Gamestate::cardAdvantageFactor()
{
    Player* player = this->getPlayer(this->getTurnPlayer());
    Player* opponent = player->getOpponent();

    short playerHand = player->getHandSize();
    short opponentHand = opponent->getHandSize();

    short playerFieldCount = player->getMinionCount();
    short opponentFieldCount = player->getMinionCount();


    float f_cardDiff = 1 + (playerHand + playerFieldCount) / ((opponentHand + opponentFieldCount)+0.01)/10;

    float factor = f_cardDiff;

    return factor;
}
float Gamestate::fieldPresenceFactor()
{
    float factor = 0;
    return factor;
}

float Gamestate::evaluate()
{
    float resources = this->resourceFactor();
    float cardAdvantage = this->cardAdvantageFactor();

    float resourcesW = 1;
    float cardAdvantageW = 2;

    float value = (resources * resourcesW + cardAdvantage * cardAdvantageW) / (resourcesW + cardAdvantageW);

    //return (float)(rand()%10 + 0);
    return value;
}

