#include "duel.h"
#include "bot.h"
#include "card.h"
#include "zone.h"
#include <iostream>
Duel::Duel()
{
    players[0].setOpponent(&players[1]);
    players[1].setOpponent(&players[0]);
    players[0].setName("Player 1");
    players[1].setName("Player 2");
    this->turnPlayer = 0;
    this->attackersTargetList = new TargetList;
    this->defendersTargetList = new TargetList;
    this->logsSource = new short [0];
    this->logs = new std::string [0];
    this->n_logs = 0;
    this->lastSource = 2;
}
Duel::~Duel()
{
    delete this->attackersTargetList;
    delete this->defendersTargetList;
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
    this->lastSource = this->turnPlayer;
    this->appendLog(this->attackLog(attacker,defender),this->lastSource);
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

    if (atk>def){
        this->appendLog(this->lifeChangeLog(this->players[this->turnPlayer].getOpponent(),-damage),this->lastSource);
        this->players[this->turnPlayer].getOpponent()->changeHp(-damage);
    }
    if (def>atk){
        this->appendLog(this->lifeChangeLog(&this->players[this->turnPlayer],-damage),this->lastSource);
        this->players[this->turnPlayer].changeHp(-damage);

    }
    attacker->setAttacks(attacker->getAttacks()-1);
    checkWinner();
    attacker->getCardName()->afterAttack(this,attacker,defender,damage);
    this->lastSource = 2;
}
void Duel::directAttack(Card* attacker)
{
    this->lastSource = this->turnPlayer;
    this->appendLog(this->directAttackLog(attacker),this->lastSource);
    attacker->getCardName()->onAttack(this,attacker,nullptr);
    short damage = attacker->getAttack();
    if (damage>0)
    {this->appendLog(this->lifeChangeLog(this->players[this->turnPlayer].getOpponent(),-damage),this->lastSource);
    this->players[this->turnPlayer].getOpponent()->changeHp(-damage);}
    attacker->setAttacks(attacker->getAttacks()-1);
    attacker->getCardName()->afterAttack(this,attacker,nullptr,damage);
    this->lastSource = 2;
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
    if (barrier>0) {
        this->appendLog(this->barrierChangeLog(card,-1),this->lastSource);
        card->setBarrier(barrier-1);
    }
    else
    {
        this->appendLog(this->destructionLog(card),this->getPlayerId(card->getOwner()));
        this->removeFromField(card);
        this->toGraveyard(card);
        this->onDestroy(card);
    }

}
void Duel::toGraveyard(Card* card)
{
    card->setPlace(3);
    Player* owner = card->getOriginalOwner();
    card->returnToOriginal();
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
    delete[] newGraveyard;
}
void Duel::toSpecialDeck(Card* card)
{
    card->setPlace(4);
    if (card->getZone()!=nullptr) {this->removeFromField(card);}
    Player* owner = card->getOriginalOwner();
    card->returnToOriginal();
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
    delete[] newSpecial;
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
bool Duel::canSummon(Player* player)
{
    return (this->getEmptyMinionZone(player)!=-1 && player->getSummonLimit()>0);
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
        this->lastSource = this->turnPlayer;
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
            delete[] newSpecial;
            this->onSummon(minion);
            }
            this->lastSource = 2;

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
        card->returnToOriginal();
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
        owner->setHand(newHand, n_hand+1);
        delete[] newHand;
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
        player->setDeck(newDeck,n_deck-1);
        delete[] newHand;
        delete[] newDeck;
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
        this->appendLog(this->summonLog(card),this->lastSource);
        card->getCardName()->onSummon(this, card);
    }
}
void Duel::onDestroy(Card* card)
{
    if (card->getCardType()!=0)
    {
        card->getCardName()->onDestroy(this, card);
    }
}
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
        Card **neweffects;
        for (int i=0;i<5;i++)
        {
            Card *card = this->players[getTurnPlayer()].getOpponent()->getMinionField()[i].getCard();

            if (card!=nullptr)
            {
            n_effects++;
            neweffects = new Card* [n_effects];
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
            neweffects = new Card* [n_effects];
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

    delete [] effects;
}
void Duel::turnStartEffects()
{
        short n_effects = 0;
        Card** effects = new Card* [n_effects];
        Card **neweffects;
        for (int i=0;i<5;i++)
        {
            Card *card = this->players[getTurnPlayer()].getOpponent()->getMinionField()[i].getCard();

            if (card!=nullptr)
            {
            n_effects++;
            neweffects = new Card* [n_effects];
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
    delete [] effects;
}
void Duel::playFromHand(Card* card)
{
    char type = card->getCardType();
    short cost = card->getCost();
    short zoneid;
    short success =0;
    this->lastSource = this->turnPlayer;

    if ((cost<=card->getOwner()->getMana())&&(card->getPlace()==1))
    {
        if ((type==1)&&(card->getOwner()->getSummonLimit()>0))
        {
            zoneid = this->getEmptyMinionZone(card->getOwner());

           if (zoneid!=-1)
           {
               this->appendLog(this->cardFromHandLog(card),this->lastSource);
               this->appendLog(this->manaChangeLog(card->getOwner(),-cost),this->lastSource);
               card->getOwner()->changeMana(-cost);
               this->summonMinion(card, zoneid);
               success=1;
           }
        }
        else if (type==0)
        {
            if (this->activateSpell(card))
            {
                this->toGraveyard(card);
                success=1;
            }
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
            if (type==1) {
                card->getOriginalOwner()->setSummonLimit(card->getOriginalOwner()->getSummonLimit()-1);
                this->onSummon(card);
            }

            delete[] newHand;

        }

    }
    this->lastSource = 2;
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
        this->onSummon(minion);
        delete[] newHand;
    }
}
void Duel::removeFromGraveyard(Card* card)
{
    short n_graveyard = card->getOriginalOwner()->getGraveyardSize();
    Card** oldGraveyard = card->getOriginalOwner()->getGraveyard();
    Card** newGraveyard = new Card*[n_graveyard-1];
        short bias = 0;
        for (int i=0;i<n_graveyard;i++)
        {
            if (oldGraveyard[i]==card) {bias = 1; continue;}
            newGraveyard[i-bias] = oldGraveyard[i];
        }
        card->getOriginalOwner()->setHand(newGraveyard, n_graveyard-1);
        delete[] newGraveyard;
}
void Duel::summonFromGraveyard(Card* minion, short zoneid)
{
    if ((minion->getCardType()>0)&&(minion->getPlace()==3))
    {
        minion->setPlace(2);
        minion->getOwner()->getMinionField()[zoneid].bindCard(minion);
        minion->getOwner()->getMinionField()[zoneid].setUsed(true);
        this->removeFromGraveyard(minion);
        this->onSummon(minion);
    }
}
void Duel::changeStats(Card* card, short a, short d)
{
    short atk = card->getAttack();
    short def = card->getDefence();
    short atk_new = atk + a;
    short def_new = def + d;
    if (atk_new<0) {atk_new = 0;}
    if (def_new<0) {def_new = 0;}
    this->appendLog(this->statChangeLog(card,atk_new,def_new), this->getPlayerId(card->getOwner()));
    card->setAttack(atk_new);
    card->setDefence(def_new);
}
void Duel::changeLevel(Card* card, short l)
{
    this->appendLog(this->levelChangeLog(card,l), this->getPlayerId(card->getOwner()));
    card->setLevel(l);
}

void Duel::passTurn()
{
    Player* turnPlayer = this->getPlayer(this->getTurnPlayer());
    Player* opponent = this->getPlayer(!this->getTurnPlayer());
    this->turnEndLog();
    this->turnEndEffects();
    this->turnCount++;
    turnPlayer->setSummonLimit(1);
    this->turnPlayer = !this->turnPlayer;
    this->turnStartLog();
    if (opponent->getDeckSize()>0)
    {
        this->appendLog(this->drawCardLog(opponent,1),2);
    }
    this->drawCard(opponent);
    this->appendLog(this->manaChangeLog(opponent, 2),this->lastSource);
    opponent->changeMana(2);
    this->turnStartEffects();
}
void Duel::generateAttackersList()
{
    Card** attackers = new Card* [0];
    short n = 0;
    Player* player = this->getPlayer(this->turnPlayer);
    for (int i=0;i<5;i++)
    {
        Zone* zone = &player->getMinionField()[i];
        Card* card = zone->getCard();
        if (card!=nullptr)
        {
            if (card->getAttacks()>0)
            {
                n++;
                Card** newAttackers = new Card* [n];
                if (n>1)
                {
                    for (int j=0;j<n;j++)
                    {
                        newAttackers[j] = attackers[j];
                    }
                    newAttackers[n-1] = card;
                }
                else
                {
                    newAttackers[0] = card;
                }
                delete[]attackers;
                attackers = newAttackers;
            }
        }
    }
    this->getAttackersList()->setTargetList(attackers,n);
}
void Duel::generateDefendersList()
{
    Card** defenders = new Card* [0];
    short n = 0;
    Player* player = this->getPlayer(this->turnPlayer)->getOpponent();
    for (int i=0;i<5;i++)
    {
        Zone* zone = &player->getMinionField()[i];
        Card* card = zone->getCard();
        if (card!=nullptr)
        {
                n++;
                Card** newDefenders = new Card* [n];
                if (n>1)
                {
                    for (int j=0;j<n;j++)
                    {
                        newDefenders[j] = defenders[j];
                    }
                    newDefenders[n-1] = card;
                }
                else
                {
                    newDefenders[0] = card;
                }
                delete[]defenders;
                defenders = newDefenders;
        }
    }
    this->getDefendersList()->setTargetList(defenders,n);
}
void Duel::startDuel(Deck *deck0, Deck* deck1)
{
    this->turnPlayer=0; //wylosuj kto 1
    this->turnCount=1;
    this->turnStartLog();
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
}
void Duel::DuelControl(Deck *deck0, Deck* deck1)
{
    startDuel(deck0,deck1);
    short choice;
    while (true)
    {
        Player* turnPlayer = this->getPlayer(this->turnPlayer);



        if (turnPlayer->checkBot()) //AI
        {
           Bot* bot = turnPlayer->getBot();
            bot->generateBaseGamestate(this);
            short n_hand = turnPlayer->getHandSize();
            for (int z = 0;z<n_hand;z++)
            {
                bot->testCardFromHand(z, this);

            }
             for (int y = 0;y<bot->getOptionsNumber();y++)
            {
                std::cout<<bot->getHandOptions()[y]<<" "<<bot->getTargetsForOptions()[y]<<" "<<bot->getHandValues()[y]<<std::endl;
            }
            bot->getBestOption();
            short bc = bot->getBestCard();
            if (bc>=0&&bc<n_hand) {this->playFromHand(turnPlayer->getHand()[bot->getBestCard()]);}
            bot->endHandTesting();
            bot->conductBattlePhase(this);
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
short Duel::makeSpellChoice(Card* card)
{
    if (this->uiBridge!=nullptr)
    {
        return this->uiBridge->makeSpellChoice(card);
    }
    else
    {
        Card** targets = card->getCardName()->getTargetList()->getTargetList();
        short nt = card->getCardName()->getTargetList()->getTargetsNumber();
        short target;
        std::cout<<"0 - cancel"<<std::endl;
        for (int i=0;i<nt;i++)
        {
            std::cout<<i+1<<" - "<<targets[i]->getName()<<std::endl;
        }
        std::cout<<"Target: ";
        std::cin>>target;
        if (target>=0 && target<=nt) {return target-1;}
        else {return -1;}
    }
}
short Duel::makeSpecialMinionMaterialChoice(Card* card)
{
    if (this->uiBridge!=nullptr)
    {
        return this->uiBridge->makeSpecialMinionMaterialChoice(card);
    }
    else
    {
        Card** targets = card->getCardName()->getTargetList()->getTargetList();
        short nt = card->getCardName()->getTargetList()->getTargetsNumber();
        short target;
        std::cout<<"0 - cancel"<<std::endl;
        for (int i=0;i<nt;i++)
        {
            std::cout<<i+1<<" - "<<targets[i]->getName()<<std::endl;
        }
        std::cout<<"Select minion: ";
        std::cin>>target;
        if (target>=0 && target<=nt) {return target-1;}
        else {return -1;}
    }
}
void Duel::turnStartLog()
{
    this->lastSource = 2;
    std::string str = "Turn "+std::to_string(this->turnCount);
    this->appendLog(str, this->lastSource);
}
void Duel::turnEndLog()
{
    this->lastSource = 2;
    std::string str = "End of turn";
    this->appendLog(str, this->lastSource);
}
void Duel::appendLog(std::string log, short log_source)
{
    int n = this->n_logs + 1;
    std::string* logsNew = new std::string[n];
    short* sourcesNew = new short [n];
    for (int i=0;i<this->n_logs;i++)
    {
        logsNew[i] = this->logs[i];
        sourcesNew[i] = this->logsSource[i];
    }
    logsNew[this->n_logs] = log;
    sourcesNew[this->n_logs] = log_source;
    delete [] this->logs; delete [] this->logsSource;
    this->logs = logsNew;
    this->logsSource = sourcesNew;
    this->n_logs = n;

}
short Duel::getPlayerId(Player* player)
{
    if (&this->players[0] == player) {return 0;}
    else return 1;
}
std::string Duel::cardFromHandLog(Card* card)
{
    std::string card_name = std::string(card->getName());
    std::string playername = card->getOwner()->getName();
    std::string str = "["+playername + "] played " + "\"" + card_name + "\"";
    return str;
}
std::string Duel::manaChangeLog(Player* player, short value)
{
    short manaBefore = player->getMana();
    short manaAfter = player->getMana() + value;
    std::string playername = std::string(player->getName());
    if (manaAfter<0) {manaAfter = 0;}
    std::string str = "["+ playername + "]'s mana:  " + std::to_string(manaBefore) + " -> " + std::to_string(manaAfter);
    return str;
}
std::string Duel::lifeChangeLog(Player* player, short value)
{
    short lifeBefore = player->getHp();
    short lifeAfter = player->getHp() + value;
    std::string playername = std::string(player->getName());
    if (lifeAfter<0) {lifeAfter = 0;}
    std::string str = "["+ playername + "]'s life:  " + std::to_string(lifeBefore) + " -> " + std::to_string(lifeAfter);
    return str;
}
std::string Duel::drawCardLog(Player* player, short n)
{
    std::string playername = std::string(player->getName());
    std::string str;
    if (n == 1)
    {
        str = "["+ playername + "] draws a card";
    }
    else
    {
        str = "["+ playername + "] draws " + std::to_string(n) + " cards";
    }
    return str;
}
std::string Duel::summonLog(Card* card)
{
    std::string card_name = std::string(card->getName());
    std::string str = "[" + card_name +"]"+" was summoned";
    return str;
}
std::string Duel::returnToHandLog(Card* card)
{
    std::string card_name = std::string(card->getName());
    std::string playername = card->getOriginalOwner()->getName();
    short type = card->getCardType();
    std::string str;
    if (type==2)
    {
        str = "[" + card_name +"]"+" was returned to ["+ playername +"]'s special deck";
    }
    else
    {
        str = "[" + card_name +"]"+" was returned to ["+ playername +"]'s hand";
    }
    return str;
}
std::string Duel::attackLog(Card* attacker, Card* defender)
{
    std::string attacker_name = std::string(attacker->getName());
    std::string defender_name = std::string(defender->getName());
    std::string atkStats = "("+std::to_string(attacker->getAttack()) + "/" + std::to_string(attacker->getDefence())+")";
    std::string defStats = "("+std::to_string(defender->getAttack()) + "/" + std::to_string(defender->getDefence())+")";
    std::string str = "[" + attacker_name +" "+atkStats+"] attacks " + "[" + defender_name +" "+defStats+"]";
    return str;
}
std::string Duel::directAttackLog(Card* attacker)
{
    std::string attacker_name = std::string(attacker->getName());
    std::string atkStats = "("+std::to_string(attacker->getAttack()) + "/" + std::to_string(attacker->getDefence())+")";
    std::string str = "[" + attacker_name +" "+atkStats+"] attacks directly";
    return str;
}
std::string Duel::destructionLog(Card* card)
{
    std::string card_name = std::string(card->getName());
    std::string playername = card->getOwner()->getName();
    std::string str = "["+ card_name +"]" +" was destroyed";
    return str;
}
std::string Duel::barrierChangeLog(Card* card, short b)
{
    std::string card_name = std::string(card->getName());
    short barrier_before = card->getBarrier();
    short barrier_new = barrier_before + b;
    if (barrier_new<0) {barrier_new = 0;}
    std::string str = "["+ card_name + "]'s barrier:  " + std::to_string(barrier_before) + " -> " + std::to_string(barrier_new);
    return str;
}
std::string Duel::statChangeLog(Card* card, short a_new, short d_new)
{
    short a = card->getAttack();
    short d = card->getDefence();
    std::string card_name = std::string(card->getName());
    std::string stats = "("+std::to_string(a)+"/"+std::to_string(a)+")";
    std::string stats_new = "("+std::to_string(a_new)+"/"+std::to_string(a_new)+")";
    std::string str ="["+ card_name + "]'s stats:  " + stats + " -> " + stats_new;
    return str;
}
std::string Duel::levelChangeLog(Card* card, short l)
{
    std::string card_name = std::string(card->getName());
    short level_before = card->getLevel();
    short level_new = l;
    if (level_new<0) {level_new = 1;}
    std::string str = "["+ card_name + "]'s level:  " + std::to_string(level_before) + " -> " + std::to_string(level_new);
    return str;
}





