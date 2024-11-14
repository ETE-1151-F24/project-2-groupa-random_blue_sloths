/*
This file is used for declaring the map mechanics
*/

#ifndef D_Map_hpp 
#define D_Map_hpp

#include <string>
#include <vector>
#include "Player.hpp"


namespace Map{ 

    class Location{
    public:
        int ID;
        std::string Name;
        bool Shop;
        bool Rest;

        Location(int _ID,std::string _Name,bool _Shop,bool _Rest)
        : ID(_ID),Name(_Name), Shop(_Shop), Rest(_Rest) {}
    };

    extern Location City,Temple,Tower,Farm,Castle;

    void setLoc(Player& P);
    void setLoc(Player& P, int Location);
    void WorldMap(const Player& P);
    void WorldMapTravel(Player& P);
    bool Adventure(Player &P, const int Width, const int Height, const std::string Spawn, const std::string Dest);
    int  Adventure(Player &P, const int Width, const int Height, const std::string Spawn, const std::string Dest, const std::string Extra);
    void RandomWorldEvent(Player& P);
    void RandomMapEvent(Player& P);
    void MonsterEvent(Player& P);
    void ItemEvent();


} // Ending namespace Map

#endif
