#include "Search_System.h"
#include "Database.h"
#include "Rank.h"

Search_System::Search_System(Database *Data)
{
    Base = Data;
}

Rank* Search_For_Sub_Rank(Rank *Top_Rank, string Name)
{
    Rank *R = NULL;
    int I;
    for (I = 0; I < Top_Rank->Sub_Ranks.size(); I++)
    {
        if (Top_Rank->Sub_Ranks[I].Rank_Name == Name)
        {
            R = &Top_Rank->Sub_Ranks[I];
            break;
        }
        Rank *R2;
        R2 = Search_For_Sub_Rank(&Top_Rank->Sub_Ranks[I], Name);
        if (R2 != NULL)
        {
            R = R2;
            break;
        }
    }
    return R;
}

Rank* Search_System::Search_For_Rank(string Name)
{
    Rank *R = NULL;
    int I;
    for (I = 0; I < Base->Ranks.size(); I++)
    {
        if (Base->Ranks[I].Rank_Name == Name)
        {
            R = &Base->Ranks[I];
            break;
        }
        Rank *R2;
        R2 = Search_For_Sub_Rank(&Base->Ranks[I], Name);
        if (R2 != NULL)
        {
            R = R2;
            break;
        }
    }
    return R;
}

Rank* Search_System::Search_For_Indexed_Sub_Rank(Rank* Rank_Object, int Index)
{
    if (Rank_Object->Sub_Ranks.size() > 0)
    {
        if (Index >= 0 && Index < Rank_Object->Sub_Ranks.size())
        {
            return &Rank_Object->Sub_Ranks[Index];
        }
    }
    else
        return NULL;
    return NULL;
}

Rank* Search_System::Search_For_Indexed_Upper_Rank(Rank* Rank_Object, int Degree)
{
    if (Rank_Object->Top_Level == false)
    {
        int Deg = Degree;
        if (Deg > 0) {
        Rank *R = Rank_Object->Get_Parent();
        Deg--;
        while (Deg != 0)
        {
            if (R->Top_Level == false) {
            R = R->Get_Parent();
            Deg--;
            }
            else
            {
                return NULL;
            }
        }
        return R;
        }
        else
            return Rank_Object;
    }
    return NULL;
}
