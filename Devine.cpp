/*
This file has functions for the map, 
leveling, and save mechanics. 
*/

#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <ctime>
#include <string>
#include <vector>
#include"Devine.hpp"
using namespace std;

namespace Map{ 

    Location City(1,"The City of Kronos",true,true);
    Location Temple(2,"Temple of Zeus",false,true);
    Location Tower(3,"Hestia's Tower",false,false);
    Location Farm(4,"Pagasus Farm",false,true);
    Location Castle(5,"Hades' Castle",false,false);

    Location PlayerLoc = City;


    void WorldMap(){
        ifstream Map;
        string MapFeed;
        if (PlayerLoc.ID==City.ID || PlayerLoc.ID==Temple.ID || PlayerLoc.ID==Tower.ID){        
            Map.open("Maps/Map1.txt");
            while (getline(Map, MapFeed)) {
                cout << MapFeed << "\n";
            }
        }else if(PlayerLoc.ID==Farm.ID || PlayerLoc.ID==Castle.ID){
            Map.open("Maps/Map2.txt");
            while (getline(Map, MapFeed)) {
                cout << MapFeed << "\n";
            }
        }
        Map.close();
        cout << "You are currently at " << PlayerLoc.Name << "\n";
    }


    void WorldMapTravel(vector<string>& inventory){
        int Destination;
        char yn;
        WorldMap();
        switch(PlayerLoc.ID){
            case 1: // City of Kronos
                cout << "Where would you like to go?\n"
                    << "1. " << Temple.Name << "\n"
                    << "2. " << Tower.Name << "\n";
                cin >> Destination;
                Format::PageBreak();
                switch(Destination){
                    case 1: // Temple of Zeus
                        if(!Adventure(5,5,"NE","SW",inventory)){return;}
                        RandomWorldEvent(inventory);
                        if(!Adventure(5,5,"NE","S",inventory)){return;}
                        PlayerLoc=Temple;
                        cout << "You have arrived at " << PlayerLoc.Name;
                    break;
                    case 2: // Hestia's Tower
                        if(!Adventure(5,5,"NW","SE",inventory)){return;}
                        RandomWorldEvent(inventory);
                        if(!Adventure(5,5,"NW","S",inventory)){return;}
                        PlayerLoc=Tower;
                        cout << "You have arrived at " << PlayerLoc.Name;
                    break;
                    default: cout << "Invalid Choice\n"; return;
                }
            break;
            case 2: // Temple of Zeus
                cout << "Where would you like to go?\n"
                    << "1. " << City.Name << "\n"
                    << "2. " << Tower.Name << "\n";
                cin >> Destination;
                Format::PageBreak();
                switch(Destination){
                    case 1: // City of Kronos
                        if(!Adventure(5,5,"S","NE",inventory)){return;}
                        RandomWorldEvent(inventory);
                        if(!Adventure(5,5,"SW","NE",inventory)){return;}
                        PlayerLoc=City;
                        cout << "You have arrived at " << PlayerLoc.Name;
                    break;
                    case 2: // Hestia's Tower
                        if(!Adventure(8,3,"W","E",inventory)){return;}
                        RandomWorldEvent(inventory);
                        switch(Adventure(8,8,"W","E","S",inventory)){
                            case 0: return;
                            case 1: PlayerLoc=Tower;
                                cout << "You have arrived at " << PlayerLoc.Name; return;
                            case 2: PlayerLoc=Farm;
                                cout << "You have arrived at " << PlayerLoc.Name; return;
                        }
                    break;
                    default: cout << "Invalid Choice\n"; return;
                }
            break;
            case 3: // Hestia's Tower
                cout << "Where would you like to go?\n"
                    << "1. " << City.Name << "\n"
                    << "2. " << Temple.Name << "\n";
                cin >> Destination;
                Format::PageBreak();
                switch(Destination){
                    case 1: // City of Kronos
                        if(!Adventure(5,5,"S","NW",inventory)){return;}
                        RandomWorldEvent(inventory);
                        if(!Adventure(5,5,"SE","NW",inventory)){return;}
                        PlayerLoc=City;
                        cout << "You have arrived at " << PlayerLoc.Name;
                    break;
                    case 2: // Temple of Zeus
                        switch(Adventure(8,8,"E","W","S",inventory)){
                            case 0: return;
                            case 2: PlayerLoc=Farm; 
                                cout << "You have arrived at " << PlayerLoc.Name; return;
                        }
                        RandomWorldEvent(inventory);
                        if(!Adventure(8,3,"E","W",inventory)){return;}
                        PlayerLoc=Temple;
                        cout << "You have arrived at " << PlayerLoc.Name;
                    break;
                    default: cout << "Invalid Choice\n"; return;
                }

            break;
            case 4: // Pagasus Farm
                cout << "Where would you like to go?\n"
                    << "1. " << Temple.Name << "\n"
                    << "2. " << Tower.Name << "\n"
                    << "3. " << Castle.Name << "\n";
                cin >> Destination;
                Format::PageBreak();
                switch(Destination){
                    case 1: // Temple of Zeus
                        if(!Adventure(8,8,"S","W",inventory)){return;}
                        RandomWorldEvent(inventory);
                        if(!Adventure(8,3,"E","W",inventory)){return;}
                        PlayerLoc=Temple;
                        cout << "You have arrived at " << PlayerLoc.Name;
                    break;
                    case 2: // Hestia's Tower
                        if(!Adventure(8,8,"S","E",inventory)){return;}
                        PlayerLoc=Tower;
                        cout << "You have arrived at " << PlayerLoc.Name;
                    break;
                    case 3: // Hades' Castle
                        if(!Adventure(10,10,"E","S",inventory)){return;}
                        RandomWorldEvent(inventory);
                        if(!Adventure(6,16,"N","S",inventory)){return;}
                        PlayerLoc=Castle;
                        cout << "You have arrived at " << PlayerLoc.Name;
                    break;
                    default: cout << "Invalid Choice\n"; return;
                }         
            break;
            case 5: // Hades' Castle
                cout << "Return to the farm? (y/n): ";
                cin >> yn;
                if(yn != 'y'||yn != 'Y'){return;}
                Format::PageBreak();
                //Pagasus Farm
                if(!Adventure(5,15,"S","N",inventory)){return;}
                RandomWorldEvent(inventory);
                if(!Adventure(10,10,"S","E",inventory)){return;}
                PlayerLoc=Farm;
                cout << "You have arrived at " << PlayerLoc.Name;
            break;
        }
    }


