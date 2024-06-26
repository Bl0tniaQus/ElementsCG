#include "duel.h"
#include "bot.h"
#include "card.h"
#include "zone.h"
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
    std::cout<<"TURN: "<<this->getTurnCount()<<std::endl<<std::endl;
    std::cout<<"Cards in opponent's hand: "<<opponent->getHandSize()<<std::endl;
    std::cout<<"Cards in opponent's deck: "<<opponent->getDeckSize()<<std::endl;
    std::cout<<"Cards in opponent's sp. deck: "<<opponent->getSpecialDeckSize()<<std::endl;
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
    std::cout<<"Cards in deck: "<<player->getDeckSize()<<std::endl;
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
    defender->getCardName()->onDefence(this,defender,attacker);
    attacker->getCardName()->onAttack(this,attacker,defender);
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
    attacker->setAttacks(attacker->getAttacks()-1);
    checkWinner();
    attacker->getCardName()->afterAttack(this,attacker,defender,damage);
}
void Duel::directAttack(Card* attacker)
{
    short damage = attacker->getAttack();
    this->players[this->turnPlayer].getOpponent()->changeHp(-damage);
    attacker->setAttacks(attacker->getAttacks()-1);
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
    short barrier = card->getBarrier();
    if (barrier>0) {card->setBarrier(barrier-1);}
    else
    {
        this->removeFromField(card);
        this->toGraveyard(card);
        this->onDestroy(card);
    }

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
    if ((minion->getCardType()>0)&&(minion->getPlace()!=2)&&zoneid!=-1)
    {
        minion->setPlace(2);
        minion->getOwner()->getMinionField()[zoneid].bindCard(minion);
        minion->getOwner()->getMinionField()[zoneid].setUsed(true);
    }
}
void Duel::summonSpecialMinion(Card *minion)
{
        if (minion->getCardName()->specialSummon(this,minion))
        {
            this->summonMinion(minion,this->getEmptyMinionZone(minion->getOriginalOwner()));
            short n_special = minion->getOriginalOwner()->getSpecialDeckSize();
            Card** oldSpecial = minion->getOriginalOwner()->getSpecialDeck();
            Card** newSpecial = new Card*[n_special-1];
            short bias = 0;
            for (int i=0;i<n_special;i++)
            {
                if (oldSpecial[i]==minion) {bias = 1; continue;}
                newSpecial[i-bias] = oldSpecial[i];
            }
            minion->getOriginalOwner()->setSpecialDeck(newSpecial, n_special-1);
            minion->getOriginalOwner()->setSpecialDeckSize(n_special-1);
            this->onSummon(minion);
            }


}
bool Duel::activateSpell(Card *spell)
{
    if ((spell->getCardType()==0)&&(spell->getPlace()==1))
    {
        return this->onSpell(spell);
    }
    return false;
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
bool Duel::onSpell(Card* card)
{
if (card->getCardType()==0)
{
    return card->getCardName()->onSpell(this, card);
}
return false;
}
void Duel::onSummon(Card* card)
{
    if (card->getCardType()!=0)
    {
        card->getCardName()->onSummon(this, card);
    }
}
void Duel::onDestroy(Card* card){}
void Duel::onTurnEnd(Card* card)
{
    card->getCardName()->onTurnEnd(this, card);
}
void Duel::onTurnStart(Card* card)
{
    card->getCardName()->onTurnStart(this, card);
}
void Duel::turnEndEffects()
{
        short n_effects = 0;
        Card** effects = new Card* [n_effects];

        for (int i=0;i<5;i++)
        {
            Card *card = this->players[getTurnPlayer()].getOpponent()->getMinionField()[i].getCard();

            if (card!=nullptr)
            {
            n_effects++;
            Card **neweffects = new Card* [n_effects];
            if (n_effects>1) {
                for (int j=0;j<n_effects;j++)
                {

                    neweffects[j] = effects[j];

                }
                neweffects[n_effects-1] = card;
                delete [] effects;
                effects = neweffects;
            } else {neweffects[0]=card; effects = neweffects;}
            }
        }
        for (int i=0;i<5;i++)
        {
            Card *card = this->players[getTurnPlayer()].getMinionField()[i].getCard();

            if (card!=nullptr)
            {
            n_effects++;
            Card **neweffects = new Card* [n_effects];
            if (n_effects>1) {
                for (int j=0;j<n_effects;j++)
                {

                    neweffects[j] = effects[j];

                }
                neweffects[n_effects-1] = card;
                delete [] effects;
                effects = neweffects;
            } else {neweffects[0]=card; effects = neweffects;}
            }
        }

    for (int i=0;i<n_effects;i++)
    {
        this->onTurnEnd(effects[i]);
    }
}
void Duel::turnStartEffects()
{
        short n_effects = 0;
        Card** effects = new Card* [n_effects];

        for (int i=0;i<5;i++)
        {
            Card *card = this->players[getTurnPlayer()].getOpponent()->getMinionField()[i].getCard();

            if (card!=nullptr)
            {
            n_effects++;
            Card **neweffects = new Card* [n_effects];
            if (n_effects>1) {
                for (int j=0;j<n_effects;j++)
                {

                    neweffects[j] = effects[j];

                }
                neweffects[n_effects-1] = card;
                delete [] effects;
                effects = neweffects;
            } else {neweffects[0]=card; effects = neweffects;}
            }
        }
        for (int i=0;i<5;i++)
        {
            Card *card = this->players[getTurnPlayer()].getMinionField()[i].getCard();

            if (card!=nullptr)
            {
            n_effects++;
            Card **neweffects = new Card* [n_effects];
            if (n_effects>1) {
                for (int j=0;j<n_effects;j++)
                {

                    neweffects[j] = effects[j];

                }
                neweffects[n_effects-1] = card;
                delete [] effects;
                effects = neweffects;
            } else {neweffects[0]=card; effects = neweffects;}
            }
        }

    for (int i=0;i<n_effects;i++)
    {
        this->onTurnStart(effects[i]);
    }
}
void Duel::playFromHand(Card* card)
{
    char type = card->getCardType();
    short cost = card->getCost();
    short zoneid;
    short success =0;

    if ((cost<=card->getOwner()->getMana())||(card->getPlace()==1))
    {
        if ((type==1)&&(card->getOwner()->getSummonLimit()>0))
        {
            zoneid = this->getEmptyMinionZone(card->getOwner());

           if (zoneid!=-1)
           {

               this->summonMinion(card, zoneid);
               success=1;
           }
        }
        else if (type==0)
        {
            if (this->activateSpell(card))
            {this->toGraveyard(card);
            success=1;}
        }
        if (success==1)
        {
            short n_hand = card->getOriginalOwner()->getHandSize();
            Card** oldHand = card->getOriginalOwner()->getHand();
            Card** newHand = new Card*[n_hand-1];
            short bias = 0;
            for (int i=0;i<n_hand;i++)
            {
                if (oldHand[i]==card) {bias = 1; continue;}
                newHand[i-bias] = oldHand[i];
            }

            card->getOriginalOwner()->setHand(newHand, n_hand-1);
            card->getOriginalOwner()->setHandSize(n_hand-1);
            if (type==1) {
                card->getOriginalOwner()->setSummonLimit(card->getOriginalOwner()->getSummonLimit()-1);
                this->onSummon(card);
            }
            card->getOwner()->changeMana(-cost);

        }

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
        this->onSummon(minion);
    }
}
void Duel::passTurn()
{
    Player* turnPlayer = this->getPlayer(this->getTurnPlayer());
    Player* opponent = this->getPlayer(!this->getTurnPlayer());
    turnEndEffects();
    opponent->changeMana(2);
    if (this->turnCount!=1) {this->drawCard(opponent);}
    this->turnCount++;
    turnPlayer->setSummonLimit(1);
    this->turnPlayer = !this->turnPlayer;
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
    this->getPlayer(0)->shuffleDeck();
    this->getPlayer(1)->shuffleDeck();
    for (int i=0;i<5;i++)
    {
        this->drawCard(&this->players[0]);
        this->drawCard(&this->players[1]);
    }

    while (true)
    {
        Player* turnPlayer = this->getPlayer(this->turnPlayer);

        turnStartEffects();

        if (turnPlayer->checkBot()) //AI
        {
            int xd;
            turnPlayer->getBot()->generateGamestate(this);
            turnPlayer->getBot()->getGamestate()->drawField(this->getTurnPlayer());
            std::cin>>xd;
            this->playFromHand(turnPlayer->getHand()[0]);

            this->passTurn();
        }
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
                    std::cout<<"0 - cancel"<<std::endl;
                    for (int i=0;i<turnPlayer->getHandSize();i++)
                    {
                        std::cout<<i+1<<" - "<<turnPlayer->getHand()[i]->getName()<<" ("<<turnPlayer->getHand()[i]->getCost()<<")"<<std::endl;
                    }
                    std::cout<<"Choice: ";
                    std::cin>>target;
                    if((target>0)&&(target<=turnPlayer->getHandSize()+1))
                    {this->playFromHand(turnPlayer->getHand()[target-1]);}

                }
                if (choice==1)
                {
                    short target;
                    std::cout<<"0 - cancel"<<std::endl;
                    for (int i=0;i<turnPlayer->getSpecialDeckSize();i++)
                    {
                        std::cout<<i+1<<" - "<<turnPlayer->getSpecialDeck()[i]->getName()<<std::endl;
                    }
                    std::cout<<"Choice: ";
                    std::cin>>target;
                    if((target>0)&&(target<=turnPlayer->getSpecialDeckSize()+1))
                    {this->summonSpecialMinion(turnPlayer->getSpecialDeck()[target-1]);}
                }
                if (choice==2)
                {
                    bool Battle = true;
                    while (Battle)
                    {
                        short attacker;

                        Card* minion;
                        std::cout<<"0 - pass turn"<<std::endl;
                        for (int i=0;i<5;i++)
                        {
                            minion = turnPlayer->getMinionField()[i].getCard();
                            if (minion!=nullptr)
                            {
                                if (minion->getAttacks()>0)
                                {
                                    std::cout<<i+1<<" - "<<minion->getName()<<" ("<<minion->getAttack()<<")"<<std::endl;
                                }
                            }

                        }
                        std::cout<<"Choice: ";
                        std::cin>>attacker;
                        if (attacker==0){ Battle=false; break;}
                        if((attacker>0)&&(attacker<6))
                        {
                            minion = turnPlayer->getMinionField()[attacker-1].getCard();
                            if (minion!=nullptr)
                            {
                                if (minion->getAttacks()>0)
                                {
                                    Card* attackerMinion = minion;
                                    short defender;
                                    bool targets = false;
                                    Player* opponent = this->getPlayer(!getTurnPlayer());
                                    std::cout<<"0 - cancel"<<std::endl;
                                    for (int i=0;i<5;i++)
                                    {
                                        minion = opponent->getMinionField()[i].getCard();
                                        if (minion!=nullptr)
                                        {
                                                std::cout<<i+1<<" - "<<minion->getName()<<" ("<<minion->getDefence()<<")"<<std::endl;
                                                targets=true;
                                        }
                                    }
                                    if (targets==false)
                                    {
                                        std::cout<<"1 - direct attack"<<std::endl;
                                    }
                                    std::cout<<"Choice: ";
                                    std::cin>>defender;
                                    if (targets==false)
                                    {
                                        if (defender==1) {this->directAttack(attackerMinion);continue;}
                                    }
                                    if((defender>0)&&(defender<6))
                                    {
                                        minion = opponent->getMinionField()[defender-1].getCard();
                                        if (minion!=nullptr)
                                        {
                                            this->combat(attackerMinion,minion);
                                        }
                                        }
                                    }

                                }
                            }
                        }

                    if (!Battle) {passTurn();}
                }
                if (choice==3)
                {
                    this->passTurn();
                }
            }
        }
    }
}
