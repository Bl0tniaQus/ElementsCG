#include "bot.h"

Bot::Bot()
{

}
void Bot::generateBaseGamestate(Duel* duel)
{
    this->baseGamestate = Gamestate(duel);
}
void Bot::generateTempGamestate(Duel* duel)
{
    this->tempGamestate = Gamestate(duel);
}
