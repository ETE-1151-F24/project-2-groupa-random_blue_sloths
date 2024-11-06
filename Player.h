#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(const std::string& name);
    void choosePlayerType();
    void displayPlayerStats();

    std::string Name;
    int Type; 
    int Magic;
};

#endif // PLAYER_H