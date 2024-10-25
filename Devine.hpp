/*
This file is used for declaring the map, 
leveling, and save mechanics. 
*/

// these is needed for header files 
#ifndef Devine_h 
#define Devine_h

#include<iostream>



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


    void WorldMap();
    void WorldMapTravel();
    bool Adventure(const int Width, const int Height, const std::string Spawn, const std::string Dest);
    int Adventure(const int Width, const int Height, const std::string Spawn, const std::string Dest,const std::string Extra);
    void RandomWorldEvent();
    void RandomMapEvent();
    void PageBreak();
    void Pause();



} // Ending namespace Map



namespace Level{ 

    void Increase();


} // Ending namespace Level



namespace Save{

    void SaveGame();
    void LoadGame();
    

} // Ending namespace Save





#endif // This is needed for header files 
