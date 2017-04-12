#include "View_System.h"
#include "Database.h"
#include <iostream>
#include "Rank.h"
#include <stack>
#include <ostream>

View_System::View_System(Database *Data)
{
    Current_Database = Data;
}

string View_System::Get_Rank_Type_Name(Rank_Type Type)
{
    if (Type == Kingdom_Type) return "Kingdom";
    if (Type == Phylum_Type) return "Phylum";
    if (Type == Sub_Phylum_Type) return "Sub Phylum";
    if (Type == Class_Type) return "Class";
    if (Type == Sub_Class_Type) return "Sub Class";
    if (Type == Infra_Class_Type) return "Infra Class";
    if (Type == Order_Type) return "Order";
    if (Type == Sub_Order_Type) return "Sub Order";
    if (Type == Super_Family_Type) return "Super Family";
    if (Type == Family_Type) return "Family";
    if (Type == Genus_Type) return "Genus";
    if (Type == Species_Type) return "Species";
    return "Null Type";
}

void View_System::Print_Tree(Rank &Rank_Ref)
{
    stack<string> Tree_Items;
    string Text = Get_Rank_Type_Name(Rank_Ref.Type) + " : " +  Rank_Ref.Rank_Name;
    Tree_Items.push(Text);

    if (Rank_Ref.Top_Level == false) {

    Rank *Parent = Rank_Ref.Get_Parent();
    while (Parent != NULL)
    {
        Text = Get_Rank_Type_Name(Parent->Type) + " : " +  Parent->Rank_Name;
        Tree_Items.push(Text);
        if (Parent->Top_Level == false) {
        Rank *Secondary = Parent->Get_Parent();
        Parent = Secondary;
        }
        else
        {
            Parent = NULL;
        }
    }

    int degree = 0;
    string gap = "";
    while (Tree_Items.empty() == false)
    {
        cout << gap << Tree_Items.size() << ". " <<  Tree_Items.top() << endl;
        gap.insert(gap.end(), ' ');
        gap.insert(gap.end(), ' ');
        degree++;
        Tree_Items.pop();
        if (Tree_Items.empty() == false) {
                cout << gap << "|\n" << gap << "|\n" << gap << "|" << endl;
        }
    }
    }
    else
    {
        cout << "Rank does not have any parent." << endl;
    }
}

void View_System::Print_Sub_Tree(Rank &Rank_Ref)
{
    if (Rank_Ref.Sub_Ranks.size() > 0)
    {
        string Text = Get_Rank_Type_Name(Rank_Ref.Type) + " : " +  Rank_Ref.Rank_Name;
        cout << Text << endl;
        int I;
        for (I = 0; I < Rank_Ref.Sub_Ranks.size(); I++)
        {
            Text = Get_Rank_Type_Name(Rank_Ref.Sub_Ranks[I].Type) + " : " +  Rank_Ref.Sub_Ranks[I].Rank_Name;
            cout << "--|" << I+1 << ". " << Text << "     " << endl;
        }
    }
    else
    {
        cout << "Rank does not contain any children." << endl;
    }
}
