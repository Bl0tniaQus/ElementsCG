#include "dueluibridge.h"
#include "../engine/duel.h"

DuelUiBridge::DuelUiBridge(Duel* duel, Ui::MainWindow* ui)
{
    this->duel = duel;
    this->ui = ui;
}
void DuelUiBridge::setHandImages()
{
    Player* player = duel->getPlayer(0);
    short n_hand = player->getHandSize();
    for (int i=0;i<n_hand;i++)
    {

    }

}

