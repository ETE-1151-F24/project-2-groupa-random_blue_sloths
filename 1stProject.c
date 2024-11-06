#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "Inventory.h"
using namespace std;

int main() {
    string name;
    cout << "Welcome to the Adventure Game!" << endl;
    cout << "What is your name: ";
    cin >> name;

    // choose player type
    Player player(name);
    player.choosePlayerType();
    player.displayPlayerStats();

    Inventory inventory;

    inventory.addItem("Healing Potion", "restores 20 magic points.", 20);
    inventory.addItem("Sword", "No magic bonus.", 0);
    inventory.addItem("Armor", "Reduces incoming magic damage by 3 points.", -3);
    inventory.addItem("Spell Book", "Increases your magic by 10 points.", 10);

    inventory.displayInventory();

    return 0;
}