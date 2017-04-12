#ifndef VIEW_SYSTEM_H_INCLUDED
#define VIEW_SYSTEM_H_INCLUDED

#include "Database.h"
#include <iostream>

class View_System
{
public:
    Database *Current_Database;
    View_System(Database *);
    void Print_Tree(Rank &);
    void Print_Sub_Tree(Rank &);
    string Get_Rank_Type_Name(Rank_Type);
};

#endif // VIEW_SYSTEM_H_INCLUDED
