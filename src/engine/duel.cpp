#include "duel.h"
#include "bot.h"
#include "card.h"
#include "zone.h"
#include <iostream>
#include <QDebug>
Duel::Duel()
{
    players = new Player[2];
    players[0].setOpponent(&players[1]);
    players[1].setOpponent(&players[0]);
    players[0].setName("Player 1");
    players[1].setName("Player 2");
    players[0].setDuel(this);
    players[1].setDuel(this);
    this->turnPlayer = 0;
    this->attackersTargetList = new TargetList;
    this->defendersTargetList = new TargetList;
    this->turnEndLingeringEffects = new Card* [0];
    this->turnStartLingeringEffects = new Card* [0];
    this->uiBridge = nullptr;
    this->n_lingering_end = 0;
    this->n_lingering_start = 0;
    this->logsSource = new short [0];
    this->logs = new std::string [0];
    this->n_logs = 0;
}
Duel::~Duel()
{
    delete this->attackersTargetList;
    delete this->defendersTargetList;
    delete [] this->turnEndLingeringEffects;
    delete [] this->turnStartLingeringEffects;
    delete [] this->logs;
    delete [] this->logsSource;
    delete [] this->players;
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
        std::cout<<opponent->getGraveyard()->at(i)->getName()<<"; ";
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
        std::cout<<player->getHand()->at(i)->getName()<<"; ";
    }std::cout<<std::endl<<"Field: ";
    for (int i=0;i<5;i++)
    {
        if (player->getMinionField()[i].getCard()!=nullptr)
        std::cout<<player->getMinionField()[i].getCard()->getName()<<"; ";
    }std::cout<<std::endl;
    std::cout<<"Graveyard: ";
    for (int i=0;i<player->getGraveyardSize();i++)
    {
        std::cout<<player->getGraveyard()->at(i)->getName()<<"; ";
    }std::cout<<std::endl;
    std::cout<<"Sp. deck: ";
    for (int i=0;i<player->getSpecialDeckSize();i++)
    {
        std::cout<<player->getSpecialDeck()->at(i)->getName()<<"; ";
    }std::cout<<std::endl<<std::endl;
}
void Duel::combat(Card* attacker, Card* defender)
{
    this->appendLog(this->attackLog(attacker,defender),this->turnPlayer);
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
    short hp;
    if (atk>def){
        hp = this->players[this->turnPlayer].getOpponent()->getHp();
        if (damage>hp) {damage = hp;}
        this->players[this->turnPlayer].getOpponent()->changeHp(-damage);
    }
    if (def>atk){
        hp = this->players[this->turnPlayer].getHp();
        if (damage>hp) {damage = hp;}
        this->players[this->turnPlayer].changeHp(-damage);

    }
    attacker->setAttacks(attacker->getAttacks()-1);
    attacker->getCardName()->afterAttack(this,attacker,defender,damage);
    this->checkWinner();
}
void Duel::directAttack(Card* attacker)
{
    this->appendLog(this->directAttackLog(attacker),this->turnPlayer);
    attacker->getCardName()->onAttack(this,attacker,nullptr);
    short damage = attacker->getAttack();
    if (damage>0)
    {
    short hp;
    hp = this->players[this->turnPlayer].getOpponent()->getHp();
    if (damage>hp) {damage = hp;}
    this->players[this->turnPlayer].getOpponent()->changeHp(-damage);
    }
    attacker->setAttacks(attacker->getAttacks()-1);
    attacker->getCardName()->afterAttack(this,attacker,nullptr,damage);
    this->checkWinner();
}
void Duel::checkWinner()
{
    short hp1 = players[0].getHp(); short hp2 = players[1].getHp();
    short result = -1;
    if ((hp1<=0)&&(hp2<=0)) {result = 2;}
    else if ((hp1<=0)&&(hp2>0)) {result = 1;}
    else if ((hp2<=0)&&(hp1>0)) {result = 0;}
    if (result!=-1&&this->uiBridge!=nullptr)
    {
        this->duelEnded = true;
        this->appendLog(this->duelResultLog(result),2);
        this->uiBridge->endDuel(result);
    }

}
void Duel::destruction(Card* card)
{
    short barrier = card->getBarrier();
    if (barrier>0) {
        this->appendLog(this->barrierChangeLog(card,-1),this->getPlayerId(card->getOwner()));
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
void Duel::releaseForSpecialSummon(Card* card, Card* sp_minion)
{
    this->removeFromField(card);
    this->toGraveyard(card);
    card->getCardName()->onSpecialSummonRelease(this,card,sp_minion);
}

void Duel::toGraveyard(Card* card)
{
    card->setPlace(3);
    Player* owner = card->getOriginalOwner();
    card->returnToOriginal();
    owner->addToGraveyard(card);
}
void Duel::toSpecialDeck(Card* card)
{
    if (card->getZone()!=nullptr&&card->getPlace()==2) {this->removeFromField(card);}
    card->setPlace(4);
    Player* owner = card->getOriginalOwner();
    card->returnToOriginal();
    owner->addToSpecialDeck(card);
    this->appendLog(this->returnToHandLog(card),this->getPlayerId(card->getOwner()));
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
        if (minion->getCardName()->specialSummon(this,minion))
        {
            this->summonMinion(minion,this->getEmptyMinionZone(minion->getOriginalOwner()));
            minion->getOriginalOwner()->removeFromSpecialDeck(minion);
            this->onSummon(minion);
            this->checkWinner();
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
        short originalPlace = card->getPlace();
        if (originalPlace == 1 || originalPlace==4) {return;}
        card->setPlace(1);
        card->returnToOriginal();
        if (card->getZone()!=nullptr&&originalPlace==2) {this->removeFromField(card);}
        card->getOriginalOwner()->addToHand(card);
        if (originalPlace == 2 || originalPlace == 3)
        {
            this->appendLog(this->returnToHandLog(card),this->getPlayerId(card->getOwner()));
        }
        if (originalPlace == 0)
        {
            this->appendLog(this->addToHandLog(card),this->getPlayerId(card->getOwner()));
        };
    }

}
void Duel::searchCard(Card* card)
{
    this->toHand(card);
    card->getOwner()->removeFromDeck(card);
    card->getOriginalOwner()->shuffleDeck();
}
void Duel::drawCard(Player* player)
{
    short n_deck = player->getDeckSize();
    if (n_deck>0)
    {
        Card* card = player->getDeck()->at(n_deck-1);
        player->addToHand(card);
        player->removeFromDeck(card);
        this->appendLog(this->drawCardLog(player, 1), this->getPlayerId(player));
    }
}
void Duel::drawCardNoLog(Player* player)
{
    short n_deck = player->getDeckSize();
    if (n_deck>0)
    {
        Card* card = player->getDeck()->at(n_deck-1);
        player->addToHand(card);
        player->removeFromDeck(card);
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
        card->setTurnPlayed(this->turnCount);
        this->appendLog(this->summonLog(card),this->getPlayerId(card->getOwner()));
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
                for (int j=0;j<n_effects-1;j++)
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
                for (int j=0;j<n_effects-1;j++)
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
        if (effects[i]->getCardName()->getHasOnTurnEnd())
        {this->botDelay(200);}
        this->onTurnEnd(effects[i]);
    }
    Card** effectsTE = new Card* [this->n_lingering_end];
    short n = this->n_lingering_end;
    for (int i=0;i<this->n_lingering_end;i++)
    {

        effectsTE[i] = this->turnEndLingeringEffects[i];
    }
    this->clearTurnEndLingeringEffects();
    for (int i=0;i<n;i++)
    {
        this->botDelay(200);
        this->onTurnEnd(effectsTE[i]);
    }
    delete [] effectsTE;
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
                for (int j=0;j<n_effects-1;j++)
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
                for (int j=0;j<n_effects-1;j++)
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
        if (effects[i]->getCardName()->getHasOnTurnStart())
        {this->botDelay(200);}
        this->onTurnStart(effects[i]);
    }
    Card** effectsTS = new Card* [this->n_lingering_start];
    short n = this->n_lingering_start;
    for (int i=0;i<this->n_lingering_start;i++)
    {
        effectsTS[i] = this->turnStartLingeringEffects[i];
    }
    this->clearTurnStartLingeringEffects();
    for (int i=0;i<n;i++)
    {
        this->botDelay(200);
        this->onTurnStart(effectsTS[i]);
    }
    delete [] effectsTS;
    delete [] effects;
}
void Duel::playFromHand(Card* card)
{
    char type = card->getCardType();
    short cost = card->getCost();
    short zoneid;
    short success =0;
    if ((cost<=card->getOwner()->getMana())&&(card->getPlace()==1))
    {
        if ((type==1)&&(card->getOwner()->getSummonLimit()>0))
        {
            zoneid = this->getEmptyMinionZone(card->getOwner());

           if (zoneid!=-1)
           {
               this->appendLog(this->cardFromHandLog(card),this->turnPlayer);
               card->getOwner()->changeMana(-cost);
               this->summonMinion(card, zoneid);
               success=1;
           }
        }
        else if (type==0)
        {
            if (this->activateSpell(card))
            {
                card->setTurnPlayed(this->turnCount);
                this->toGraveyard(card);
                success=1;
            }
        }
        if (success==1)
        {
            card->getOwner()->removeFromHand(card);
            if (type==1) {
                card->getOriginalOwner()->setSummonLimit(card->getOriginalOwner()->getSummonLimit()-1);
                this->onSummon(card);
            }
        }

    }
    this->checkWinner();
}
void Duel::summonFromHand(Card* minion, short zoneid)
{
    if ((minion->getCardType()==1)&&(minion->getPlace()==1))
    {

        minion->setPlace(2);
        minion->getOriginalOwner()->getMinionField()[zoneid].bindCard(minion);
        minion->getOriginalOwner()->getMinionField()[zoneid].setUsed(true);
        minion->getOriginalOwner()->removeFromHand(minion);
        this->onSummon(minion);

    }
}
void Duel::summonFromGraveyard(Card* minion, short zoneid)
{
    if ((minion->getCardType()>0)&&(minion->getPlace()==3))
    {
        minion->setPlace(2);
        minion->getOwner()->getMinionField()[zoneid].bindCard(minion);
        minion->getOwner()->getMinionField()[zoneid].setUsed(true);
        minion->getOriginalOwner()->removeFromGraveyard(minion);
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
void Duel::changeBarrier(Card* card, short b)
{
    this->appendLog(this->barrierChangeLog(card,b), this->getPlayerId(card->getOwner()));
    card->setBarrier(b);
}
void Duel::changeSpellImmunity(Card* card, bool si)
{
    if (card->getIsSpellImmune()&&si==false)
    {
        this->appendLog(this->spellImmunityChangeLog(card,si),this->getPlayerId(card->getOwner()));
    }
    else if (si==true)
    {
        this->appendLog(this->spellImmunityChangeLog(card,si),this->getPlayerId(card->getOwner()));
    }
    card->setIsSpellImmune(si);
}

void Duel::excavateCard(Card* card)
{
    this->appendLog(this->excavateCardLog(card), this->getPlayerId(card->getOriginalOwner()));
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
        this->drawCard(opponent);
    }

    opponent->changeMana(2);
    this->turnStartEffects();
}
void Duel::generateAttackersList(Player* player)
{
    std::vector<Card*> attackers = std::vector<Card*>(0);
    for (int i=0;i<5;i++)
    {
        Zone* zone = &player->getMinionField()[i];
        Card* card = zone->getCard();
        if (card!=nullptr)
        {
            if (card->getAttacks()>0)
            {
                attackers.push_back(card);
            }
        }
    }
    this->getAttackersList()->setTargetList(attackers);
}
void Duel::generateDefendersList(Player* player)
{
    std::vector<Card*> defenders = std::vector<Card*>(0);
    for (int i=0;i<5;i++)
    {
        Zone* zone = &player->getOpponent()->getMinionField()[i];
        Card* card = zone->getCard();
        if (card!=nullptr)
        {
            defenders.push_back(card);
        }
    }
    this->getDefendersList()->setTargetList(defenders);
}
Card* Duel::getCardFromCopyId(int id)
{
    short n_deck,n_special;
    std::vector<Card>* deck;
    n_deck = players[0].getOriginalDeckSize();
    deck = players[0].getOriginalDeck();
    int id_card;
    for (int i=0;i<n_deck;i++)
    {
        id_card = deck->at(i).getCopyId();
        if (id_card==id) return &deck->at(i);
    }
    n_special = players[0].getOriginalSpecialDeckSize();
    deck = players[0].getOriginalSpecialDeck();
    for (int i=0;i<n_special;i++)
    {
        id_card = deck->at(i).getCopyId();
        if (id_card==id) return &deck->at(i);
    }
    n_deck = players[1].getOriginalDeckSize();
    deck = players[1].getOriginalDeck();
    for (int i=0;i<n_deck;i++)
    {
        id_card = deck->at(i).getCopyId();
        if (id_card==id) return &deck->at(i);
    }
    n_special = players[1].getOriginalSpecialDeckSize();
    deck = players[1].getOriginalSpecialDeck();
    for (int i=0;i<n_special;i++)
    {
        id_card = deck->at(i).getCopyId();
        if (id_card==id) return &deck->at(i);
    }
    return nullptr;
}
void Duel::botDelay(int ms)
{
    if (this->uiBridge!=nullptr)
    {
        uiBridge->delay(ms);
    }
}
void Duel::startDuel(Deck *deck0, Deck* deck1)
{
    int j = rand() % 2;
    this->turnPlayer=j;
    this->turnCount=1;
    this->turnStartLog();
    this->getPlayer(0)->setOriginalDeck(*deck0->getDeck());
    this->getPlayer(0)->setOriginalSpecialDeck(*deck0->getSpecialDeck());
    this->getPlayer(0)->setDeckOwnership();
    this->getPlayer(1)->setOriginalDeck(*deck1->getDeck());
    this->getPlayer(1)->setOriginalSpecialDeck(*deck1->getSpecialDeck());
    this->getPlayer(1)->setDeckOwnership();
    this->getPlayer(0)->shuffleDeck();
    this->getPlayer(1)->shuffleDeck();
    for (int i=0;i<5;i++)
    {
        this->drawCardNoLog(&this->players[0]);
        this->drawCardNoLog(&this->players[1]);
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
           bot->playTurn(this);
           bot->generateBaseGamestate(this);
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
                        std::cout<<i+1<<" - "<<turnPlayer->getHand()->at(i)->getName()<<" ("<<turnPlayer->getHand()->at(i)->getCost()<<")"<<std::endl;
                    }
                    std::cout<<"Choice: ";
                    std::cin>>target;
                    if((target>0)&&(target<=turnPlayer->getHandSize()+1))
                    {this->playFromHand(turnPlayer->getHand()->at(target-1));}

                }
                if (choice==1)
                {
                    short target;
                    std::cout<<"0 - cancel"<<std::endl;
                    for (int i=0;i<turnPlayer->getSpecialDeckSize();i++)
                    {
                        std::cout<<i+1<<" - "<<turnPlayer->getSpecialDeck()->at(i)->getName()<<std::endl;
                    }
                    std::cout<<"Choice: ";
                    std::cin>>target;
                    if((target>0)&&(target<=turnPlayer->getSpecialDeckSize()+1))
                    {this->summonSpecialMinion(turnPlayer->getSpecialDeck()->at(target-1));}
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
int Duel::makeSpellChoice(Card* card)
{
    if (this->uiBridge!=nullptr)
    {
        return this->uiBridge->makeSpellChoice(card);
    }
    else
    {
        std::vector<Card*>* targets = card->getCardName()->getTargetList()->getTargetList();
        short nt = card->getCardName()->getTargetList()->getTargetsNumber();
        short target;
        std::cout<<"0 - cancel"<<std::endl;
        for (int i=0;i<nt;i++)
        {
            std::cout<<i+1<<" - "<<targets->at(i)->getName()<<std::endl;
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
        std::vector<Card*>* targets = card->getCardName()->getTargetList()->getTargetList();
        short nt = card->getCardName()->getTargetList()->getTargetsNumber();
        short target;
        std::cout<<"0 - cancel"<<std::endl;
        for (int i=0;i<nt;i++)
        {
            std::cout<<i+1<<" - "<<targets->at(i)->getName()<<std::endl;
        }
        std::cout<<"Select minion: ";
        std::cin>>target;
        if (target>=0 && target<=nt) {return target-1;}
        else {return -1;}
    }
}
void Duel::addTurnEndLingeringEffect(Card* card)
{
    this->n_lingering_end++;
    Card** newLingering = new Card* [this->n_lingering_end];
    if (this->n_lingering_end==1) {newLingering[0] = card;}
    else{
        for (int i=0; i<n_lingering_end-1;i++)
        {
            newLingering[i] = this->turnEndLingeringEffects[i];
        }
        newLingering[n_lingering_end-1] = card;
    }
    delete[] this->turnEndLingeringEffects;
    this->turnEndLingeringEffects = newLingering;
}
void Duel::clearTurnEndLingeringEffects()
{
    delete [] this->turnEndLingeringEffects;
    this->n_lingering_end = 0;
    this->turnEndLingeringEffects = new Card* [0];
}
void Duel::addTurnStartLingeringEffect(Card* card)
{
    this->n_lingering_start++;
    Card** newLingering = new Card* [this->n_lingering_start];
    if (this->n_lingering_start==1) {newLingering[0] = card;}
    else{
        for (int i=0; i<n_lingering_start-1;i++)
        {
            newLingering[i] = this->turnStartLingeringEffects[i];
        }
        newLingering[n_lingering_start-1] = card;
    }
    delete[] this->turnStartLingeringEffects;
    this->turnStartLingeringEffects = newLingering;
}
void Duel::clearTurnStartLingeringEffects()
{
    delete [] this->turnStartLingeringEffects;
    this->n_lingering_start = 0;
    this->turnStartLingeringEffects = new Card* [0];
}

void Duel::updateBoard()
{
    if (this->uiBridge!=nullptr)
    {
        this->uiBridge->updateBoard();
    }
}

void Duel::turnStartLog()
{
    std::string str = "Turn "+std::to_string(this->turnCount);
    this->appendLog(str, 2);
}
void Duel::turnEndLog()
{
    std::string str = "End of turn";
    this->appendLog(str, 2);
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
    std::string str = "["+playername + "] played " + "[" + card_name + "]";
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
    std::string stats = "("+std::to_string(a)+"/"+std::to_string(d)+")";
    std::string stats_new = "("+std::to_string(a_new)+"/"+std::to_string(d_new)+")";
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
std::string Duel::addToHandLog(Card* card)
{
    std::string card_name = std::string(card->getName());
    std::string playername = card->getOriginalOwner()->getName();
    std::string str;
    str = "[" + playername +"]"+" has added ["+ card_name +"] to their hand";
    return str;
}
std::string Duel::excavateCardLog(Card* card)
{
    std::string card_name = std::string(card->getName());
    std::string playername = card->getOwner()->getName();
    std::string str = "["+ playername +"]" +" reveals [" + card_name + "]";
    return str;
}
std::string Duel::spellImmunityChangeLog(Card* card, bool change)
{
    std::string card_name = std::string(card->getName());
    std::string str;
    if (change)
    {
        str = "["+ card_name +"]" +" is now immune to spells";
    }
    else if (!change)
    {
        str = "["+ card_name +"]" +" is now vulnerable to spells";
    }
    return str;
}
std::string Duel::spellImmunityMessageLog(Card* effect, Card* minion)
{
    std::string effect_name = std::string(effect->getName());
    std::string minion_name = std::string(minion->getName());
    std::string str = "["+ minion_name +"]" +" is unaffected by [" + effect_name + "]";
    return str;
}
void Duel::appendSILog(Card* effect, Card* minion)
{
    this->appendLog(this->spellImmunityMessageLog(effect,minion),this->getPlayerId(minion->getOwner()));
}
std::string Duel::duelResultLog(short res)
{
    std::string str;
    if (res==0 || res==1)
    {
        std::string playername = std::string(this->players[res].getName());
        str = "["+ playername +"] has won the duel!";
    }
    else if (res==2)
    {
        str = "Duel had ended with a draw.";
    }
    return str;
}





