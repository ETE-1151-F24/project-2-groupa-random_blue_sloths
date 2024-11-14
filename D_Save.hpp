/*
This file is used for declaring the saving mechanic 
*/

#ifndef D_Save_hpp 
#define D_Save_hpp

#include <string>
#include <vector>
#include "Player.hpp"


namespace Save{

    void SaveMenu(Player& P);
    void PrintSave();
    void PrintSave(const int Filenum);
    bool SaveGame(const int Filenum, const Player& P);
    bool LoadGame(const int Filenum, Player& P);
    bool DeleteSave(const int Filenum);
    
} // Ending namespace Save

#endif
