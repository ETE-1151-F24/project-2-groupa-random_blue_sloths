/*
This file has functions for the map
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "D_Map.hpp"
#include "D_Misc.hpp"
#include "Player.hpp"
#include "Inventory.hpp"
using namespace std;


namespace Map{ 
    
    Location City(1,"The City of Kronos",true,true);
    Location Temple(2,"Temple of Zeus",false,true);
    Location Tower(3,"Hestia's Tower",false,false);
    Location Farm(4,"Pagasus Farm",false,true);
    Location Castle(5,"Hades' Castle",false,false);



    void setLoc(Player& P){
        switch(P.Loc.ID){
            case 1: P.Loc=City; break;
            case 2: P.Loc=Temple; break;
            case 3: P.Loc=Tower; break;
            case 4: P.Loc=Farm; break;
            case 5: P.Loc=Castle; break;
        }
    }

    void setLoc(Player& P, int Location){
        switch(Location){
            case 1: P.Loc=City; break;
            case 2: P.Loc=Temple; break;
            case 3: P.Loc=Tower; break;
            case 4: P.Loc=Farm; break;
            case 5: P.Loc=Castle; break;
        }
    }

    void WorldMap(const Player& P){
        ifstream Map;
        string MapFeed;
        if (P.Loc.ID==City.ID || P.Loc.ID==Temple.ID || P.Loc.ID==Tower.ID){        
            Map.open("Maps/Map1.txt");
            while (getline(Map, MapFeed)) {
                cout << MapFeed << "\n";
            }
        }else if(P.Loc.ID==Farm.ID || P.Loc.ID==Castle.ID){
            Map.open("Maps/Map2.txt");
            while (getline(Map, MapFeed)) {
                cout << MapFeed << "\n";
            }
        }
        Map.close();
        cout << "You are currently at " << P.Loc.Name << "\n";
    }

    void WorldMapTravel(Player& P){
        int Destination;
        char yn;
        WorldMap(P);
        switch(P.Loc.ID){
            case 1: // City of Kronos
                cout << "Where would you like to go?\n"
                    << "1. " << Temple.Name << "\n"
                    << "2. " << Tower.Name << "\n";
                cin >> Destination;
                Format::PageBreak();
                switch(Destination){
                    case 1: // Temple of Zeus
                        if(!Adventure(P,5,5,"NE","SW")){return;}
                        RandomWorldEvent(P);
                        if(!Adventure(P,5,5,"NE","S")){return;}
                        P.Loc=Temple;
                        cout << "You have arrived at " << P.Loc.Name << "\n";
                    break;
                    case 2: // Hestia's Tower
                        if(!Adventure(P,5,5,"NW","SE")){return;}
                        RandomWorldEvent(P);
                        if(!Adventure(P,5,5,"NW","S")){return;}
                        P.Loc=Tower;
                        cout << "You have arrived at " << P.Loc.Name << "\n";
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
                        if(!Adventure(P,5,5,"S","NE")){return;}
                        RandomWorldEvent(P);
                        if(!Adventure(P,5,5,"SW","NE")){return;}
                        P.Loc=City;
                        cout << "You have arrived at " << P.Loc.Name << "\n";
                    break;
                    case 2: // Hestia's Tower
                        if(!Adventure(P,8,3,"W","E")){return;}
                        RandomWorldEvent(P);
                        switch(Adventure(P,8,8,"W","E","S")){
                            case 0: return;
                            case 1: P.Loc=Tower;
                                cout << "You have arrived at " << P.Loc.Name << "\n"; return;
                            case 2: P.Loc=Farm;
                                cout << "You have arrived at " << P.Loc.Name << "\n"; return;
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
                        if(!Adventure(P,5,5,"S","NW")){return;}
                        RandomWorldEvent(P);
                        if(!Adventure(P,5,5,"SE","NW")){return;}
                        P.Loc=City;
                        cout << "You have arrived at " << P.Loc.Name << "\n";
                    break;
                    case 2: // Temple of Zeus
                        switch(Adventure(P,8,8,"E","W","S")){
                            case 0: return;
                            case 2: P.Loc=Farm; 
                                cout << "You have arrived at " << P.Loc.Name << "\n"; return;
                        }
                        RandomWorldEvent(P);
                        if(!Adventure(P,8,3,"E","W")){return;}
                        P.Loc=Temple;
                        cout << "You have arrived at " << P.Loc.Name << "\n";
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
                        if(!Adventure(P,8,8,"S","W")){return;}
                        RandomWorldEvent(P);
                        if(!Adventure(P,8,3,"E","W")){return;}
                        P.Loc=Temple;
                        cout << "You have arrived at " << P.Loc.Name << "\n";
                    break;
                    case 2: // Hestia's Tower
                        if(!Adventure(P,8,8,"S","E")){return;}
                        P.Loc=Tower;
                        cout << "You have arrived at " << P.Loc.Name << "\n";
                    break;
                    case 3: // Hades' Castle
                        if(!Adventure(P,10,10,"E","S")){return;}
                        RandomWorldEvent(P);
                        if(!Adventure(P,6,16,"N","S")){return;}
                        P.Loc=Castle;
                        cout << "You have arrived at " << P.Loc.Name << "\n";
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
                if(!Adventure(P,5,15,"S","N")){return;}
                RandomWorldEvent(P);
                if(!Adventure(P,10,10,"S","E")){return;}
                P.Loc=Farm;
                cout << "You have arrived at " << P.Loc.Name << "\n";
            break;
        }
    }


    bool Adventure(Player& P, const int Width, const int Height, const string Spawn, const string Dest){
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
                    << "          8. Up\n"
                    << "4. Left                  6. Right\n"
                    << "          2. Down                       : ";
                cin >> input;
                switch(input){
                    case 8: // UP
                        if (PlayerSpace[0]==0){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[0]--; moved=true;}
                        break;
                    case 4: // Left
                        if (PlayerSpace[1]==0){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[1]--; moved=true;}
                        break;
                    case 6: // Right
                        if (PlayerSpace[1]==Width-1){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[1]++; moved=true;}
                        break;
                    case 2: // Down
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
                    MonsterEvent(P);
                    Format::Pause(); Format::PageBreak();
                    break;
                case 8:  
                    RandomMapEvent(P); 
                    break;
                case 9: 
                    cout << "You open a chest to find\n"
                         << "...\n";
                    if ((rand()%10)<9){
                        cout << "It was a Mimic!\n"
                             << "You loose health\n";
                    }else{ItemEvent();}
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
        return false;
    }



    /*-------------------------------------------------------------------------------------*/
    /*-------------------------------------------------------------------------------------*/
    /*-------------------------------------------------------------------------------------*/



    int Adventure(Player& P, const int Width, const int Height, const string Spawn, const string Dest,const string Extra){
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
                    << "          8. Up\n"
                    << "4. Left                  6. Right\n"
                    << "          2. Down                       : ";
                cin >> input;
                switch(input){
                    case 8: // UP
                        if (PlayerSpace[0]==0){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[0]--; moved=true;}
                        break;
                    case 4: // Left
                        if (PlayerSpace[1]==0){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[1]--; moved=true;}
                        break;
                    case 6: // Right
                        if (PlayerSpace[1]==Width-1){
                            cout<<"You can not move that way\n";
                            Format::PageBreak();
                            break;
                        }
                        else {PlayerSpace[1]++; moved=true;}
                        break;
                    case 2: // Down
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
                    MonsterEvent(P);
                    Format::Pause(); Format::PageBreak();
                    break;
                case 8:  
                    RandomMapEvent(P); 
                    break;
                case 9: 
                    cout << "You open a chest to find\n"
                         << "...\n";
                    if ((rand()%10)<9){
                        cout << "It was a Mimic!\n"
                             << "You loose health\n";
                    }else{ItemEvent();}
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


    void RandomWorldEvent(Player& P){
        switch(rand()%10){
            case 1:
                cout << "Something happened\n"
                     << "It was unremarkable\n";
            break;
            case 9:
                MonsterEvent(P);
            break;
            default: 
                cout << "You found something on the road\n";
                ItemEvent();
        }
        cout << "You travel\n";
        Format::Pause(); Format::PageBreak();
    }


    void RandomMapEvent(Player& P){
        switch(rand()%10){
            case 1:
                cout << "You found something in the dirt\n";
                ItemEvent();
            break;
            case 9:
                MonsterEvent(P);
            break;
            default: cout << "Something happened\n"
                          << "It was unremarkable\n";
        }
        Format::Pause(); Format::PageBreak();
    }


    void MonsterEvent(Player& P){
        cout << "A monster appears\n"
            << "Comencing combat\n"
            << "...\n"
            << "You Win!\n";
        Level::GainExp(P,10);
    }


    void ItemEvent(){
        switch(rand()%10){
            case 1: case 2: 
                cout << "It was a Health Potion\n";
                addItem("Health Potion","A mysterious liquid of life",50);
            break;
            case 3:  
                cout << "It was an Attack Potion\n";
                addItem("Attack Potion","A potion that makes you hit real hard",5);
            case 4: 
                cout << "It was a Fire Scroll\n";
                addItem("Fire Scroll","A scroll used to cast a basic fire spell",25);
            break;      
            default: cout << "It was rubbish\n";  
        }
    }


} // Ending namespace Map

