#include <iostream>
#include "Database.h"
#include "Rank.h"
#include "View_System.h"
#include "Search_System.h"

using namespace std;

int Auto_Choice_1 = 0;

void Function_Add(Rank *R, Database &Base, View_System &View, Search_System &Search)
{
    int Degree = 0;
    if (R != NULL)
    {
        Degree = R->Type;
        if (Degree == Species_Type)
        {
            int choice_1;
            int choice_1_continue = 1;
            Rank *R_2 = NULL;
            while (choice_1_continue)
            {
                cout << View.Get_Rank_Type_Name(R->Type) << " : " << R->Rank_Name << endl;
                cout << "You can not add any items here as species can not contain any children." << endl;
                cout << "What do you want to do ?" << endl;
                cout << "1. Move up" << endl;
                cout << "2. Back" << endl;
                cout << "Enter your choice : " << endl;
                cin >> choice_1;
                switch (choice_1)
                {
                case 1:
                    R_2 = R->Get_Parent();
                    R = R_2;
                    choice_1_continue = 0;
                    break;
                case 2:
                    choice_1_continue = 0;
                    return;
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
                }
            }
            return;
        }
    }

    cout << "Adding elements to the database....." << endl;
    int Continue_Adding = 1;
    int I;
    int Rank_Name_Continue;
    int Rank_Index_Continue;

    while (Continue_Adding)
    {
        int I;
        string New_Rank;
        int New_Rank_Index;
Start_From_First:
        Rank_Name_Continue = 1;

        if (R != NULL)
        {
            Degree = R->Type;
            if (Degree == Species_Type)
            {
                int choice_1;
                int choice_1_continue = 1;
                Rank *R_2 = NULL;
                while (choice_1_continue)
                {
                    cout << View.Get_Rank_Type_Name(R->Type) << " : " << R->Rank_Name << endl;
                    cout << "You can not add any items here as species can not contain any children." << endl;
                    cout << "What do you want to do ?" << endl;
                    cout << "1. Move up" << endl;
                    cout << "2. Back" << endl;
                    cout << "Enter your choice : " << endl;
                    cin >> choice_1;
                    switch (choice_1)
                    {
                    case 1:
                        R_2 = R->Get_Parent();
                        R = R_2;
                        choice_1_continue = 0;
                        break;
                    case 2:
                        choice_1_continue = 0;
                        Continue_Adding = 0;
                        return;
                        break;
                    default:
                        cout << "Invalid choice. Try again." << endl;
                    }
                }
            }
        }

        while (Rank_Name_Continue)
        {

            cout << "Current : ";
            if (R == NULL) cout << "Base" << endl;
            else cout << View.Get_Rank_Type_Name(R->Type) << " : " << R->Rank_Name << endl;

            cout << "What do you want to do ?" << endl;
            cout << "1. Add" << endl;
            cout << "2. Move up" << endl;
            cout << "3. Back" << endl;
            cout << "Enter your choice : " << endl;
            int choice_2;
            cin >> choice_2;

            switch (choice_2)
            {
            case 1:
                break;
            case 2:
                if (R == NULL)
                {
                    cout << "Can not move up. You are in Base." << endl;
                    goto Start_From_First;
                }
                else
                {
                    if (R->Top_Level == false)
                    {
                        Rank *Parent = R->Get_Parent();
                        R = Parent;
                        goto Start_From_First;
                    }
                    else
                    {
                        cout << "Can not move up. You are in Base." << endl;
                        R = NULL;
                        goto Start_From_First;
                    }
                }
                break;
            case 3:
                return;
                break;
            default:
                cout << "Choice is not right. Try again." << endl;
                goto Start_From_First;
            }
Start_From_Entering_Name:
            if (R == NULL)
                cout << "New rank name : " << endl;
            else
                cout << "New sub rank name : " << endl;


            cin >> New_Rank;

            Rank *Found_Rank = NULL;
            //if (R == NULL)
            //{
            Found_Rank = Search.Search_For_Rank(New_Rank);
            if (Found_Rank != NULL)
            {
                cout << "Name already exists in database. What do you want to do ?" << endl;
                cout << "1. Move to " << New_Rank << endl;
                cout << "2. Try another name" << endl;
                cout << "Enter your choice : " << endl;
                int choice_3;
                cin >> choice_3;
                switch (choice_3)
                {
                case 1:
                    R = Found_Rank;
                    goto Start_From_First;
                    break;
                case 2:
                    goto Start_From_Entering_Name;
                    break;
                default:
                    cout << "Invalid choice. Try entering the name again." << endl;
                    goto Start_From_Entering_Name;
                }
            }
            else
            {
                Rank_Name_Continue = 0;
            }

        }

        Rank_Index_Continue = 1;

        while (Rank_Index_Continue)
        {
            for (I = 1; I <= 12; I++)
                cout << I << ". " << View.Get_Rank_Type_Name((Rank_Type)I) << endl;

            cout << "Enter rank type (enter the index) : ";
            cin >> New_Rank_Index;
            if (New_Rank_Index >= 1 && New_Rank_Index <= 12)
            {
                Rank_Index_Continue = 0;
            }
            else
            {
                cout << "Invalid index. Try again." << endl;
            }
        }


        if (R == NULL)
        {
            int New_Rank_ID = Base.Add_Rank(New_Rank, (Rank_Type)New_Rank_Index);
            R = &Base.Ranks[New_Rank_ID];
        }
        else
        {
            int New_Rank_ID = R->Add_Sub_Rank(New_Rank, (Rank_Type)New_Rank_Index);
            R = &R->Sub_Ranks[New_Rank_ID];
        }

        cout << "Element successfully added." << endl;
    }
}

