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


    void WorldMapTravel(){
        int Destination;
        char yn;
        WorldMap();
        switch(PlayerLoc.ID){
            case 1: // City of Kronos
                cout << "Where would you like to go?\n"
                    << "1. " << Temple.Name << "\n"
                    << "2. " << Tower.Name << "\n";
                cin >> Destination;
                PageBreak();
                switch(Destination){
                    case 1: // Temple of Zeus
                        if(!Adventure(5,5,"NE","SW")){return;}
                        RandomWorldEvent();
                        if(!Adventure(5,5,"NE","S")){return;}
                        PlayerLoc=Temple;
                    break;
                    case 2: // Hestia's Tower
                        if(!Adventure(5,5,"NW","SE")){return;}
                        RandomWorldEvent();
                        if(!Adventure(5,5,"NW","S")){return;}
                        PlayerLoc=Tower;
                    break;
                    default: cout << "Invalid Choice\n"; return;
                }
            break;
            case 2: // Temple of Zeus
                cout << "Where would you like to go?\n"
                    << "1. " << City.Name << "\n"
                    << "2. " << Tower.Name << "\n";
                cin >> Destination;
                PageBreak();
                switch(Destination){
                    case 1: // City of Kronos
                        if(!Adventure(5,5,"S","NE")){return;}
                        RandomWorldEvent();
                        if(!Adventure(5,5,"SW","NE")){return;}
                        PlayerLoc=City;
                    break;
                    case 2: // Hestia's Tower
                        if(!Adventure(8,3,"W","E")){return;}
                        RandomWorldEvent();
                        switch(Adventure(8,8,"W","E","S")){
                            case 0: return;
                            case 1: PlayerLoc=Tower; return;
                            case 2: PlayerLoc=Farm; return;
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
                PageBreak();
                switch(Destination){
                    case 1: // City of Kronos
                        if(!Adventure(5,5,"S","NW")){return;}
                        RandomWorldEvent();
                        if(!Adventure(5,5,"SE","NW")){return;}
                        PlayerLoc=City;
                    break;
                    case 2: // Temple of Zeus
                        switch(Adventure(8,8,"E","W","S")){
                            case 0: return;
                            case 2: PlayerLoc=Farm; return;
                        }
                        RandomWorldEvent();
                        if(!Adventure(8,3,"E","W")){return;}
                        PlayerLoc=Temple;
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
                PageBreak();
                switch(Destination){
                    case 1: // Temple of Zeus
                        if(!Adventure(8,8,"S","W")){return;}
                        RandomWorldEvent();
                        if(!Adventure(8,3,"E","W")){return;}
                        PlayerLoc=Temple;
                    break;
                    case 2: // Hestia's Tower
                        if(!Adventure(8,8,"S","E")){return;}
                        PlayerLoc=Tower;
                    break;
                    case 3: // Hades' Castle
                        if(!Adventure(10,10,"E","S")){return;}
                        RandomWorldEvent();
                        if(!Adventure(6,16,"N","S")){return;}
                        PlayerLoc=Castle;
                    break;
                    default: cout << "Invalid Choice\n"; return;
                }         
            break;
            case 5: // Hades' Castle
                cout << "Return to the farm? (y/n): ";
                cin >> yn;
                if(yn != 'y'||yn != 'Y'){return;}
                PageBreak();
                //Pagasus Farm
                if(!Adventure(5,15,"S","N")){return;}
                RandomWorldEvent();
                if(!Adventure(10,10,"S","E")){return;}
                PlayerLoc=Farm;
            break;
        }
    }


    bool Adventure(const int Width, const int Height, const string Spawn, const string Dest){
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
                            PageBreak();
                            break;
                        }
                        else {PlayerSpace[0]--; moved=true;}
                        break;
                    case 2: // Left
                        if (PlayerSpace[1]==0){
                            cout<<"You can not move that way\n";
                            PageBreak();
                            break;
                        }
                        else {PlayerSpace[1]--; moved=true;}
                        break;
                    case 3: // Right
                        if (PlayerSpace[1]==Width-1){
                            cout<<"You can not move that way\n";
                            PageBreak();
                            break;
                        }
                        else {PlayerSpace[1]++; moved=true;}
                        break;
                    case 4: // Down
                        if (PlayerSpace[0]==Height-1){
                            cout<<"You can not move that way\n";
                            PageBreak();
                            break;
                        }
                        else {PlayerSpace[0]++; moved=true;}
                        break;
                    default: cout << "Invalid Input\n";
                }
            }while(!moved);
            PageBreak();
            switch(Map[PlayerSpace[0]][PlayerSpace[1]]){       
                case 4: case 5: case 6: case 7:
                    cout << "A monster appears\n"
                         << "Comencing combat\n"
                         << "...\n"
                         << "You Win!\n";
                    Pause();
                    break;
                case 8:  
                    RandomMapEvent(); 
                    break;
                case 9: 
                    cout << "You open a chest to find\n"
                         << "...\n"
                         << "Nothing\n";
                    Pause();
                    break;
                case 10:
                    cout << "Do you want to give up and retreat? (y/n): "; 
                    cin >> yn;
                    if (yn == 'y' || yn == 'Y') {return false;}
                    PageBreak();
                    break;
                case 11: case 12: case 13: case 14: 
                    cout << "Do you want to continue forward? (y/n): "; 
                    cin >> yn;
                    if (yn == 'y' || yn == 'Y') {return true;}
                    PageBreak();
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



    int Adventure(const int Width, const int Height, const string Spawn, const string Dest,const string Extra){
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
                            PageBreak();
                            break;
                        }
                        else {PlayerSpace[0]--; moved=true;}
                        break;
                    case 2: // Left
                        if (PlayerSpace[1]==0){
                            cout<<"You can not move that way\n";
                            PageBreak();
                            break;
                        }
                        else {PlayerSpace[1]--; moved=true;}
                        break;
                    case 3: // Right
                        if (PlayerSpace[1]==Width-1){
                            cout<<"You can not move that way\n";
                            PageBreak();
                            break;
                        }
                        else {PlayerSpace[1]++; moved=true;}
                        break;
                    case 4: // Down
                        if (PlayerSpace[0]==Height-1){
                            cout<<"You can not move that way\n";
                            PageBreak();
                            break;
                        }
                        else {PlayerSpace[0]++; moved=true;}
                        break;
                    default: cout << "Invalid Input\n";
                }
            }while(!moved);
            PageBreak();
            switch(Map[PlayerSpace[0]][PlayerSpace[1]]){       
                case 4: case 5: case 6: case 7:
                    cout << "A monster appears\n"
                         << "Comencing combat\n"
                         << "...\n"
                         << "You Win!\n";
                    Pause();
                    break;
                case 8:  
                    RandomMapEvent(); 
                    break;
                case 9: 
                    cout << "You open a chest to find "
                         << "...\n"
                         << "Nothing\n";
                    Pause();
                    break;
                case 10:
                    cout << "Do you want to give up and retreat? (y/n): "; 
                    cin >> yn;
                    if (yn == 'y' || yn == 'Y') {return 0;}
                    PageBreak();
                    break;
                case 11: case 12: case 13: 
                    cout << "Do you want to continue forward? (y/n): "; 
                    cin >> yn;
                    if (yn == 'y' || yn == 'Y') {return 1;}
                    PageBreak();
                    break;
                case 14:
                    cout << "You see a farm nearby, investigate? (y/n): ";
                    cin >> yn;
                    if (yn == 'y' || yn == 'Y') {return 2;}
                    PageBreak();
            }
            if(Map[PlayerSpace[0]][PlayerSpace[1]]<10){
                Map[PlayerSpace[0]][PlayerSpace[1]]=0;
            }
        }while(moved);
    return 0;
    }


    void RandomWorldEvent(){
        switch(rand()%10){
            case 1:
                cout << "Something happened\n"
                     << "It was unremarkable\n";\
            break;
            case 9:
                cout << "A monster appears\n"
                     << "Comencing combat\n"
                     << "...\n"
                     << "You Win!\n";
            break;
            default: cout << "You found something\n"
                          << "It was rubbish\n";
        }
        cout << "You travel\n";
        Pause();
    }


    void RandomMapEvent(){
        switch(rand()%10){
            case 1:
                cout << "You found something\n"
                     << "It was rubbish\n";
            break;
            case 9:
                cout << "A monster appears\n"
                     << "Comencing combat\n"
                     << "...\n"
                     << "You Win!\n";
            break;
            default: cout << "Something happened\n"
                          << "It was unremarkable\n";
        }
        Pause();
    }


    void PageBreak(){
        cout << "--------------------------------------------------------\n"; 
    }

    void Pause(){
        cout << "Press Enter to continue  ";
        cin.ignore();cin.ignore();
        PageBreak();
    }

} // Ending namespace Map



namespace Level{ 

    void Increase(){

    }

} // Ending namespace Level



namespace Save{ 

} // Ending namespace Save


