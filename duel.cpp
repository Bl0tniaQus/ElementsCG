#include "duel.h"
#include "card.h"
#include <iostream>
Duel::Duel()
{
    players[0].setOpponent(&players[1]);
    players[1].setOpponent(&players[0]);
    players[0].setName('a');
    players[1].setName('b');
    this->turnPlayer = 0;
}
void Duel::drawField(char p)
{
    Player* player = this->getPlayer(p);
    Player* opponent = this->getPlayer(!p);
    std::cout<<"Cards in opponent's hand: "<<opponent->getHandSize()<<std::endl;
    std::cout<<"Opponent's field: ";
    for (int i=4;i>=0;i--)
    {
        if (opponent->getMinionField()[i].getCard()!=nullptr)
        std::cout<<opponent->getMinionField()[i].getCard()->getName()<<"; ";
    }std::cout<<std::endl;
    std::cout<<"Opponent's graveyard: ";
    for (int i=0;i<opponent->getGraveyardSize();i++)
    {
        std::cout<<opponent->getGraveyard()[i]->getName()<<"; ";
    }std::cout<<std::endl<<std::endl;
    std::cout<<opponent->getHp()<<"/"<<opponent->getMana()<<std::endl;
    for (int i=4;i>=0;i--)
    {
        std::cout<<opponent->getMinionField()[i].getUsed()<<" ";
    }
    std::cout<<std::endl<<"---------"<<std::endl;
    for (int i=0;i<5;i++)
    {
        std::cout<<player->getMinionField()[i].getUsed()<<" ";
    }
    std::cout<<std::endl<<std::endl;
    std::cout<<player->getHp()<<"/"<<player->getMana()<<std::endl;
    std::cout<<"Hand: ";
    for (int i=0;i<player->getHandSize();i++)
    {
        std::cout<<player->getHand()[i]->getName()<<"; ";
    }std::cout<<std::endl<<"Field: ";
    for (int i=0;i<5;i++)
    {
        if (player->getMinionField()[i].getCard()!=nullptr)
        std::cout<<player->getMinionField()[i].getCard()->getName()<<"; ";
    }std::cout<<std::endl;
    std::cout<<"Graveyard: ";
    for (int i=0;i<player->getGraveyardSize();i++)
    {
        std::cout<<player->getGraveyard()[i]->getName()<<"; ";
    }std::cout<<std::endl;
    std::cout<<"Sp. deck: ";
    for (int i=0;i<player->getSpecialDeckSize();i++)
    {
        std::cout<<player->getSpecialDeck()[i]->getName()<<"; ";
    }std::cout<<std::endl<<std::endl;
}
void Duel::combat(Card* attacker, Card* defender)
{
    short atk = attacker->getAttack();
    short def = defender->getDefence();
    short damage = 0;
    if (atk>def)
    {
        destruction(defender);
        damage = atk-def;
    }
    if (atk<def)
    {
        destruction(attacker);
        damage = def-atk;
    }

    if (atk>def){this->players[this->turnPlayer].getOpponent()->changeHp(-damage);}
    if (def>atk){this->players[this->turnPlayer].changeHp(-damage);}
    checkWinner();
}
void Duel::directAttack(Card* attacker)
{
    short damage = attacker->getAttack();
    this->players[this->turnPlayer].getOpponent()->changeHp(-damage);
    checkWinner();
}
void Duel::checkWinner()
{
    short hp1 = players[0].getHp(); short hp2 = players[1].getHp();
    if ((hp1<=0)&&(hp2<=0)) {std::cout<<"X";}
    else if ((hp1<=0)&&(hp2>0)) {std::cout<<"2";}
    else if ((hp2<=0)&&(hp1>0)) {std::cout<<"1";}

}
void Duel::destruction(Card* card)
{
    this->toGraveyard(card);
    this->onDestroy(card);
}
void Duel::toGraveyard(Card* card)
{
    card->setPlace(3);
    Player* owner = card->getOriginalOwner();
    card->setOwner(owner);
    short n_graveyard = owner->getGraveyardSize();
    Card** oldGraveyard = owner->getGraveyard();
    Card** newGraveyard = new Card*[n_graveyard+1];


    if (n_graveyard==0) {newGraveyard[0] = card;}
    else{
    for (int i=0;i<n_graveyard;i++)
    {
        newGraveyard[i] = oldGraveyard[i];
    }
    newGraveyard[n_graveyard] = card;
    }
    owner->setGraveyard(newGraveyard, n_graveyard+1);
}
void Duel::toSpecialDeck(Card* card)
{
    card->setPlace(4);
    if (card->getZone()!=nullptr) {this->removeFromField(card);}
    Player* owner = card->getOriginalOwner();
    card->setOwner(owner);
    short n_special = owner->getSpecialDeckSize();
    Card** oldSpecial = owner->getSpecialDeck();
    Card** newSpecial = new Card*[n_special+1];


    if (n_special==0) {newSpecial[0] = card;}
    else{
    for (int i=0;i<n_special;i++)
    {
        newSpecial[i] = oldSpecial[i];
    }
    newSpecial[n_special] = card;
    }
    owner->setSpecialDeck(newSpecial, n_special+1);
}
void Duel::removeFromField(Card* card)
{
    card->getZone()->setUsed(false);
    card->getZone()->destroyCard();
    card->setZone(nullptr);
}
short Duel::getEmptyMinionZone(Player* player)
{
    Zone* zones = player->getMinionField();
    for (int i=0;i<5;i++)
    {
        if (zones[i].getUsed()==false) {return i;}
    }
    return -1;
}
void Duel::summonMinion(Card *minion, short zoneid)
{
    if ((minion->getCardType()>0)&&(minion->getPlace()!=2))
    {
        minion->setPlace(2);
        minion->getOwner()->getMinionField()[zoneid].bindCard(minion);
        minion->getOwner()->getMinionField()[zoneid].setUsed(true);

    }
}
void Duel::summonSpecialMinion(Card *minion)
{
    this->setTargetList(nullptr,0);
    short id = minion->getCardId();
    //two requirements tree
    if (id==8)
    {
        this->generateSpecialMinionMaterialList(minion,1);

        short n_targets1 = this->getTargetList().getTargetsNumber();
        Card** temp_targets = this->getTargetList().getTargetList();
        Card** targets1 = new Card* [n_targets1];
        for (int i=0;i<n_targets1;i++)
        {
            targets1[i] = temp_targets[i];
        } delete []temp_targets;
        this->generateSpecialMinionMaterialList(minion,2);
        short n_targets2 = this->getTargetList().getTargetsNumber();
        temp_targets = this->getTargetList().getTargetList();
        Card** targets2 = new Card* [n_targets2];
        for (int i=0;i<n_targets2;i++)
        {
            targets2[i] = temp_targets[i];
        } delete []temp_targets;

        if ((n_targets1==0)||(n_targets2==0)) {return;}
        else if ((n_targets1==1)&&(n_targets2==1))
        {
            if (targets1[0]==targets2[0]) {return;}
        }
        else if ((n_targets1==1)&&(n_targets2>1))
        {
            for (int i=0;i<n_targets2;i++)
            {
                if (targets2[i]==targets1[0]) {return;}
            }
        }
        else if ((n_targets2==1)&&(n_targets1>1))
        {
            for (int i=0;i<n_targets2;i++)
            {
                if (targets2[i]==targets1[0]) {return;}
            }
        }
        int target;
        for (int i=0;i<n_targets1;i++)
        {
            std::cout<<i<<" - "<<targets1[i]->getName()<<std::endl;
        }
        std::cout<<"First minion: ";
        std::cin>>target;
        Card* targetCard = targets1[target];
        Card* targetCard2;
        Card** new_targets2;
        short duplicate=0;
        for (int i=0;i<n_targets2;i++)
        {
            if (targets2[i]==targetCard)
            {
                duplicate=1;
                new_targets2 = new Card* [n_targets2-1];
                short bias=0;
                for (int j=0;j<n_targets2;j++)
                {
                   if (targets2[j]==targetCard) {bias=1; continue;}
                   new_targets2[j-bias]=targets2[j];
                }
            }
        }
        if (duplicate==1)
        {
            for (int i=0;i<n_targets2-1;i++)
            {
                std::cout<<i<<" - "<<new_targets2[i]->getName()<<std::endl;
            }
            std::cout<<"Second minion: ";
            std::cin>>target;
            targetCard2 = new_targets2[target];
        }
        else
        {
            for (int i=0;i<n_targets2-1;i++)
            {
                std::cout<<i<<" - "<<new_targets2[i]->getName()<<std::endl;
            }
            std::cout<<"Second minion: ";
            std::cin>>target;
            targetCard2 = new_targets2[target];
        }
        this->removeFromField(targetCard);
        this->removeFromField(targetCard2);
        this->toGraveyard(targetCard);
        this->toGraveyard(targetCard2);
        this->summonMinion(minion,this->getEmptyMinionZone(minion->getOriginalOwner()));
    }
}
void Duel::activateSpell(Card *spell, short zoneid)
{
    if ((spell->getCardType()==0)&&(spell->getPlace()==1))
    {
        this->onSpell(spell,zoneid);
    }
}
void Duel::toHand(Card* card)
{
    if (card->getCardType()==2) {this->toSpecialDeck(card);}
    else{
        card->setPlace(1);
        if (card->getZone()!=nullptr) {this->removeFromField(card);}
        short n_hand = card->getOriginalOwner()->getHandSize();
        Card** oldHand = card->getOriginalOwner()->getHand();
        Card** newHand = new Card*[n_hand+1];
        if (n_hand==1) {newHand[0] = card;}
        else{
        for (int i=0;i<n_hand;i++)
        {
            newHand[i] = oldHand[i];
        }
        newHand[n_hand] = card;
        }
        Player* owner = card->getOriginalOwner();
        card->setOwner(owner);
        owner->setHand(newHand, n_hand+1);
        owner->setHandSize(n_hand+1);
    }

}
void Duel::drawCard(Player* player)
{
    short n_deck = player->getDeckSize();

    if (n_deck>0)
    {
        short n_hand = player->getHandSize();
        Card** oldHand = player->getHand();
        Card** newHand = new Card*[n_hand+1];
        Card** newDeck = new Card*[n_deck-1];
        Card** oldDeck = player->getDeck();
        oldDeck[n_deck-1]->setPlace(1);
        if (n_hand==0) {newHand[0] = oldDeck[n_deck-1];}
        else{
        for (int i=0;i<n_hand;i++)
        {
            newHand[i] = oldHand[i];
        }
        newHand[n_hand] = oldDeck[n_deck-1];
        }


        player->setHand(newHand, n_hand+1);
        for (int i=0;i<n_deck-1;i++)
        {
            newDeck[i] = oldDeck[i];
        }
        player->setHandSize(n_hand+1);
        player->setDeckSize(n_deck-1);
        player->setDeck(newDeck,n_deck-1);
    }


}
bool Duel::checkEffectRequirements(Card* card)
{
    this->setTargetList(nullptr,0);
    short id = card->getCardId();
    //any monster on field
    if (id==4)
{
this->generateTargetList(card);
    if (this->targetList.getTargetsNumber()>0) {return true;}
}
//monster with the same name in hand
else if (id==1)
{
    this->generateTargetList(card);
        if (this->targetList.getTargetsNumber()>0) {return true;}
}
return false;
}
void Duel::onSpell(Card* card, short zoneid)
{
short id = card->getCardId();
if (id==4) //Whirlwind
{
    bool usable = this->checkEffectRequirements(card);
    if (usable)
    {
        Card** targets = this->targetList.getTargetList();
        int target;
        for (int i=0;i<this->targetList.getTargetsNumber();i++)
        {
            std::cout<<i<<" - "<<targets[i]->getName()<<std::endl;
        }
        std::cout<<"Target: ";
        std::cin>>target;
        Card* targetCard = targets[target];
        this->toHand(targetCard);
    }
}
}
void Duel::onSummon(Card* card, short zoneid)
{
    short id = card->getCardId();
    //summon minion from hand
    if (id==1)
    {
        bool usable = this->checkEffectRequirements(card);
        if (usable)
        {
            Card** targets = this->targetList.getTargetList();
            Card* targetCard = targets[0];
            this->summonFromHand(targetCard, this->getEmptyMinionZone(card->getOwner()));
        }
    }
    //Draw a card
    else if (id==7)
    {
        this->drawCard(card->getOwner());
    }

}
void Duel::onDestroy(Card* card){}
void Duel::onTurnEnd(Card* card)
{
    short id = card->getCardId();
    if (id==5)
    {
        card->getOwner()->changeMana(2);
    }
    else if (id==6)
    {
        this->drawCard(card->getOwner());
    }

}
void Duel::setTargetList(Card** targets, short n_targets)
{
    this->targetList.setTargetList(targets);
    this->targetList.setTargetNumber(n_targets);

}
void Duel::generateSpecialMinionMaterialList(Card* minion, short n)
{
    short n_targets=0;
    Card** targets = new Card* [n_targets];
    short servantId = minion->getCardId();
    Player* owner = minion->getOriginalOwner();
    //Brass Beetle
    if (servantId==8)
    {
        for (int i=0;i<5;i++)
        {
            Card* card = owner->getMinionField()[i].getCard();
            if (card!=nullptr)
            {
                if (card->getElement()[0]=='E')//Earth minion
                {
                    n_targets++;
                    Card **newtargets = new Card* [n_targets];
                    if (n_targets>1) {
                        for (int j=0;j<n_targets;j++)
                        {

                            newtargets[j] = targets[j];

                        }
                        newtargets[n_targets-1] = card;
                        delete [] targets;
                        targets = newtargets;
                    } else {newtargets[0]=card; targets = newtargets;}
                }
            }
        }
        }
    this->setTargetList(targets,n_targets);
}