void Function_Browse(Rank *R, View_System &View,Database &Base, Search_System &Search, bool Add_Delete = false)
{
    int second_choice_continue = 1;
    while (second_choice_continue)
    {

        cout << "Rank Name : " << R->Rank_Name << endl;
        cout << "Rank Type : " << View.Get_Rank_Type_Name(R->Type) << endl;
        if (R->Top_Level == true)
        {
            cout << "Rank has parent : No" << endl;
        }
        else
        {
            cout << "Rank has parent : Yes" << endl;
        }

        cout << "What do you want to do ?" << endl;
        cout << "1. Watch root tree" << endl;
        cout << "2. Watch sub tree" << endl;
        cout << "3. Goto parent" << endl;

        if (Add_Delete == true)
        {
            cout << "4. Delete all sub items" << endl;
            cout << "5. Delete it" << endl;
            cout << "6. Back" << endl;
        }
        else
            cout << "4. Back" << endl;

        int second_choice = 0;
        int sub_tree_continue_choice;
        int top_tree_continue_choice;
        int Delete_Choice;
        cout << "Enter your choice : " << endl;
        cin >> second_choice;
        switch (second_choice)
        {
        case 1:
            top_tree_continue_choice = 1;
            while(top_tree_continue_choice)
            {
                cout << "---------------------------" << endl;
                View.Print_Tree(*R);
                cout << "---------------------------" << endl;

                top_tree_continue_choice = 1;
                if (R->Top_Level == false)
                {
                    cout << "Enter index to go to that Rank. Enter 0 to back." << endl;
                    int rank_choice_1 = 0;
                    cin >> rank_choice_1;

                    if (rank_choice_1 != 0)
                    {
                        Rank *R_New = Search.Search_For_Indexed_Upper_Rank(R, rank_choice_1-1);

                        if (R_New != NULL)
                        {
                            R = R_New;

                            top_tree_continue_choice = 0;
                        }
                        else
                        {
                            cout << "Upper index not found." << endl;
                        }
                    }
                    else
                    {
                        top_tree_continue_choice = 0;
                    }
                }
                else
                {
                    top_tree_continue_choice = 0;
                }
            }
            break;
        case 2:

            sub_tree_continue_choice = 1;
            while (sub_tree_continue_choice)
            {
                cout << "---------------------------" << endl;
                View.Print_Sub_Tree(*R);
                cout << "---------------------------" << endl;

                if (R->Sub_Ranks.size() > 0)
                {
                    cout << "Enter index to go to that Rank. Enter 0 to back." << endl;
                    int rank_choice_2 = 0;
                    cin >> rank_choice_2;
                    if (rank_choice_2 != 0)
                    {
                        Rank *R_New = Search.Search_For_Indexed_Sub_Rank(R, rank_choice_2-1);

                        if (R_New != NULL)
                        {
                            R = R_New;

                            sub_tree_continue_choice = 0;
                        }
                        else
                        {
                            cout << "Sub index not found." << endl;
                        }
                    }
                    else
                    {
                        sub_tree_continue_choice = 0;
                    }
                }
                else
                {
                    sub_tree_continue_choice = 0;
                }
            }
            break;
        case 3:
            if (R->Top_Level == true)
            {
                cout << "Rank " << R->Rank_Name << " does not have a parent." << endl;
            }
            else
            {
                Rank *Parent_Rank = R->Get_Parent();
                R = Parent_Rank;
            }
            break;
        case 4:
            ////Code for Delete
            if (Add_Delete == true)
            {
                cout << endl << "Do you really want to delete sub items of this Rank ?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;

                cin >> Delete_Choice;
                switch (Delete_Choice)
                {
                case 1:
                    R->Clear_Sub_Ranks();
                    cout << "-----------------------------------------" << endl;
                    cout << "Sub ranks deleted" << endl;
                    cout << "-----------------------------------------" << endl;
                    break;
                case 2:

                    break;
                default:
                    cout << "Invalid choice." << endl;
                }
            }
            else
            {
                second_choice_continue = 0;
            }
            break;
        case 5:
            //Delete it
            cout << endl << "Do you really want to delete sub items of this Rank ?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;

            cin >> Delete_Choice;
            switch (Delete_Choice)
            {
            case 1:
                if (R->Top_Level == false)
                {
                    Rank *Temp = R;
                    Rank *Parent_Rank = R->Get_Parent();
                    R = Parent_Rank;
                    R->Delete_Sub_Rank(R->Contains(Temp->Rank_Name));
                    cout << "-----------------------------------------" << endl;
                    cout << "Rank deleted" << endl;
                    cout << "-----------------------------------------" << endl;
                }
                else
                {
                    Rank *Temp = R;
                    int ID = Base.Contains(Temp->Rank_Name);
                    Temp == NULL;
                    Base.Delete_Rank(ID);
                    second_choice_continue = 0;
                    R == NULL;
                    Auto_Choice_1 = 1;
                    cout << "-----------------------------------------" << endl;
                    cout << "Rank deleted" << endl;
                    cout << "-----------------------------------------" << endl;
                }
                break;
            case 2:
                break;
            default:
                cout << "Invalid choice." << endl;
            }
            break;
        case 6:
            second_choice_continue = 0;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
}

void Function_Delete(Rank *R, Database &Base, View_System &View, Search_System &Search)
{
    if (R == NULL)
    {
        int Delete_Continue;
        int Search_Continue;
        int Delete_choice;
        int Browse_Continue;
        string Text;
        Rank *Browsing_Rank;

        Delete_Continue = 1;

        while (Delete_Continue)
        {
            cout << endl << "Select item to delete : " << endl;
            cout << "1. Search by taxonomy" << endl;
            cout << "2. Browse from root" << endl;
            cout << "3. Back" << endl;
            cout << "Enter your selection : " << endl;

            cin >> Delete_choice;

            switch (Delete_choice)
            {
            case 1:

                Search_Continue = 1;

                while (Search_Continue)
                {

                    string inp = "";
                    cout << "Enter the term to search (enter 0 to back): " << endl;
                    cin >> inp;
                    if (inp == "0")
                    {
                        Search_Continue = 0;
                        break;
                    }

                    R = Search.Search_For_Rank(inp);
                    if (R != NULL)
                    {
                        cout << "Rank found for the term " << inp << "." << endl;
                        Function_Browse(R, View, Base, Search, true);

                        if (Auto_Choice_1 == 1)
                        {
                            goto Start_Again_1;
                            break;
                        }
                    }
                    else
                    {
                        cout << "Not found!" << endl;
                    }

                }

                break;
            case 2:

Start_Again_1:
                int I;

                if (Base.Ranks.size() > 0)
                {
                    Browse_Continue = 1;
                    while (Browse_Continue)
                    {
                        cout << "------------------------------" << endl;
                        for (I = 0; I < Base.Ranks.size(); I++)
                        {
                            Text = View.Get_Rank_Type_Name(Base.Ranks[I].Type) + " : " + Base.Ranks[I].Rank_Name;
                            cout << I+1 << ". " << Text << endl;
                        }
                        cout << "-----------------------------" << endl;
                        cout << "Enter index to browse. 0 to back to main menu" << endl;
                        int Browse_choice;
                        cin >> Browse_choice;
                        switch (Browse_choice)
                        {
                        case 0:
                            Browse_Continue = 0;
                            R = NULL;
                            break;
                        default:
                            if (Browse_choice > 0 && Browse_choice - 1 < Base.Ranks.size())
                            {
                                int ID = Browse_choice - 1;
                                R = &Base.Ranks[ID];
                                Browse_Continue = 0;
                            }
                            else
                            {
                                cout << "Invalid choice. Try again." << endl;
                            }
                        }

                    }

                }
                else
                {
                    cout << "No database is found." << endl;
                }
                if (Auto_Choice_1 == 1)
                {
                   Auto_Choice_1 = 0;
                }
                else
                {
                if (R != NULL)
                {
                    Function_Browse(R, View, Base, Search,true);
                    if (R->Top_Level == true)
                    {
                        goto Start_Again_1;
                    }
                }
                }

                break;
            case 3:
                Delete_Continue = 0;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
            }

        }
    }
}

int main()
{
    Database Base;

    //Default database : Human
    /*
     Base.Add_Rank(Kingdom("Animalia"));
     Rank &Animalia = Base.Get_Rank(0);

     Animalia.Add_Sub_Rank(Phylum("Chordata"));
     Rank &Chordata = Animalia.Get_Sub_Rank(0);

     Chordata.Add_Sub_Rank("Vertebrata", Sub_Phylum_Type);
     Rank &Vertebrata = Chordata.Get_Sub_Rank(0);

     Vertebrata.Add_Sub_Rank("Mammalia", Class_Type);
     Rank &Mammalia = Vertebrata.Get_Sub_Rank(0);

     Mammalia.Add_Sub_Rank("Theria", Sub_Class_Type);
     Rank &Theria = Mammalia.Get_Sub_Rank(0);

     Theria.Add_Sub_Rank("Eutheria", Infra_Class_Type);
     Rank &Eutheria = Theria.Get_Sub_Rank(0);

     Eutheria.Add_Sub_Rank("Primates", Order_Type);
     Rank &Order = Eutheria.Get_Sub_Rank(0);

     Order.Add_Sub_Rank("Antropoidea", Sub_Order_Type);
     Rank &Antropoidea = Order.Get_Sub_Rank(0);

     Antropoidea.Add_Sub_Rank("Hominoidea", Super_Family_Type);
     Rank &Hominoidea = Antropoidea.Get_Sub_Rank(0);

     Hominoidea.Add_Sub_Rank("Hominidae", Family_Type);
     Rank &Hominidae = Hominoidea.Get_Sub_Rank(0);

     Hominidae.Add_Sub_Rank("Homo", Genus_Type);
     Rank &Homo = Hominidae.Get_Sub_Rank(0);

     Homo.Add_Sub_Rank("sapiens", Species_Type);
     Rank &sapiens = Homo.Get_Sub_Rank(0);
    */

    cout << "Animals Classification System 0.2" << endl;

    Base.Load_From_File("Data.acd");
    View_System View(&Base);
    Search_System Search(&Base);

    int running = 1;
    int search_continue;
    while (running)
    {

        cout << "1. Search" << endl;
        cout << "2. Browse" << endl;
        cout << "3. Add to Database" << endl;
        cout << "4. Remove from Database" << endl;
        cout << "5. Exit" << endl;

        cout << endl << "Enter your choice : " << endl;
        int choice;
        cin >> choice;

        string Text = "";
        int browse_choice_continue;
        Rank *Browsing_Rank;
        switch (choice)
        {
        case 1:
            search_continue = 1;

            while (search_continue)
            {
                string inp = "";

                cout << "Enter the term to search (enter 0 to back): " << endl;
                cin >> inp;

                if (inp == "0")
                {
                    search_continue = 0;
                    break;
                }

                Rank *R;
                R = Search.Search_For_Rank(inp);

                if (R != NULL)
                {
                    cout << "Rank found for the term " << inp << "." << endl;

                    Function_Browse(R, View, Base, Search);
                }
                else
                {
                    cout << "Not found!" << endl;
                }

            }
            break;
        case 2:
Start_Again_1:
            Browsing_Rank = NULL;
            int I;
            if (Browsing_Rank == NULL)
            {
                if (Base.Ranks.size() > 0)
                {
                    browse_choice_continue = 1;
                    while (browse_choice_continue)
                    {
                        cout << "------------------------------" << endl;
                        for (I = 0; I < Base.Ranks.size(); I++)
                        {
                            Text = View.Get_Rank_Type_Name(Base.Ranks[I].Type) + " : " + Base.Ranks[I].Rank_Name;
                            cout << I+1 << ". " << Text << endl;
                        }
                        cout << "-----------------------------" << endl;
                        cout << "Enter index to browse. 0 to back to main menu" << endl;
                        int browse_choice;
                        cin >> browse_choice;
                        switch (browse_choice)
                        {
                        case 0:
                            browse_choice_continue = 0;
                            break;
                        default:
                            if (browse_choice > 0 && browse_choice - 1 < Base.Ranks.size())
                            {
                                int ID = browse_choice - 1;
                                Browsing_Rank = &Base.Ranks[ID];
                                browse_choice_continue = 0;
                            }
                            else
                            {
                                cout << "Invalid choice. Try again." << endl;
                            }
                        }

                    }

                }
                else
                {
                    cout << "No database is found." << endl;
                }

                if (Browsing_Rank != NULL)
                {
                    Function_Browse(Browsing_Rank, View, Base, Search);
                    if (Browsing_Rank->Top_Level == true)
                    {
                        goto Start_Again_1;
                    }
                }

            }
            else
            {
                Function_Browse(Browsing_Rank, View, Base, Search);
                cout << endl;
            }

            break;
        case 3:

            Function_Add(NULL, Base, View,Search);

            break;
        case 4:

            Function_Delete(NULL, Base, View,Search);
            break;
        case 5:
            running = 0;
            Base.Save_To_File("Data.acd");
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }


    return 0;
}

