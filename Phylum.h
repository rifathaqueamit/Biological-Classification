#ifndef PHYLUM_H_INCLUDED
#define PHYLUM_H_INCLUDED

#include "Rank.h"

class Phylum : public Rank
{
public:
    Phylum() {Rank_Name = ""; Type = Phylum_Type; Top_Level = false;}
    Phylum(string Name);
};

#endif // PHYLUM_H_INCLUDED
