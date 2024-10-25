/*
This file has functions for the map, 
leveling, and save mechanics. 
*/

#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <ctime>
#include <string>
#include"Devine.hpp"
using namespace std;

namespace Map{ 

    Location City(1,"The City of Kronos",true,true);
    Location Temple(2,"Temply of Zeus",false,true);
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
    }


    void WorldMapTravel(const Location Destination){
        switch(PlayerLoc.ID){
            case 1: // City of Kronos
                switch(Destination.ID){
                    case 2: // Temple of Zeus
                        Adventure(5,5,"NE","SW");
                        RandomEvent();
                        Adventure(5,5,"NE","S");
                    break;
                    case 3: // Hestia's Tower
                        Adventure(5,5,"NW","SE");
                        RandomEvent();
                        Adventure(5,5,"NW","S");
                    break;
                }
            break;
            case 2: // Temple of Zeus
                switch(Destination.ID){
                    case 1: // City of Kronos
                        Adventure(5,5,"S","NE");
                        RandomEvent();
                        Adventure(5,5,"SW","NE");
                    break;
                    case 3: // Hestia's Tower
                        Adventure(8,3,"W","E");
                        RandomEvent();
                        Adventure(8,8,"W","E","S");
                    break;
                }
            break;
            case 3: // Hestia's Tower
                switch(Destination.ID){
                    case 1: // City of Kronos
                        Adventure(5,5,"S","NW");
                        RandomEvent();
                        Adventure(5,5,"SE","NW");
                    break;
                    case 2: // Temple of Zeus
                        Adventure(8,8,"E","W","S");
                        RandomEvent();
                        Adventure(8,3,"E","W");
                    break;
                }

            break;
            case 4: // Pagasus Farm
                switch(Destination.ID){
                    case 2: // Temple of Zeus
                        Adventure(8,8,"S","W");
                        RandomEvent();
                        Adventure(8,3,"E","W");
                    break;
                    case 3: // Hestia's Tower
                        Adventure(8,8,"S","E");
                    break;
                    case 5: // Hades' Castle
                        Adventure(10,10,"E","S");
                        RandomEvent();
                        Adventure(6,16,"N","S");
                    break;
                }          
            break;
            case 5: // Hades' Castle
                //Pagasus Farm
                Adventure(5,15,"S","N");
                RandomEvent();
                Adventure(10,10,"S","E");
            break;
        }
    }



    void Adventure(const int Width, const int Height, const string Spawn, const string Dest){
        int map[Width]{Height};
        bool fog[Width][Height];
        srand(time(0));
        for (int i=0;i=Width-1;i++){
            for (int j=0;j=Height-1;j++){
                map[i][j]=rand()%100+1;
            }
        }



    }



    void Adventure(const int Width, const int Height, const string Spawn, const string Dest,const string Extra){


    }


    void RandomEvent(){


    }

} // Ending namespace Map



namespace Level{ 

    void Increase(){

    }

} // Ending namespace Level



namespace Save{ 

} // Ending namespace Save


