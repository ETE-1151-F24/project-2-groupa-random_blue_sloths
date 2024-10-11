/*
This file is used to store all the items
and equipment stats in the game
*/

// these is needed for header files 
#ifndef ItemList_h 
#define ItemList_h

#include<string> // To use string - names, descriptions
#include<vector> // To use vectors - each item type


// Namespace created so varible names can be reused by other people
namespace ItemList{ // List of all items


// Type of item
enum class ItemType {
    Weapon, Armor, Accessory, 
    Consumable, Misc
}; // Wraps up class items


// Variables for Items
class Items {
 public: 
    int ItemID;             // Unique Identifer for the item
    std::string ItemName;   // Name of item
    ItemType Type;          // Item type
    std::string ItemDesc;   // Description of item

    // Constructor for items vector
    Items(int _ItemID, std::string _ItemName, ItemType _Type, std::string _ItemDesc)
        : ItemID(_ItemID), ItemName(_ItemName), Type(_Type), ItemDesc(_ItemDesc) {}
};


// Variables for Weapons
class Weapon: public Items {
 public:
    int Damage;             // Attribute modifiers
    int MDam;

    // Constructor for weapon vector
    Weapon(int _ItemID, std::string _ItemName, ItemType _Type, std::string _ItemDesc, int _Damage, int _MDam)
        : Items(_ItemID, _ItemName, _Type, _ItemDesc), Damage(_Damage), MDam(_MDam) {}
};


// Variables for Armor
class Armor: public Items {
 public:
    int MaxHealth;          // Attribute modifiers
    int MaxMana;
    int Defence;
    int MDef;

    // Constructor for armor vector
    Armor(int _ItemID, std::string _ItemName, ItemType _Type, std::string _ItemDesc, int _MaxHealth, int _MaxMana, int _Defence, int _MDef)
        : Items(_ItemID, _ItemName, _Type, _ItemDesc), MaxHealth(_MaxHealth), MaxMana(_MaxMana), Defence(_Defence), MDef{_MDef} {}
};


// Creating extra variables for Accessory
class Accessory: public Items {
 public:
    int MaxHealth;          // Attribute modifiers
    int MaxMana;
    int Damage;
    int MDam;
    int Defence;
    int MDef;

    // Constructor for accessory vector
    Accessory(int _ItemID, std::string _ItemName, ItemType _Type, std::string _ItemDesc,  int _MaxHealth, int _MaxMana, int _Damage, int _MDam, int _Defence, int _MDef)
        : Items(_ItemID, _ItemName, _Type, _ItemDesc), MaxHealth(_MaxHealth), MaxMana(_MaxMana), Defence(_Defence), MDef{_MDef} {}
};


// Creating extra variables for Consumable
class Consumable: public Items {
 public:
    int AddHealth;          // Amount to add to player health
    int AddMana;            // Amount to add to player mana

    // Constructor for consumable vector
    Consumable(int _ItemID, std::string _ItemName, ItemType _Type, std::string _ItemDesc,  int _AddHealth, int _AddMana)
        : Items(_ItemID, _ItemName, _Type, _ItemDesc), AddHealth(_AddHealth), AddMana(_AddMana) {}
};


// Vector to store all misc items
//
// ID, ItemName, ItemType, ItemDescription
std::vector<Items> misc = {
    {000, "Empty", ItemType::Misc, "There is nothing here"},
    {001, "Dungeon Key", ItemType::Misc, "A rather large heavy metal key."},
    {002, "Lockpick", ItemType::Misc, "A tool for nefarious purposes."},
    {003, "Bucket", ItemType::Misc, "It's a bucket...There's a hole in it"}
}; // ID count 000 - 099                                               


// Vector to store all weapon items
//
// ID, ItemName, ItemType, ItemDescription, 
// Damage, MagicDamage
std::vector<Weapon> weapons = {
    {101, "Stick", ItemType::Weapon, "A sturdy stick", 
            2, 0    },
    {102, "Tree Branch", ItemType::Weapon, "A recently fallen branch, looks likes a good walking stick", 
            1, 1    },
    {103, "Fairy Wand", ItemType::Weapon, "It is a wand...Just really small and useless", 
            0, 2    }
};// ID count 100 - 199


// Vector to store all armor items
//
// ID, ItemName, ItemType, ItemDescription, 
// MaxHealth, MaxMana, Defence, MagicDefence
std::vector<Armor> armors = {
    { 201, "Generic Robes", ItemType::Armor, "Basic looking robes", 
            0, 5, 0, 1  },
    { 202, "Generic Leather Armor", ItemType::Armor, "Armor fashioned with basic leather", 
            0, 0, 2, 0  },
    { 203, "Generic Cloth Armor", ItemType::Armor, "It's hard to call it armor, but it does cover you", 
            0, 0, 1, 1  }
}; // ID count 200 - 299


// Vector to store all accessory items
//
// ID, ItemName, ItemType, ItemDescription, 
// MaxHealth, MaxMana,   Damage, MagicDamage,   Defence, MagicDefence
std::vector<Accessory> accessories = {
    { 301, "Red Wristband", ItemType::Accessory, "A very flashy and cool looking wristband", 
            0, 0,   0, 0,   0, 0    },
    { 302, "Fingerless Glove", ItemType::Accessory, "Gloves with the finger torn off",
            0, 0,   0, 0,   1, 0    },
    { 303, "Lover's Pendant", ItemType::Accessory, "A sentimental token from your soul mate",
            25, 0,  0, 0,   0, 0    },
    { 304, "Magic Paper", ItemType::Accessory, "A single sheet of magical paper",
            0, 5,   0, 1,   0, 0    }
}; // ID count 300 - 399


// Vectore to store all consumable items
//
// ID, ItemName, ItemType, ItemDescription, 
// AddHealth, AddMana
std::vector<Consumable> consumables = {
    { 401, "Small Health Potion", ItemType::Consumable, "A small vial of red liquid", 
            50, 0   },
    { 402, "Health Potion", ItemType::Consumable, "A flask filled with red liquid",
            100, 0  },
    { 403, "Small Mana Potion", ItemType::Consumable, "A small vial of blue liquid", 
            0, 20   },
    { 404, "Mana Smoothie", ItemType::Consumable, "A smoothie made of mana banana", 
            50, 10  },
    { 405, "Bread", ItemType::Consumable, "Dry bread", 
            25, 0   },
    { 406, "Milk", ItemType::Consumable, "Fresh cow's milk", 
            0, 10   }
}; // ID count 400 - 499


} // Ending namespace ItemList

#endif // This is needed for header files 
