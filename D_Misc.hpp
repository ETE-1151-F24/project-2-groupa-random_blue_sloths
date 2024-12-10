/*
This file is used for declaring the leveling 
mechanics and misc formatting. 
*/

#ifndef D_Misc_h 
#define D_Misc_h

#include "Player.hpp"


namespace Level{ 

    void GainExp(Player& P, const int amount);
    void LevelUp(Player& P);

} // Ending namespace Level


namespace Format{

    void PageBreak();
    void Pause();

} // Ending namespace Format


#endif // This is needed for header files 
