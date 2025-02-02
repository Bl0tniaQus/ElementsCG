#include "gamestate.h"
#include "zone.h"
#include "card.h"
#include <iostream>
Gamestate::Gamestate()
{

}
Gamestate::Gamestate(Duel* duel):Duel()
{
    this->setTurnCount(duel->getTurnCount());
    this->setTurnPlayer(duel->getTurnPlayer());
    std::vector<std::vector<short>>* usedZonesArr = new std::vector<std::vector<short>>(2);
    short* cardsOnFieldArr = new short(2);
    std::vector<std::vector<int>>* fieldCardsArr = new std::vector<std::vector<int>>(2);
    Player* player;
    Player* player_new;
    for (int i=0;i<2;i++)
    {
        player = duel->getPlayer(i);
        player_new = this->getPlayer(i);
        player_new->setHp(player->getHp());
        player_new->setMana(player->getMana());
        player_new->setName(player->getName());
        player_new->setSummonLimit(player->getSummonLimit());
        if (player->getBot()!=nullptr) {player_new->setBot(player->getBot());}
        player_new->setOpponent(this->getPlayer(!i));

        short handSize = player->getHandSize();
        int* cardsInHand = new int [handSize];
        std::vector<Card*>* hand = player->getHand();
        for (int i=0;i<handSize;i++)
        {cardsInHand[i] = hand->at(i)->getCopyId();}

        short cardsOnField = 0;
        std::vector<short> usedZones(0);
        std::vector<int> fieldCards(0);
        Zone *field;
        for (int j=0;j<5;j++)
        {
            field = &player->getMinionField()[j];
            if (field->getUsed())
            {
                cardsOnField++;
                usedZones.push_back(field->getId());
                fieldCards.push_back(field->getCard()->getCopyId());
            }
        }

        short graveyardSize = player->getGraveyardSize();
        int* cardsInGraveyard = new int [graveyardSize];
        std::vector<Card*>* graveyard = player->getGraveyard();
        for (int j=0;j<graveyardSize;j++){cardsInGraveyard[j] = graveyard->at(j)->getCopyId();}

        short deckSize = player->getDeckSize();
        int* cardsInDeck = new int [deckSize];
        std::vector<Card*>* deck = player->getDeck();
        for (int j=0;j<deckSize;j++){cardsInDeck[j] = deck->at(j)->getCopyId();}

        short specialDeckSize = player->getSpecialDeckSize();
        int* cardsInSpecialDeck = new int [specialDeckSize];
        std::vector<Card*>* specialDeck = player->getSpecialDeck();
        for (int j=0;j<specialDeckSize;j++){cardsInSpecialDeck[j] = specialDeck->at(j)->getCopyId();}

        short originalDeckSize = player->getOriginalDeckSize();
        short originalSpecialDeckSize = player->getOriginalSpecialDeckSize();
        std::vector<Card>* originalDeck = player->getOriginalDeck();
        std::vector<Card>* originalSpecialDeck = player->getOriginalSpecialDeck();

        Deck* OGDeck = new Deck(*originalDeck, *originalSpecialDeck);
        player_new->setOriginalDeck(*OGDeck->getDeck());
        player_new->setOriginalSpecialDeck(*OGDeck->getSpecialDeck());
        delete OGDeck;


        std::vector<Card*> deckCopy = std::vector<Card*>(deckSize);
        std::vector<Card*> specialDeckCopy = std::vector<Card*>(specialDeckSize);
        std::vector<Card>* originalDeckCopy = player_new->getOriginalDeck();
        std::vector<Card>* originalSpecialDeckCopy = player_new->getOriginalSpecialDeck();
        player_new->setDeckOwnership();
        for (short j = 0; j<originalDeckSize; j++)
        {
            originalDeckCopy->at(j).copyProperties(&originalDeck->at(j));
            originalDeckCopy->at(j).copyCardName(originalDeck->at(j).getCardName());
        }

        for (int j=0;j<deckSize;j++)
        {
            int id = cardsInDeck[j];
            for (int k=0;k<originalDeckSize;k++)
            {
                int originalId = originalDeckCopy->at(k).getCopyId();
                if (id==originalId)
                {
                    deckCopy[j] = &originalDeckCopy->at(k);
                    break;
                }
            }
        }

        for (short j = 0; j<originalSpecialDeckSize; j++)
        {
            originalSpecialDeckCopy->at(j).copyProperties(&originalSpecialDeck->at(j));
            originalSpecialDeckCopy->at(j).copyCardName(originalSpecialDeck->at(j).getCardName());
        }
        for (int j=0;j<specialDeckSize;j++)
        {
            int id = cardsInSpecialDeck[j];
            for (int k=0;k<originalSpecialDeckSize;k++)
            {
                int originalId = originalSpecialDeckCopy->at(k).getCopyId();
                if (id==originalId)
                {
                    specialDeckCopy[j] = &originalSpecialDeckCopy->at(k);
                    break;
                }
            }
        }
        player_new->setDeck(deckCopy);
        player_new->setSpecialDeck(specialDeckCopy);
        std::vector<Card*> handCopy = std::vector<Card*>(handSize);
        for (int j=0;j<handSize;j++)
        {
            int id = cardsInHand[j];
            for (int k=0;k<originalDeckSize;k++)
            {
                int originalId = originalDeckCopy->at(k).getCopyId();
                if (id==originalId)
                {
                    handCopy[j] = &originalDeckCopy->at(k);
                    break;
                }
            }
        }
        std::vector<Card*> graveyardCopy = std::vector<Card*>(graveyardSize);
        for (int j=0;j<graveyardSize;j++)
        {
            int id = cardsInGraveyard[j];
            for (int k=0;k<originalDeckSize;k++)
            {
                int originalId = originalDeckCopy->at(k).getCopyId();
                if (id==originalId)
                {
                    graveyardCopy[j] = &originalDeckCopy->at(k);
                    break;
                }
            }
            for (int k=0;k<originalSpecialDeckSize;k++)
            {
                int originalId = originalSpecialDeckCopy->at(k).getCopyId();
                if (id==originalId)
                {
                    graveyardCopy[j] = &originalSpecialDeckCopy->at(k);
                    break;
                }
            }
        }

        player_new->setHand(handCopy);
        player_new->setGraveyard(graveyardCopy);

        usedZonesArr->at(i) = usedZones;
        cardsOnFieldArr[i] = cardsOnField;
        fieldCardsArr->at(i) = fieldCards;
        player = nullptr;
        player_new = nullptr;
        delete[] cardsInHand;
        delete[] cardsInGraveyard;
        delete[] cardsInDeck;
        delete[] cardsInSpecialDeck;
    }
    for (int i=0;i<2;i++)
    {
        std::vector<Card>* originalDeck = this->getPlayer(i)->getOriginalDeck();
        short originalDeckSize = this->getPlayer(i)->getOriginalDeckSize();
        std::vector<Card>* originalSpecialDeck =  this->getPlayer(i)->getOriginalSpecialDeck();
        short originalSpecialDeckSize = this->getPlayer(i)->getOriginalSpecialDeckSize();
        std::vector<Card>* originalDeckOpp = this->getPlayer(!i)->getOriginalDeck();
        short originalDeckSizeOpp = this->getPlayer(!i)->getOriginalDeckSize();
        std::vector<Card>* originalSpecialDeckOpp =  this->getPlayer(!i)->getOriginalSpecialDeck();
        short originalSpecialDeckSizeOpp = this->getPlayer(!i)->getOriginalSpecialDeckSize();
        for (int j = 0; j<cardsOnFieldArr[i];j++)
        {
            bool found = false;
            short zone = usedZonesArr->at(i)[j];
            int id = fieldCardsArr->at(i)[j];
            for (int k = 0; k<originalDeckSize;k++)
            {
                int originalId = originalDeck->at(k).getCopyId();
                if (id==originalId)
                {
                    this->getPlayer(i)->getMinionField()[zone].bindCard(&originalDeck->at(k));
                    this->getPlayer(i)->getMinionField()[zone].setUsed(true);
                    found = true;
                    break;
                }
            }
            if (found) {continue;}
            for (int k = 0; k<originalSpecialDeckSize;k++)
            {
                int originalId = originalSpecialDeck->at(k).getCopyId();
                if (id==originalId)
                {
                    this->getPlayer(i)->getMinionField()[zone].bindCard(&originalSpecialDeck->at(k));
                    this->getPlayer(i)->getMinionField()[zone].setUsed(true);
                    found = true;
                    break;
                }
            }
            if (found) {continue;}
            for (int k = 0; k<originalDeckSizeOpp;k++)
            {
                int originalId = originalDeckOpp->at(k).getCopyId();
                if (id==originalId)
                {
                    originalDeckOpp->at(k).setOwner(this->getPlayer(i));
                    this->getPlayer(i)->getMinionField()[zone].bindCard(&originalDeckOpp->at(k));
                    found = true;
                    break;
                }
            }
            if (found) {continue;}
            for (int k = 0; k<originalSpecialDeckSizeOpp;k++)
            {
                int originalId = originalSpecialDeckOpp->at(k).getCopyId();
                if (id==originalId)
                {
                    originalSpecialDeckOpp->at(k).setOwner(this->getPlayer(i));
                    this->getPlayer(i)->getMinionField()[zone].bindCard(&originalSpecialDeckOpp->at(k));
                    found = true;
                    break;
                }
            }
        }
    }

        delete usedZonesArr;
        delete fieldCardsArr;
        delete cardsOnFieldArr;

    short n_lingering_end = duel->getTurnEndLingeringEffectsNumber();
    short n_lingering_start = duel->getTurnStartLingeringEffectsNumber();
    Card** turnEndLingering = duel->getTurnEndLingeringEffects();
    Card** turnStartLingering = duel->getTurnStartLingeringEffects();
    Card* c;
    for (short i=0;i<n_lingering_end;i++)
    {
        c = this->getCardFromCopyId(turnEndLingering[i]->getCopyId());
        this->addTurnEndLingeringEffect(c);
    }
    for (short i=0;i<n_lingering_start;i++)
    {
        c = this->getCardFromCopyId(turnStartLingering[i]->getCopyId());
        this->addTurnStartLingeringEffect(c);
    }
}
float Gamestate::resourceFactor()
{
    Player* player = this->getPlayer(this->getTurnPlayer());
    Player* opponent = player->getOpponent();

    short playerHp = player->getHp();
    short playerMana = player->getMana();
    short opponentHp = opponent->getHp();
    short opponentMana = opponent->getMana();

    if (opponentHp<=0) {return 99999;}

    float f_oppHp = 1 + ((30/(opponentHp))*1.5)/100;
    float f_pHp = 1 + playerHp/100;
    float f_oppMana = 1 + (15/(opponentMana+0.01) * 2)/20;
    float f_pMana = 1 + (playerMana * 0.7)/30;
    float f_hpDiff = 1 + ((playerHp - opponentHp) * 1.2) / 50;
    float f_manaDiff = 1 + ((playerMana - opponentMana) * 0.3) / 70;
    float factor = f_oppHp * f_pHp * f_oppMana * f_pMana * f_hpDiff * f_manaDiff;

    return factor;

}
float Gamestate::cardAdvantageFactor()
{
    Player* player = this->getPlayer(this->getTurnPlayer());
    Player* opponent = player->getOpponent();

    short playerHand = player->getHandSize();
    short opponentHand = opponent->getHandSize();

    short playerFieldCount = player->getMinionCount();
    short opponentFieldCount = player->getMinionCount();


    float f_cardDiff = 1 + ((playerHand + playerFieldCount) - (opponentHand + opponentFieldCount))/50.0;

    float factor = f_cardDiff;

    return factor;
}
float Gamestate::fieldPresenceFactor()
{
    float factor;

    Player* player = this->getPlayer(this->getTurnPlayer());
    Player* opponent = player->getOpponent();

    Zone* playerField = player->getMinionField();
    Zone* opponentField = opponent->getMinionField();

    short n_playerMinions = player->getMinionCount();
    short n_opponentMinions = opponent->getMinionCount();

    short highestLvl = -1, highestLvlOpp = -1;
    short sumLvl = 0, sumLvlOpp = 0;
    short highestAtk = -1, highestAtkOpp = -1, highestDef = -1, highestDefOpp = -1;
    short sumAtk = 0, sumDef = 0, sumAtkOpp = 0, sumDefOpp = 0;
    Card* card;
    for (int i = 0; i<5; i++)
    {
        short atk;
        short def;
        short lvl;
        card = playerField[i].getCard();
        if (card!=nullptr)
        {
            atk = card->getAttack();
            def = card->getDefence();
            lvl = card->getLevel();
            if (atk>highestAtk) {highestAtk = atk;}
            if (def>highestDef) {highestDef = def;}
            if (lvl>highestLvl) {highestLvl = lvl;}
            sumLvl = sumLvl + lvl;
            sumAtk = sumAtk + atk;
            sumDef = sumDef + def;
        }
        card = opponentField[i].getCard();
        if (card!=nullptr)
        {
            atk = card->getAttack();
            def = card->getDefence();
            lvl = card->getLevel();
            if (atk>highestAtkOpp) {highestAtkOpp = atk;}
            if (def>highestDefOpp) {highestDefOpp = def;}
            if (lvl>highestLvlOpp) {highestLvlOpp = lvl;}
            sumLvlOpp = sumLvlOpp + lvl;
            sumAtkOpp = sumAtkOpp + atk;
            sumDefOpp = sumDefOpp + def;
        }
    }
    this->generateAttackersList();
    this->generateDefendersList();
    std::vector<Card*>* attackers = this->getAttackersList()->getTargetList();
    short n_attackers = this->getAttackersList()->getTargetsNumber();
    std::vector<Card*>* defenders = this->getDefendersList()->getTargetList();
    short n_defenders = this->getDefendersList()->getTargetsNumber();

    //offense
    short vulnerable_defenders = 0;
    for (int i=0;i<n_defenders;i++)
    {
        Card* defender = defenders->at(i);
        for (int j=0;j<n_attackers;j++)
        {
            Card* attacker = attackers->at(j);
            if (attacker->getAttack()>defender->getDefence())
            {
                vulnerable_defenders++;
                break;
            }
        }
    }
    //defence
    short possible_attacks = n_attackers * n_defenders;
    short mitigated_attacks = 0;
    short barriers = 0;
    for (int i=0;i<n_attackers;i++)
    {
        Card* defender = attackers->at(i); //turn player's defence
        for (int j=0;j<n_defenders;j++)
        {
            Card* attacker = defenders->at(j); //opponent's offense
            if (defender->getDefence()>=attacker->getAttack())
            {
                mitigated_attacks++;
            }
            if (defender->getBarrier()>0)
            {
                barriers += defender->getBarrier();
            }
        }
    }
    float f_pressenceLvl = 1 + ((sumLvl - sumLvlOpp) / 50.0);
    float f_pressenceCount = 1 + (n_playerMinions - n_opponentMinions)/10.0;
    float f_offense = 1 + (sumAtk - sumDefOpp)/30.0;
    float f_defence = 1 + (sumDef - sumAtkOpp)/30.0;
    float f_protection;
    float f_breakthrough;
    if (possible_attacks==0) {f_protection = 1;}
    else {f_protection = 0.5 + (mitigated_attacks/(possible_attacks));}
    if (n_opponentMinions==0) {f_breakthrough = (1 + (n_attackers/10.0))/1.1;}
    else {f_breakthrough = (0.5 + (vulnerable_defenders/n_opponentMinions))/1.1;}


    factor = f_pressenceLvl * f_pressenceCount * f_offense * f_defence;
    return factor;
}

float Gamestate::evaluate()
{
    float resources = this->resourceFactor();
    float cardAdvantage = this->cardAdvantageFactor();
    float fieldPresenceFactor = this->fieldPresenceFactor();

    short resourcesW = 1;
    short cardAdvantageW = 2;
    short fieldPresenceW = 3;
   // std::cout<<resources<<" "<<cardAdvantage<<" "<<fieldPresenceFactor<<std::endl;
    float value = (resources * resourcesW + cardAdvantage * cardAdvantageW + fieldPresenceFactor * fieldPresenceW) / (resourcesW + cardAdvantageW + fieldPresenceW);

    //return (float)(rand()%10 + 0);
    return value;
}

