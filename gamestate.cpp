#include "gamestate.h"

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
        Zone *field = player->getMinionField();
        //zrobić!!!


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
        this->players[i].setOriginalSpecialDeck(new Card [originalSpecialDeckSize],originalSpecialDeckSize);

    }
}