    bool Adventure(const int Width, const int Height, const string Spawn, const string Dest, vector<string>& inventory){
        srand(time(0));
        vector<vector<int>> Map(Height, vector<int>(Width));
        vector<vector<bool>> Fog(Height, vector<bool>(Width, true));
        int PlayerSpace[2];
        int D;
        bool moved=false;
        char yn;
        int input;

        auto PrintMap = [](const int height, const int width, const vector<vector<int>>& map, const vector<vector<bool>>& fog, const int playerspace[2]) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (playerspace[0]==i && playerspace[1]==j){
                        cout << " P ";
                    }else if (!fog[i][j]) {
                        switch (map[i][j]) {
                            case 0: case 1: case 2: case 3:
                                cout << "[ ]";
                            break;
                            case 4: case 5: case 6: case 7:
                                cout << "[M]";
                            break;
                            case 8: cout << "[E]"; break;
                            case 9: cout << "[I]"; break;
                            case 10: cout << "[R]"; break;
                            case 11: cout << " ^ "; break;
                            case 12: cout << " < "; break;
                            case 13: cout << " > "; break;
                            case 14: cout << " v "; break;
                        }
                    }else{cout << "[~]";}
                    cout << "  ";
                }
                cout << "\n";
            }
        };

        auto Half = [](const int length){
            if(length%2==0){return length/2+rand()%2;
            }else{return length/2;};
        };

        auto FogClear = [](const int height, const int width,const int PlayerSpace[2],vector<vector<bool>>& fog){
            for (int i=PlayerSpace[0]-1; i<=PlayerSpace[0]+1; i++){
                for (int j=PlayerSpace[1]-1; j<=PlayerSpace[1]+1; j++){
                    if (i>=0 && i<height && j>=0 && j<width){
                        fog[i][j]=false;
                    }
                }
            }
        };

        for (int i=0; i<Height; i++){
            for (int j=0; j<Width; j++){
                Map[i][j]=rand()%10;
            }
        };

        if(Dest=="N"){PlayerSpace[0]=0;PlayerSpace[1]=Half(Width)+(rand()%3-1);D=11;
        }else if(Dest=="NE"){PlayerSpace[0]=0;PlayerSpace[1]=Width-rand()%2-1;D=11;
        }else if(Dest=="NW"){PlayerSpace[0]=0;PlayerSpace[1]=rand()%2;D=11;
        }else if(Dest=="E"){PlayerSpace[0]=Half(Height)+(rand()%3-1);PlayerSpace[1]=Width-1;D=13;
        }else if(Dest=="W"){PlayerSpace[0]=Half(Height)+(rand()%3-1);PlayerSpace[1]=0;D=12;
        }else if(Dest=="S"){PlayerSpace[0]=Height-1;PlayerSpace[1]=Half(Width)+(rand()%3-1);D=14;
        }else if(Dest=="SE"){PlayerSpace[0]=Height-1;PlayerSpace[1]=Width-rand()%2-1;D=14;
        }else if(Dest=="SW"){PlayerSpace[0]=Height-1;PlayerSpace[1]=rand()%2;D=14;}

        for (int i=PlayerSpace[0]-1; i<=PlayerSpace[0]+1; i++){
            for (int j=PlayerSpace[1]-1; j<=PlayerSpace[1]+1; j++){
                if (i>=0 && i<Height && j>=0 && j<Width){
                    Map[i][j]=D;
                }
            }
        };
        
        
        if(Spawn=="N"){PlayerSpace[0]=0;PlayerSpace[1]=Half(Width)+(rand()%3-1);
        }else if(Spawn=="NE"){PlayerSpace[0]=0;PlayerSpace[1]=Width-rand()%2-1;
        }else if(Spawn=="NW"){PlayerSpace[0]=0;PlayerSpace[1]=rand()%2;
        }else if(Spawn=="E"){PlayerSpace[0]=Half(Height)+(rand()%3-1);PlayerSpace[1]=Width-1;
        }else if(Spawn=="W"){PlayerSpace[0]=Half(Height)+(rand()%3-1);PlayerSpace[1]=0;
        }else if(Spawn=="S"){PlayerSpace[0]=Height-1;PlayerSpace[1]=Half(Width)+(rand()%3-1);
        }else if(Spawn=="SE"){PlayerSpace[0]=Height-1;PlayerSpace[1]=Width-rand()%2-1;
        }else if(Spawn=="SW"){PlayerSpace[0]=Height-1;PlayerSpace[1]=rand()%2;}

        for (int i=PlayerSpace[0]-1; i<=PlayerSpace[0]+1; i++){
            for (int j=PlayerSpace[1]-1; j<=PlayerSpace[1]+1; j++){
                if (i>=0 && i<Height && j>=0 && j<Width){
                    Map[i][j]=0;
                }
            }
        };

        Map[PlayerSpace[0]][PlayerSpace[1]]=10;

        do{

            do{
                moved=false;
                FogClear(Height,Width,PlayerSpace,Fog);
                PrintMap(Height,Width,Map,Fog,PlayerSpace);
                cout << "Where would you like to move\n"
                    << "          1. Up\n"
                    << "2. Left                  3. Right\n"
                    << "          4. Down                       ";
                cin >> input;
                switch(input){
                    case 1: // UP
                        if (PlayerSpace[0]==0){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[0]--; moved=true;}
                        break;
                    case 2: // Left
                        if (PlayerSpace[1]==0){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[1]--; moved=true;}
                        break;
                    case 3: // Right
                        if (PlayerSpace[1]==Width-1){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[1]++; moved=true;}
                        break;
                    case 4: // Down
                        if (PlayerSpace[0]==Height-1){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[0]++; moved=true;}
                        break;
                    default: cout << "Invalid Input\n";
                }
            }while(!moved);
            Format::PageBreak();
            switch(Map[PlayerSpace[0]][PlayerSpace[1]]){       
                case 4: case 5: case 6: case 7:
                    MonsterEvent();
                    Format::Pause(); Format::PageBreak();
                    break;
                case 8:  
                    RandomMapEvent(inventory); 
                    break;
                case 9: 
                    cout << "You open a chest to find\n"
                         << "...\n";
                    if (rand()%10<9){
                        cout << "It was a Mimic!\n"
                             << "You loose health\n";
                    }else{ItemEvent(inventory);}
                    Format::Pause(); Format::PageBreak();
                    break;
                case 10:
                    cout << "Do you want to give up and retreat? (y/n): "; 
                    cin >> yn;
                    if (yn == 'y' || yn == 'Y') {return false;}
                    Format::PageBreak();
                    break;
                case 11: case 12: case 13: case 14: 
                    cout << "Do you want to continue forward? (y/n): "; 
                    cin >> yn;
                    if (yn == 'y' || yn == 'Y') {return true;}
                    Format::PageBreak();
            }
            if(Map[PlayerSpace[0]][PlayerSpace[1]]<10){
                Map[PlayerSpace[0]][PlayerSpace[1]]=0;
            }
        }while(moved);
    return 0;
    }



    /*-------------------------------------------------------------------------------------*/
    /*-------------------------------------------------------------------------------------*/
    /*-------------------------------------------------------------------------------------*/



    int Adventure(const int Width, const int Height, const string Spawn, const string Dest,const string Extra,vector<string>& inventory){
        srand(time(0));
        vector<vector<int>> Map(Height, vector<int>(Width));
        vector<vector<bool>> Fog(Height, vector<bool>(Width, true));
        int PlayerSpace[2];
        int D;
        bool moved;
        char yn;
        int input;

        auto PrintMap = [](const int height, const int width, const vector<vector<int>>& map, const vector<vector<bool>>& fog, const int playerspace[2]) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (playerspace[0]==i && playerspace[1]==j){
                        cout << " P ";
                    }else if (!fog[i][j]) {
                        switch (map[i][j]) {
                            case 0: case 1: case 2: case 3:
                                cout << "[ ]";
                            break;
                            case 4: case 5: case 6: case 7:
                                cout << "[M]";
                            break;
                            case 8: cout << "[E]"; break;
                            case 9: cout << "[I]"; break;
                            case 10: cout << "[R]"; break;
                            case 11: cout << " ^ "; break;
                            case 12: cout << " < "; break;
                            case 13: cout << " > "; break;
                            case 14: cout << " v "; break;
                        }
                    }else{cout << "[~]";}
                    cout << "  ";
                }
                cout << "\n";
            }
        };

        auto Half = [](const int length){
            if(length%2==0){return length/2+rand()%2;
            }else{return length/2;};
        };

        auto FogClear = [](const int height, const int width,const int PlayerSpace[2],vector<vector<bool>>& fog){
            for (int i=PlayerSpace[0]-1; i<=PlayerSpace[0]+1; i++){
                for (int j=PlayerSpace[1]-1; j<=PlayerSpace[1]+1; j++){
                    if (i>=0 && i<height && j>=0 && j<width){
                        fog[i][j]=false;
                    }
                }
            }
        };

        for (int i=0; i<Height; i++){
            for (int j=0; j<Width; j++){
                Map[i][j]=rand()%10;
            }
        };
        
        if(Dest=="N"){PlayerSpace[0]=0;PlayerSpace[1]=Half(Width)+(rand()%3-1);D=11;
        }else if(Dest=="NE"){PlayerSpace[0]=0;PlayerSpace[1]=Width-rand()%2-1;D=11;
        }else if(Dest=="NW"){PlayerSpace[0]=0;PlayerSpace[1]=rand()%2;D=11;
        }else if(Dest=="E"){PlayerSpace[0]=Half(Height)+(rand()%3-1);PlayerSpace[1]=Width-1;D=13;
        }else if(Dest=="W"){PlayerSpace[0]=Half(Height)+(rand()%3-1);PlayerSpace[1]=0;D=12;
        }else if(Dest=="S"){PlayerSpace[0]=Height-1;PlayerSpace[1]=Half(Width)+(rand()%3-1);D=14;
        }else if(Dest=="SE"){PlayerSpace[0]=Height-1;PlayerSpace[1]=Width-rand()%2-1;D=14;
        }else if(Dest=="SW"){PlayerSpace[0]=Height-1;PlayerSpace[1]=rand()%2;D=14;}

        for (int i=PlayerSpace[0]-1; i<=PlayerSpace[0]+1; i++){
            for (int j=PlayerSpace[1]-1; j<=PlayerSpace[1]+1; j++){
                if (i>=0 && i<Height && j>=0 && j<Width){
                    Map[i][j]=D;
                }
            }
        };

        if(Extra=="N"){PlayerSpace[0]=0;PlayerSpace[1]=Half(Width)+(rand()%3-1);D=11;
        }else if(Extra=="NE"){PlayerSpace[0]=0;PlayerSpace[1]=Width-rand()%2-1;D=11;
        }else if(Extra=="NW"){PlayerSpace[0]=0;PlayerSpace[1]=rand()%2;D=11;
        }else if(Extra=="E"){PlayerSpace[0]=Half(Height)+(rand()%3-1);PlayerSpace[1]=Width-1;D=13;
        }else if(Extra=="W"){PlayerSpace[0]=Half(Height)+(rand()%3-1);PlayerSpace[1]=0;D=12;
        }else if(Extra=="S"){PlayerSpace[0]=Height-1;PlayerSpace[1]=Half(Width)+(rand()%3-1);D=14;
        }else if(Extra=="SE"){PlayerSpace[0]=Height-1;PlayerSpace[1]=Width-rand()%2-1;D=14;
        }else if(Extra=="SW"){PlayerSpace[0]=Height-1;PlayerSpace[1]=rand()%2;D=14;}

        for (int i=PlayerSpace[0]-1; i<=PlayerSpace[0]+1; i++){
            for (int j=PlayerSpace[1]-1; j<=PlayerSpace[1]+1; j++){
                if (i>=0 && i<Height && j>=0 && j<Width){
                    Map[i][j]=D;
                }
            }
        };
        
        
        if(Spawn=="N"){PlayerSpace[0]=0;PlayerSpace[1]=Half(Width)+(rand()%3-1);
        }else if(Spawn=="NE"){PlayerSpace[0]=0;PlayerSpace[1]=Width-rand()%2-1;
        }else if(Spawn=="NW"){PlayerSpace[0]=0;PlayerSpace[1]=rand()%2;
        }else if(Spawn=="E"){PlayerSpace[0]=Half(Height)+(rand()%3-1);PlayerSpace[1]=Width-1;
        }else if(Spawn=="W"){PlayerSpace[0]=Half(Height)+(rand()%3-1);PlayerSpace[1]=0;
        }else if(Spawn=="S"){PlayerSpace[0]=Height-1;PlayerSpace[1]=Half(Width)+(rand()%3-1);
        }else if(Spawn=="SE"){PlayerSpace[0]=Height-1;PlayerSpace[1]=Width-rand()%2-1;
        }else if(Spawn=="SW"){PlayerSpace[0]=Height-1;PlayerSpace[1]=rand()%2;}

        for (int i=PlayerSpace[0]-1; i<=PlayerSpace[0]+1; i++){
            for (int j=PlayerSpace[1]-1; j<=PlayerSpace[1]+1; j++){
                if (i>=0 && i<Height && j>=0 && j<Width){
                    Map[i][j]=0;
                }
            }
        };

        Map[PlayerSpace[0]][PlayerSpace[1]]=10;

        do{
            do{
                moved=false;
                FogClear(Height,Width,PlayerSpace,Fog);
                PrintMap(Height,Width,Map,Fog,PlayerSpace);
                cout << "Where would you like to move\n"
                    << "          1. Up\n"
                    << "2. Left                  3. Right\n"
                    << "          4. Down                       ";
                cin >> input;
                switch(input){
                    case 1: // UP
                        if (PlayerSpace[0]==0){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[0]--; moved=true;}
                        break;
                    case 2: // Left
                        if (PlayerSpace[1]==0){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[1]--; moved=true;}
                        break;
                    case 3: // Right
                        if (PlayerSpace[1]==Width-1){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[1]++; moved=true;}
                        break;
                    case 4: // Down
                        if (PlayerSpace[0]==Height-1){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[0]++; moved=true;}
                        break;
                    default: cout << "Invalid Input\n";
                }
            }while(!moved);
            Format::PageBreak();
            switch(Map[PlayerSpace[0]][PlayerSpace[1]]){       
                case 4: case 5: case 6: case 7:
                    MonsterEvent();
                    Format::Pause(); Format::PageBreak();
                    break;
                case 8:  
                    RandomMapEvent(inventory); 
                    break;
                case 9: 
                    cout << "You open a chest to find\n"
                         << "...\n";
                    if (rand()%10<9){
                        cout << "It was a Mimic!\n"
                             << "You loose health\n";
                    }else{ItemEvent(inventory);}
                    Format::Pause(); Format::PageBreak();
                    break;
                case 10:
                    cout << "Do you want to give up and retreat? (y/n): "; 
                    cin >> yn;
                    if (yn == 'y' || yn == 'Y') {return 0;}
                    Format::PageBreak();
                    break;
                case 11: case 12: case 13: 
                    cout << "Do you want to continue forward? (y/n): "; 
                    cin >> yn;
                    if (yn == 'y' || yn == 'Y') {return 1;}
                    Format::PageBreak();
                    break;
                case 14:
                    cout << "You see a farm nearby, investigate? (y/n): ";
                    cin >> yn;
                    if (yn == 'y' || yn == 'Y') {return 2;}
                    Format::PageBreak();
            }
            if(Map[PlayerSpace[0]][PlayerSpace[1]]<10){
                Map[PlayerSpace[0]][PlayerSpace[1]]=0;
            }
        }while(moved);
    return 0;
    }


    void RandomWorldEvent(vector<string>& inventory){
        switch(rand()%10){
            case 1:
                cout << "Something happened\n"
                     << "It was unremarkable\n";
            break;
            case 9:
                MonsterEvent();
            break;
            default: 
                cout << "You found something on the road\n";
                ItemEvent(inventory);
        }
        cout << "You travel\n";
        Format::Pause(); Format::PageBreak();
    }


    void RandomMapEvent(vector<string>& inventory){
        switch(rand()%10){
            case 1:
                cout << "You found something in the dirt\n";
                ItemEvent(inventory);
            break;
            case 9:
                MonsterEvent();
            break;
            default: cout << "Something happened\n"
                          << "It was unremarkable\n";
        }
        Format::Pause(); Format::PageBreak();
    }


    void MonsterEvent(){
        cout << "A monster appears\n"
            << "Comencing combat\n"
            << "...\n"
            << "You Win!\n";
        Level::GainExp(10);
    }


    void ItemEvent(vector<string>& inventory){
        switch(rand()%10){
            case 1: case 2: 
                cout << "It was a Health Potion\n";
                inventory.push_back("Healing Potion");
            break;
            case 3:  
                cout << "It was an Attack Potion\n";
                inventory.push_back("Attack Potion");
            case 4: 
                cout << "It was a Fire Potion\n";
                inventory.push_back("Fire Scroll");
            break;      
            default: cout << "It was rubbish\n";  
        }
    }


} // Ending namespace Map


