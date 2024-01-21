#ifndef DUEL_H
#define DUEL_H
#include "player.h"
class Duel
{
private:
    Player players[2]; //0 - player 1, 1 - player2
    short turnCount;
    char turnPlayer;
public:
    Duel();
    short getTurnCount() {return this->turnCount;}
    char getTurnPlayer() {return this->turnPlayer;}
    Player* getPlayer(char p) {return &this->players[p];}
    void passTurn() {this->turnPlayer = !this->turnPlayer;}
    void drawField(char p);
    void combat(Card* attacker, Card* defender);
    void directAttack(Card* attacker);
    void destruction(Card* card);
    void checkWinner();
};

#endif // DUEL_H
