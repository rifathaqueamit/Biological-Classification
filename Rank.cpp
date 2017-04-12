#include "Rank.h"
#include <vector>

Rank::Rank(string Name, Rank_Type Type_Of_Rank, bool Root_Level)
{
    Rank_Name = Name;
    Type = Type_Of_Rank;
    Top_Level = Root_Level;
}

int Rank::Add_Sub_Rank(string Name, Rank_Type Type_Of_Rank)
{
    Rank New_Rank = Rank(Name, Type_Of_Rank, false);
    New_Rank.Parent = this;
    Sub_Ranks.push_back(New_Rank);
    return Sub_Ranks.size() - 1;
}

int Rank::Add_Sub_Rank(Rank Rank_Object)
{
    Rank_Object.Parent = this;
    Sub_Ranks.push_back(Rank_Object);
    return Sub_Ranks.size() - 1;
}

Rank& Rank::Get_Sub_Rank(int ID)
{
    return Sub_Ranks[ID];
}

Rank* Rank::Get_Parent()
{
    if (Top_Level == false)
    {
        return Parent;
    }
    else
    {
        return NULL;
    }
}

Rank& Rank::Get_Parent_Reference()
{
    return *Parent;
}

int Rank::Contains(string Rank_Name)
{
    int I;
    for (I = 0; I < Sub_Ranks.size(); I++)
    {
        if (Sub_Ranks[I].Rank_Name == Rank_Name)
        {
            return I;
        }
    }
    return -1;
}

void Rank::Delete_Sub_Rank(int ID)
{
    Sub_Ranks.erase(Sub_Ranks.begin() + ID);
}

void Rank::Clear_Sub_Ranks()
{
    Sub_Ranks.clear();
}
