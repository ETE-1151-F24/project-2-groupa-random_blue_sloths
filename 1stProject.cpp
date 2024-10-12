#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to display inventory
void displayInventory(const vector<string>& inventory) {
    if (inventory.empty()) {
        cout << "Your inventory is empty.\n";
    } else {
        cout << "Inventory: \n";
        for (size_t i = 0; i < inventory.size(); ++i) {
            cout << i + 1 << ". " << inventory[i] << endl;
        }
    }
}

//choose player power based on input
string choosePower(int choice) {
    switch (choice) {
        case 1: return "Healing";
        case 2: return "Telekinesis";
        case 3: return "Invisibility";
        case 4: return "Super Strength";
        case 5: return "Super Speed";
        case 6: return "Power Absorption";
        case 7: return "Time Traveler";
        case 8: return "X-ray Vision";
        case 9: return "Radar Sensing";
        case 10: return "Shape Shifting";
        default: return "Unknown Power"; 
    }
}

int main() {
    cout << "Welcome" << endl;
    
    string playerName;
    cout << "What is your name: ";
    cin >> playerName;
    cout << "Welcome " << playerName << "!" << endl;

    // Choosing player power
    int choice;
    cout << "What powers will " << playerName << " possess?" << endl;
    cout << "1. Healing" << endl;
    cout << "2. Telekinesis" << endl;
    cout << "3. Invisibility" << endl;
    cout << "4. Super Strength" << endl;
    cout << "5. Super Speed" << endl;
    cout << "6. Power Absorption" << endl;
    cout << "7. Time Traveler" << endl;
    cout << "8. X-ray Vision" << endl;
    cout << "9. Radar Sensing" << endl;
    cout << "10. Shape Shifting" << endl;
    cin >> choice;

    // Get the chosen power
    string playerPower = choosePower(choice);
    cout << playerName << " has chosen the power of " << playerPower << "!\n";

 // Add items to inventory
    vector<string> inventory;
    inventory.push_back("Healing Potion");
    inventory.push_back("Magic Stone");
    inventory.push_back("Teleportation Ring");
    inventory.push_back("Invisibilty Cloak");
    inventory.push_back("Sword");
    inventory.push_back("Shield");

    char viewInventoryChoice;
    cout << "Would you like to view your inventory? (y/n): ";
    cin >> viewInventoryChoice;

    if (viewInventoryChoice == 'y' || viewInventoryChoice == 'Y') {
        displayInventory(inventory);
    } else {
        cout << "You chose not to view the inventory.\n";
    }

    return 0;
}
