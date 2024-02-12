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
        short graveyardSize = player->getGraveyardSize();
        this->players[i].setGraveyardSize(graveyardSize);
        short deckSize = player->getDeckSize();
        this->players[i].setDeckSize(deckSize);
        short specialDeckSize = player->getSpecialDeckSize();
        this->players[i].setSpecialDeckSize(specialDeckSize);
        short originalDeckSize = player->getOriginalDeckSize();
        this->players[i].setOriginalDeckSize(originalDeckSize);
        short originalSpecialDeckSize = player->getOriginalSpecialDeckSize();
        this->players[i].setOriginalDeckSize(originalSpecialDeckSize);

        Card* originalDeck = player->getOriginalDeck();
        Card* originalSpecialDeck = player->getOriginalSpecialDeck();

    }
}
