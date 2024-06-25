#ifndef CARDCATALOG_H
#define CARDCATALOG_H
#include "catalogentry.h"

class CardCatalog
{
private:
    CatalogEntry* catalogEntries;
    int n_entries;
public:
    CardCatalog();
    void addEntry(CatalogEntry entry);
    CatalogEntry* getEntryByCardId(int id);
};

#endif // CARDCATALOG_H
