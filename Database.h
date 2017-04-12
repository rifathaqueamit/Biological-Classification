#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <iostream>
#include <vector>
#include "Rank.h"

using namespace std;

class Database
{
    public:
    vector<Rank> Ranks;
    Database() {}

    int Add_Rank(string,Rank_Type);
    int Add_Rank(Rank);
    void Delete_Rank(int);
    Rank& Get_Rank(int);
    int Contains(string);
    void Save_To_File(string);
    void Load_From_File(string);
};

#endif // DATABASE_H_INCLUDED
