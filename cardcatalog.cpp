#include "cardcatalog.h"
#include <iostream>
CardCatalog::CardCatalog()
{
    this->n_entries=0;
    this->catalogEntries = new CatalogEntry[0];
    //0 - spell, 1 - minion, 2 - sminion
    //id,name,element,cost,type,level,atk,def
    this->addEntry(CatalogEntry(1,"Copper Worm", "Earth", 1, 1,1,1,1));
    this->addEntry(CatalogEntry(2,"Silver Wolf", "Earth", 4, 1,3,5,3));
    this->addEntry(CatalogEntry(3,"Dragonoid Soldier", "Air", 2, 1,3,3,4));
    this->addEntry(CatalogEntry(4,"Whirlwind", "Wind", 5, 0,-1,-1,-1));
    this->addEntry(CatalogEntry(5,"Dragonoid Sage", "Air", 3, 1,3,2,3));
    this->addEntry(CatalogEntry(6,"Tungsten Firefly", "Earth", 2, 1,2,2,2));
    this->addEntry(CatalogEntry(7,"Dragonoid Scout", "Air", 3, 1,3,3,2));
    this->addEntry(CatalogEntry(8,"Brass Beetle", "Earth", -1, 2,5,4,5));


}
void CardCatalog::addEntry(CatalogEntry entry)
{
    this->n_entries++;
    CatalogEntry *newCatalog = new CatalogEntry[this->n_entries+1];
    for (int i=0; i<n_entries-1;i++)
    {
        newCatalog[i] = this->catalogEntries[i];
    }
    delete[] this->catalogEntries;
    this->catalogEntries = newCatalog;
    this->catalogEntries[this->n_entries-1] = entry;
}
CatalogEntry* CardCatalog::getEntryByCardId(int id)
{

    for (int i=0;i<this->n_entries;i++)
    {
        if (this->catalogEntries[i].getId()==id)
        {
            return &catalogEntries[i];
        }
    }
    return nullptr;
}
