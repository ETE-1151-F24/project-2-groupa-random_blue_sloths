/*
This file is used to store all base stats
of the player and enimies
*/

// these is needed for header files 
#ifndef BaseStats_h
#define BaseStats_h

#include<string> // To use string - names, descriptions


// Namespace created so varible names can be reused by other people
namespace BaseStats{ // Base stats of player and enimies


// Base variable for new characters
class Character{
 public:
    std::string Name;
    std::string RaceName;
    
    int Level = 1;
    int MaxHealth = 100;
    int MaxMana = 25;

    int Health = MaxHealth;
    int Mana = MaxMana;
    int Damage = 3;
    int MDam = 2;
    int Defence = 0;
    int MDef = 0;
};


// Variables for the player
class Player: public Character{
 public:
    int BagSize = 9;
    std::string Background;
    std::string Profession;
    int EquippedWeapon = 0;
    int EquippedArmor = 0;
    int EquippedAccessory = 0;
};


} // Ending namespace BaseStats

#endif // This is needed for header files 
