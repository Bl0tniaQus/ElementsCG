#include "bot.h"

Bot::Bot()
{

}
void Bot::generateGamestate(Duel* duel)
{
    this->gamestate = Gamestate(duel);
}
