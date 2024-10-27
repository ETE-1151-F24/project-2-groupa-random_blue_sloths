/*
This file is used for declaring the map, 
leveling, and save mechanics. 
*/

#include<string>
#include<vector>

// these is needed for header files 
#ifndef Devine_h 
#define Devine_h


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
    void WorldMapTravel(std::vector<std::string>& inventory);
    bool Adventure(const int Width, const int Height, const std::string Spawn, const std::string Dest, std::vector<std::string>& inventory);
    int  Adventure(const int Width, const int Height, const std::string Spawn, const std::string Dest,const std::string Extra, std::vector<std::string>& inventory);
    void RandomWorldEvent(std::vector<std::string>& inventory);
    void RandomMapEvent(std::vector<std::string>& inventory);
    void MonsterEvent();
    void ItemEvent(std::vector<std::string>& inventory);


} // Ending namespace Map



namespace Level{ 

    void GainExp(const int amount);
    void LevelUp();

} // Ending namespace Level



namespace Save{

    void SaveMenu(std::string& playerName, std::string& playerPower, std::vector<std::string>& inventory);
    void PrintSave();
    void PrintSave(const int Filenum);
    bool SaveGame(const int Filenum, const std::string& playerName, const std::string& playerPower,
                 const int& PlayerLevel, const int PlayerExp, const std::vector<std::string>& inventory);
    bool LoadGame(int Filenum, std::string& playerName, std::string& playerPower,
                 int& PlayerLevel, int PlayerExp, std::vector<std::string>& inventory);
    bool DeleteSave(const int Filenum);
    
} // Ending namespace Save


namespace Format{

    void PageBreak();
    void Pause();

} // Ending namespace Format


#endif // This is needed for header files 
