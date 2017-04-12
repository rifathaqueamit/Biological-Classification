#ifndef RANK_H_INCLUDED
#define RANK_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;

enum Rank_Type
{
    Null_Type = 0,
    Kingdom_Type,
    Phylum_Type,
    Sub_Phylum_Type,
    Class_Type,
    Sub_Class_Type,
    Infra_Class_Type,
    Order_Type,
    Sub_Order_Type,
    Super_Family_Type,
    Family_Type,
    Genus_Type,
    Species_Type
};

class Rank
{
public:
    string Rank_Name;
    Rank_Type Type;
    vector<Rank> Sub_Ranks;

    Rank *Parent;
    bool Top_Level;

    Rank() {Rank_Name = ""; Type = Null_Type; Top_Level = false;}
    Rank(string, Rank_Type, bool);
    int Add_Sub_Rank(string, Rank_Type);
    int Add_Sub_Rank(Rank);
    void Delete_Sub_Rank(int);
    void Clear_Sub_Ranks();
    Rank& Get_Sub_Rank(int);
    Rank* Get_Parent();
    Rank& Get_Parent_Reference();
    int Contains(string);
};

#endif // RANK_H_INCLUDED