void Duel::generateTargetList(Card* effect)
{
    short n_targets=0;
    Card** targets = new Card* [n_targets];
    short effectId;

    //list of end of turn effects
    if (effect == nullptr)
    {
        for (int i=0;i<5;i++)
        {
            Card *card = this->players[getTurnPlayer()].getOpponent()->getMinionField()[i].getCard();

            if (card!=nullptr)
            {
            short cardid = card->getCardId();
            if (!((cardid==5)||(cardid==6))) {continue;}
            n_targets++;
            Card **newtargets = new Card* [n_targets];
            if (n_targets>1) {
                for (int j=0;j<n_targets;j++)
                {

                    newtargets[j] = targets[j];

                }
                newtargets[n_targets-1] = card;
                delete [] targets;
                targets = newtargets;
            } else {newtargets[0]=card; targets = newtargets;}
            }
        }
        for (int i=0;i<5;i++)
        {
            Card *card = this->players[getTurnPlayer()].getMinionField()[i].getCard();
            if (card!=nullptr)
            {
            n_targets++;
            Card **newtargets = new Card* [n_targets];
            if (n_targets>1) {
                for (int j=0;j<n_targets;j++)
                {

                    newtargets[j] = targets[j];

                }
                newtargets[n_targets-1] = card;
                delete [] targets;
                targets = newtargets;
            } else {newtargets[0]=card; targets = newtargets;}
            }
        }



    } else {effectId = effect->getCardId();}
    //any monster on field
    if (effectId==4)
    {
        for (int i=0;i<5;i++)
        {
            Card *card = this->players[getTurnPlayer()].getOpponent()->getMinionField()[i].getCard();

            if (card!=nullptr)
            {

            n_targets++;
            Card **newtargets = new Card* [n_targets];
            if (n_targets>1) {
                for (int j=0;j<n_targets;j++)
                {

                    newtargets[j] = targets[j];

                }
                newtargets[n_targets-1] = card;
                delete [] targets;
                targets = newtargets;
            } else {newtargets[0]=card; targets = newtargets;}
            }
        }
        for (int i=0;i<5;i++)
        {
            Card *card = this->players[getTurnPlayer()].getMinionField()[i].getCard();
            if (card!=nullptr)
            {
            n_targets++;
            Card **newtargets = new Card* [n_targets];
            if (n_targets>1) {
                for (int j=0;j<n_targets;j++)
                {

                    newtargets[j] = targets[j];

                }
                newtargets[n_targets-1] = card;
                delete [] targets;
                targets = newtargets;
            } else {newtargets[0]=card; targets = newtargets;}
            }
        }
    }
    //Monster in hand with the same name
    else if (effectId==1)
    {

        for (int i=0;i<effect->getOwner()->getHandSize();i++)
        {
            Card *card = effect->getOwner()->getHand()[i];
            if ((card!=nullptr)&&(card->getCardId()==effectId)&&(card!=effect))
            {

            n_targets++;
            Card **newtargets = new Card* [n_targets];
            if (n_targets>1) {
                for (int j=0;j<n_targets;j++)
                {

                    newtargets[j] = targets[j];

                }
                newtargets[n_targets-1] = card;
                delete [] targets;
                targets = newtargets;
            } else {newtargets[0]=card; targets = newtargets;}
            }

    }}
    this->setTargetList(targets,n_targets);
}
void Duel::playFromHand(Card* card)
{
    char type = card->getCardType();
    short cost = card->getCost();
    short zoneid;

    if ((cost<=card->getOwner()->getMana())||(card->getPlace()==1))
    {
        if (type==1)
        {
            zoneid = this->getEmptyMinionZone(card->getOwner());

           if (zoneid!=-1)
           {

               this->summonMinion(card, zoneid);
           }
        }
        else if (type==0)
        {
            zoneid = this->getEmptyMinionZone(card->getOwner());
            this->activateSpell(card,zoneid);
            this->toGraveyard(card);
        }

        short n_hand = card->getOriginalOwner()->getHandSize();
        Card** oldHand = card->getOriginalOwner()->getHand();
        Card** newHand = new Card*[n_hand-1];
        short bias = 0;
        for (int i=0;i<n_hand;i++)
        {
            if (oldHand[i]==card) {bias = 1; continue;}
            newHand[i-bias] = oldHand[i];
        }

        card->getOriginalOwner()->setHand(newHand, n_hand-1);//tu problem
        card->getOriginalOwner()->setHandSize(n_hand-1);
        if (type==1) {this->onSummon(card, zoneid);}
        card->getOwner()->changeMana(-cost);
    }

}
void Duel::summonFromHand(Card* minion, short zoneid)
{
    if ((minion->getCardType()==1)&&(minion->getPlace()==1))
    {

        minion->setPlace(2);
        minion->getOwner()->getMinionField()[zoneid].bindCard(minion);
        minion->getOwner()->getMinionField()[zoneid].setUsed(true);
        short n_hand = minion->getOriginalOwner()->getHandSize();
        Card** oldHand = minion->getOriginalOwner()->getHand();
        Card** newHand = new Card*[n_hand-1];
        short bias = 0;
        for (int i=0;i<n_hand;i++)
        {
            if (oldHand[i]==minion) {bias = 1; continue;}
            newHand[i-bias] = oldHand[i];
        }
        minion->getOriginalOwner()->setHand(newHand, n_hand-1);
        minion->getOriginalOwner()->setHandSize(n_hand-1);
        this->onSummon(minion,this->getEmptyMinionZone(minion->getOwner()));
    }
}
void Duel::passTurn()
{
    generateTargetList(nullptr);
    Card** eotTargets = this->getTargetList().getTargetList();
    short n_targets = this->getTargetList().getTargetsNumber();
    for (int i=0;i<n_targets;i++)
    {
        this->onTurnEnd(eotTargets[i]);
    }
    this->getPlayer(this->turnPlayer)->changeMana(2);
    this->getPlayer(!this->turnPlayer)->changeMana(2);
    this->turnPlayer = !this->turnPlayer;
    this->drawCard(this->getPlayer(this->turnPlayer));
}
void Duel::DuelControl(Deck *deck0, Deck* deck1)
{
    short choice;
    this->turnPlayer=0; //wylosuj kto 1
    this->turnCount=1;
    this->getPlayer(0)->setOriginalDeck(deck0->getDeck(),deck0->getDeckSize());
    this->getPlayer(0)->setOriginalSpecialDeck(deck0->getSpecialDeck(),deck0->getSpecialDeckSize());
    this->getPlayer(0)->setDeckOwnership();
    this->getPlayer(1)->setOriginalDeck(deck1->getDeck(),deck1->getDeckSize());
    this->getPlayer(1)->setOriginalSpecialDeck(deck1->getSpecialDeck(),deck1->getSpecialDeckSize());
    this->getPlayer(1)->setDeckOwnership();
    for (int i=0;i<5;i++)
    {
        this->drawCard(&this->players[0]);
        this->drawCard(&this->players[1]);
    }

    while (true)
    {
        Player* turnPlayer = this->getPlayer(this->turnPlayer);
        if (this->turnCount!=1) {this->drawCard(turnPlayer);}

        if (turnPlayer->checkBot()) //AI
        {}
        else //player
        {
           this->drawField(this->turnPlayer);

            std::cout<<"0 - play from hand, 1 - play from sp. deck, 2 - battle, 3 - pass turn"<<std::endl;
            std::cout<<"Action: ";
            std::cin>>choice;
            if ((choice>=0)&&(choice<=3))
            {
                if (choice==0)
                {
                    short target;
                    for (int i=0;i<turnPlayer->getHandSize();i++)
                    {
                        std::cout<<i<<" - "<<turnPlayer->getHand()[i]->getName()<<std::endl;
                    }
                    std::cout<<"Choice: ";
                    std::cin>>target;
                    if((target>=0)&&(target<=turnPlayer->getHandSize()))
                    {this->playFromHand(turnPlayer->getHand()[target]);}

                }
            }
        }
    }
}
