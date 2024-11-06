#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>
#include <string>

class Inventory {
public:
    void addItem(const std::string& name, const std::string& description, int trait);
    void displayInventory();
};

#endif // INVENTORY_H