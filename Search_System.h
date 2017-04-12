#ifndef SEARCH_SYSTEM_H_INCLUDED
#define SEARCH_SYSTEM_H_INCLUDED

#include "Database.h"
#include "Rank.h"

class Search_System
{
public:
    Database *Base;
    Search_System() {};
    Search_System(Database *);
    Rank* Search_For_Rank(string);
    Rank* Search_For_Indexed_Sub_Rank(Rank*, int);
    Rank* Search_For_Indexed_Upper_Rank(Rank*, int);
};

#endif // SEARCH_SYSTEM_H_INCLUDED