namespace Level{ 

    int PlayerLevel=1;
    int PlayerExp=0;

    void GainExp(const int amount){
        const int ExpCap = PlayerLevel*50+50;
        PlayerExp+=amount;
        cout << "You have gained " << amount << " Experience\n";
        if(PlayerExp>=ExpCap){
            PlayerExp=PlayerExp%ExpCap;
            LevelUp();
        }
    }

    void LevelUp(){
        PlayerLevel+=1;
        cout << "LEVEL UP\n"
             << "You are now Level " << PlayerLevel << "\n";
    }   

} // Ending namespace Level


namespace Save{ 

    void SaveMenu(string& playerName, string& playerPower, vector<string>& inventory){
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
                    case 1:
                        switch(SaveGame(Filenum,playerName,playerPower,Level::PlayerLevel,Level::PlayerExp,inventory)){
                            case 0: return;
                            case 1: opnum=4;
                        }
                    break;
                    case 2:
                        switch(LoadGame(Filenum,playerName,playerPower,Level::PlayerLevel,Level::PlayerExp,inventory)){
                            case 0: return;
                            case 1: opnum=4;
                        }
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
        getline(SaveFile, temp); // playerName
        cout << "Name: " << temp << "  -  Level: ";
        getline(SaveFile, temp); // playerPower
        getline(SaveFile, temp); // PlayerLevel
        cout << temp << "  -  Location: ";
        getline(SaveFile, temp); // PlayerExp
        SaveFile >> tempnum;
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
    // Timestamp, playerName, playerPower, PlayerLevel,
    // PlayerExp, PlayerLoc.ID, inventory.size, inventory
    bool SaveGame(const int Filenum, const string& playerName, const string& playerPower,
                 const int& PlayerLevel,const int PlayerExp, const vector<string>& inventory){                    
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
                 << playerName << "\n" 
                 << playerPower << "\n"
                 << Level::PlayerLevel << "\n"
                 << Level::PlayerExp << "\n"
                 << Map::PlayerLoc.ID << "\n"
                 << inventory.size() << "\n";
        for (const string& item : inventory) {
            SaveFile << item << "\n";
        }
        SaveFile.close();
        cout << "Game saved successfully.\n";
        return 0;
    }

    //
    //
    // Timestamp, playerName, playerPower, PlayerLevel,
    // PlayerExp, PlayerLoc.ID, inventory.size, inventory
    bool LoadGame(int Filenum, string& playerName, string& playerPower, int& PlayerLevel, 
                  int PlayerExp, vector<string>& inventory){
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
        getline(SaveFile, playerName); // playerName
        getline(SaveFile, playerPower); // playerPower
        SaveFile >> Level::PlayerLevel; // PlayerLevel
        SaveFile.ignore();
        SaveFile >> Level::PlayerExp; // PlayerExp
        SaveFile.ignore();
        SaveFile >> Map::PlayerLoc.ID; // PlayerLoc.ID
        SaveFile.ignore();
        switch(Map::PlayerLoc.ID){
            case 1: Map::PlayerLoc=Map::City; break;
            case 2: Map::PlayerLoc=Map::Temple; break;
            case 3: Map::PlayerLoc=Map::Tower; break;
            case 4: Map::PlayerLoc=Map::Farm; break;
            case 5: Map::PlayerLoc=Map::Castle; break;
        }
        SaveFile >> size; // inventory.size
        SaveFile.ignore();
        inventory.clear();
        for (int i = 0; i < size; i++) {
            getline(SaveFile, Item);        // inventory
            inventory.push_back(Item);
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
        switch (fail){
            case 0: cout << "File successfully deleted\n";
            case 1: cout << "No file to delete found\n";
        }
        return fail;
    }

} // Ending namespace Save


namespace Format{

    void PageBreak(){
        cout << "-------------------------------------------------------------\n"; 
    }

    void Pause(){
        cout << "Press Enter to continue  ";
        cin.ignore();cin.ignore();
    }

} // Ending namespace Format

