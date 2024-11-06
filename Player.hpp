#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Devine.hpp"

class Player {
public:

    std::string Name;
    int Level;
    int Exp;
    int Type; 
    int Magic;
    Map::Location Loc;

    void choosePlayerType();
    void displayPlayerStats();

};

#endif // PLAYER_H