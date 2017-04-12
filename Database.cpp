#include "Database.h"
#include "Rank.h"
#include <iostream>
#include <fstream>

int Database::Add_Rank(string Name, Rank_Type Type)
{
    Rank New_Rank(Name, Type, true);
    Ranks.push_back(New_Rank);
    return Ranks.size() - 1;
}

int Database::Add_Rank(Rank Rank_Object)
{
    Ranks.push_back(Rank_Object);
    return Ranks.size() - 1;
}

Rank& Database::Get_Rank(int ID)
{
    return Ranks[ID];
}

void Write_Sub_Ranks(ofstream &File_To_Write,Rank &Top_Level)
{
    int I;
    File_To_Write << Top_Level.Sub_Ranks.size() << endl;
    for (I = 0; I < Top_Level.Sub_Ranks.size(); I++)
    {
        File_To_Write << Top_Level.Sub_Ranks[I].Rank_Name << endl;
        File_To_Write << (int)Top_Level.Sub_Ranks[I].Type << endl;
        Write_Sub_Ranks(File_To_Write, Top_Level.Sub_Ranks[I]);
    }
}

void Read_Sub_Ranks(ifstream &File_To_Read, Rank *Top_Level)
{
    int Ranks_Count;
    string Rank_Name;
    int Type;
    File_To_Read >> Ranks_Count;
    if (Ranks_Count > 0) {
    int I;
    for (I = 0; I < Ranks_Count; I++)
    {
        File_To_Read >> Rank_Name;
        File_To_Read >> Type;
        int Sub_Rank_ID = Top_Level->Add_Sub_Rank(Rank_Name, (Rank_Type)Type);
        Read_Sub_Ranks(File_To_Read, &Top_Level->Sub_Ranks[Sub_Rank_ID]);
    }
    }
}

void Correct_Sub_Parents(Rank *Current_Rank)
{
    int I;
    for (I = 0; I < Current_Rank->Sub_Ranks.size(); I++)
    {
        Current_Rank->Sub_Ranks[I].Parent = Current_Rank;
        Correct_Sub_Parents(&Current_Rank->Sub_Ranks[I]);
    }
}

void Database::Load_From_File(string File_Name)
{
    Ranks.clear();
    ifstream File_To_Read;
    File_To_Read.open(File_Name.c_str(), ios::in);
    if (File_To_Read.is_open() == true)
    {
        int Ranks_Count;
        string Rank_Name;
        int Type;
        File_To_Read >> Ranks_Count;
        int I;
        for (I = 0; I < Ranks_Count; I++)
        {
            File_To_Read >> Rank_Name;
            File_To_Read >> Type;

            int Rank_ID = Add_Rank(Rank_Name, (Rank_Type)Type);
            Read_Sub_Ranks(File_To_Read, &Ranks[Rank_ID]);
        }
    }
    else
    {
        cout << "Could not open data file." << endl;
    }
    File_To_Read.close();

    //Rearrange the parents
    int I;
    for (I = 0; I < Ranks.size(); I++)
    {
        Ranks[I].Parent = NULL;
        Correct_Sub_Parents(&Ranks[I]);
    }
}


void Database::Save_To_File(string File_Name)
{
    ////////////////////////////////
    //File Format : acd
    ////////////////////////////////
    ////////////////////////////////
    //(Number of Ranks)(#1.Rank_Name)(#1.Rank_Type)
    //(#1.Number of sub Ranks)(#1.#1.Sub Rank Name)(#1.#1.Sub Rank Type).....
    /////////////////////////////////
    ofstream File_To_Write;
    File_To_Write.open(File_Name.c_str(), ios::out | ios::trunc);
    if (File_To_Write.is_open() == false)
    {
        cout << "Could not saved to file." << endl;
        return;
    }
    File_To_Write << Ranks.size() << endl;
    int I;
    for (I = 0; I < Ranks.size(); I++)
    {
        File_To_Write << Ranks[I].Rank_Name << endl;
        File_To_Write << (int)Ranks[I].Type << endl;
        Write_Sub_Ranks(File_To_Write, Ranks[I]);
    }
    File_To_Write.close();
}


int Database::Contains(string Rank_Name)
{
    int I;
    for (I = 0; I < Ranks.size(); I++)
    {
        if (Ranks[I].Rank_Name == Rank_Name)
        {
            return I;
        }
    }
    return -1;
}

void Database::Delete_Rank(int ID)
{
    Ranks.erase(Ranks.begin() + ID);
}
