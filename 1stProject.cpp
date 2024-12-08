#include <iostream>
#include <vector>
#include <string>
#include "Player.hpp"
#include "Devine.hpp"
#include "Inventory.hpp"
using namespace std;

int main() {

    Player player;

    string name;
    cout << "Welcome to the Adventure Game!" << endl;
    cout << "What is your name: ";
    cin >> name;

    // choose player type
    player.Name = name;
    player.choosePlayerType();
    player.displayPlayerStats();

    addItem("Healing Potion", "restores 20 magic points.", 20);
    addItem("Sword", "No magic bonus.", 0);
    addItem("Armor", "Reduces incoming magic damage by 3 points.", -3);
    addItem("Spell Book", "Increases your magic by 10 points.", 10);

    displayInventory();


    bool DONE=false;

    while (!DONE){
        Map::WorldMapTravel(inventoryItems);
        displayInventory();
    }

    return 0;
}