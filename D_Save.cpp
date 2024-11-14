/*
This file has functions for the saving mechanics 
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include "D_Misc.hpp"
#include "D_Map.hpp"
#include "D_Save.hpp"
#include "Player.hpp"
#include "Inventory.hpp"
using namespace std;

namespace Save{ 

    void SaveMenu(Player& P){
        int Filenum;
        int opnum;
        do{
            do{
                PrintSave();
                cout << "(1-3) Choose a save file\n"
                    << "4. Exit\n";
                cin >> Filenum;
                switch(Filenum){
                    case 1: case 2: case 3: break;
                    case 4: return;
                    default: cout << "Invalid Choice\n";
                }
            }while(Filenum<1&&Filenum>4);
            Format::PageBreak();
            PrintSave(Filenum);
            Format::PageBreak();
            do{
                cout << "What would you like to do?\n"
                    << "1. Save Game\n2. Load Game\n3. Delete Save\n4. Back\n";
                cin >> opnum;
                switch(opnum){
                    if(SaveGame(Filenum,P)==1){opnum=4;}
                    else{return;}
                    break;
                    case 2:
                    if(LoadGame(Filenum,P)==1){opnum=4;}
                    else{return;}
                    break;
                    case 3:
                        DeleteSave(Filenum);
                    break;
                    case 4: break;
                    default: cout << "Invalid Choice\n";
                }
            }while(opnum<1&&opnum>4);            
        }while(opnum==3||opnum==4);
    }

    void PrintSave(){
        Format::PageBreak();
        for (int i=1; i<=3; i++){
            PrintSave(i);
            Format::PageBreak();
        }
    }

    //
    //
    // Timestamp, P.Name, P.Level, P.Exp, P.Type
    // P.Magic, P.Loc.ID, inventory.size, inventory
    void PrintSave(const int Filenum){
        string temp;
        int tempnum;
        ifstream SaveFile;
        switch(Filenum) {
            case 1: SaveFile.open("Saves/Save1.txt"); break;
            case 2: SaveFile.open("Saves/Save2.txt"); break;
            case 3: SaveFile.open("Saves/Save3.txt"); break;
        }
        if (!SaveFile) {cout << "Save " << Filenum << ": Empty.\n"; return;}
        getline(SaveFile, temp); // Timestamp
        cout << "Save " << Filenum << "     -     Saved on: " << temp << "\n";
        getline(SaveFile, temp); // p.Name
        cout << "Name: " << temp << "  -  Level: ";
        getline(SaveFile, temp); // p.Level
        getline(SaveFile, temp); // P.Exp
        getline(SaveFile, temp); // P.Type

        cout << temp << "  -  Location: ";
        getline(SaveFile, temp); // P.Magic
        SaveFile >> tempnum; // P.Loc.ID
        switch(tempnum){
            case 1: cout << Map::City.Name; break;
            case 2: cout << Map::Temple.Name; break;
            case 3: cout << Map::Tower.Name; break;
            case 4: cout << Map::Farm.Name; break;
            case 5: cout << Map::Castle.Name; break;
        }
        cout << "\n";
        SaveFile.close();
    }
    
    //
    //
    // Timestamp, P.Name, P.Level, P.Exp, P.Type
    // P.Magic, P.Loc.ID, inventory.size, inventory
    bool SaveGame(const int Filenum, const Player& P){  
        string temp;                  
        char timestamp[20];             
        ofstream SaveFile;
        switch(Filenum){
            case 1:SaveFile.open("Saves/Save1.txt"); break;
            case 2:SaveFile.open("Saves/Save2.txt"); break;
            case 3:SaveFile.open("Saves/Save3.txt"); break;
        }
        if (!SaveFile) {cout << "Error opening file for saving.\n"; return 1;}
        time_t now = std::time(nullptr);
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
        SaveFile << timestamp << "\n"
                 << P.Name << "\n" 
                 << P.Level << "\n"
                 << P.Exp << "\n"
                 << P.Type << "\n"
                 << P.Magic << "\n"
                 << P.Loc.ID << "\n"
                 << inventoryItems.size() << "\n";
        for (int i=0; i<inventoryItems.size(); i++) {
            temp = inventoryItems[i];
            SaveFile << temp << "\n";
            temp = inventoryDescriptions[i];
            SaveFile << temp << "\n";
            temp = inventoryTraits[i];
            SaveFile << temp << "\n";
        }

        SaveFile.close();
        cout << "Game saved successfully.\n";
        return 0;
    }

    //
    //
    // Timestamp, P.Name, P.Level, P.Exp, P.Type
    // P.Magic, P.Loc.ID, inventory.size, inventory
    bool LoadGame(const int Filenum, Player& P){
        string temp;
        int size;
        string Item;
        ifstream SaveFile;
        switch(Filenum){
            case 1:SaveFile.open("Saves/Save1.txt"); break;
            case 2:SaveFile.open("Saves/Save2.txt"); break;
            case 3:SaveFile.open("Saves/Save3.txt"); break;
        }
        if (!SaveFile) {cout << "Error opening file\n"; return 1;}
        getline(SaveFile, temp); // Timestamp
        getline(SaveFile, P.Name);
        SaveFile >> P.Level; SaveFile.ignore();
        SaveFile >> P.Exp; SaveFile.ignore();
        SaveFile >> P.Type; SaveFile.ignore();
        SaveFile >> P.Magic; SaveFile.ignore();
        SaveFile >> P.Loc.ID; SaveFile.ignore();
        Map::setLoc(P);
        SaveFile >> size; // inventory.size
        SaveFile.ignore();
        inventoryItems.clear(); 
        inventoryDescriptions.clear(); 
        inventoryTraits.clear();
        for (int i = 0; i < size; i++) {
            getline(SaveFile, temp);
            inventoryItems.push_back(temp);
            getline(SaveFile, temp);
            inventoryDescriptions.push_back(temp);
            SaveFile >> size; SaveFile.ignore();
            inventoryTraits.push_back(size);
        }
        SaveFile.close();
        cout << "Game loaded successfully.\n";
        return 0;
    }
    
    bool DeleteSave(const int Filenum){
        bool fail;
        char yn;
        cout << "Are you sure you want to delete this save?\n"
             << "This operation cannot be undone\n"
             << "(y/n): ";
        cin >> yn;
        if (yn == 'y' || yn == 'Y') {
        } else { return 1;}
        switch(Filenum){
            case 1: fail=remove("Saves/Save1.txt"); break;
            case 2: fail=remove("Saves/Save2.txt"); break;
            case 3: fail=remove("Saves/Save3.txt"); break;
        }
        if(fail){cout << "No file to delete found\n";}
        else{cout << "File successfully deleted\n";}
        return fail;
    }

} // Ending namespace Save


