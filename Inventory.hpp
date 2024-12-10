#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>
#include <string>

    std::vector<std::string> inventoryItems;
    std::vector<std::string> inventoryDescriptions;
    std::vector<int> inventoryTraits;

    void addItem(const std::string& name, const std::string& description, int trait);
    void displayInventory();

#endif // INVENTORY_H