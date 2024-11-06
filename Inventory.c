#include <iostream>
#include "Inventory.h"
using namespace std;

vector<string> inventoryItems;
vector<string> inventoryDescriptions;
vector<int> inventoryTraits;

void Inventory::addItem(const std::string& name, const std::string& description, int trait) {
    inventoryItems.push_back(name);
    inventoryDescriptions.push_back(description);
    inventoryTraits.push_back(trait);
}

void Inventory::displayInventory() {
    for (int i = 0; i < inventoryItems.size(); ++i) {
        cout << "Item: " << inventoryItems[i] << "\n";
        cout << "Description: " << inventoryDescriptions[i] << "\n";
        cout << "Trait: " << inventoryTraits[i] << "\n";
        cout << "----------------------\n";
    }
}