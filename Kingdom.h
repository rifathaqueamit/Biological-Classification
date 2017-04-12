#ifndef KINGDOM_H_INCLUDED
#define KINGDOM_H_INCLUDED

#include "Rank.h"

class Kingdom : public Rank
{
public:
    Kingdom() {Rank_Name = ""; Type = Kingdom_Type; Top_Level = true;}
    Kingdom(string Name);
};

#endif // KINGDOM_H_INCLUDED
