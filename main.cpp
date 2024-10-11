
#include<iostream>
#include<iomanip>
#include<string>        // To work with multiple words
#include<cmath>         // Math function | abs()
#include<vector>        // Vector for inventory
#include<limits>        // Limit - cin.ingore() modifier
#include"ItemList.h"    // All items stored in vectors
#include"BaseStats.h"   // Base stats for player and enimies
using namespace std;


// Creating namespace for my functions 
// so anyone can reuse names
namespace Devine{ // Functions made by Devin

 // More information of each function below the int main

 void Title(const string title, const int width); 
 void sTitle(const string title, const int width); 
 void Pause(const int width);
 void PageBreak(const char fill, const int width);

 void AddHealthMana(const int Health, const int Mana, BaseStats::Player& P);
 void MinusHealth(const int Minus, BaseStats::Player& P, bool Alive);
 void AttributeMOD(const int MaxHealth, const int MaxMana, const int Damage,
    const int MDam, const int Defence, const int MDef, BaseStats::Player& P);

 void AddItem(const int ItemID, vector<int>& Inventory);
 void RemoveItem(const int ItemID, vector<int>& Inventory); 
 string ItemName(const int ItemID);
 bool InventoryFull(const BaseStats::Player& P, const vector<int>& Inventory);

 void EquipItem(const int ItemID, vector<int>& Inventory, BaseStats::Player& P);
 void unEquipItem(const int ItemID, vector<int>& Inventory, BaseStats::Player& P);

 bool YESno();
 bool NOyes();

 int MainMenu(vector<int>& Inventory, BaseStats::Player& P);

}
















int main(){

 //Only three varibles are not in my namespace
 BaseStats::Player player; // Class that holds all player stats
 bool Alive = true; // Bool to determine player is alive
 vector<int> Inventory; // Vector for holding inventory items in the form of ItemIDs

 
    Devine::Title(" Evil Powers of Enderwind ", 80);
    Devine::Pause(80);
    cout << "\nThank you for your interest in applying to\n"
         << "the Enderwind Adventure's Guild!\n"
         << "Please fill out the questionaire\n";
    Devine::PageBreak('-',40);
    cout << "What is your name?\n";

    getline(cin, player.Name); // Name input, getline used To input more than one word
    Devine::PageBreak('-',40);

 // I used labels and goto statements to return on invalid choices
 // These could be replaced with a do while statement but I don't wanna

 InvalidRaceChoice:     // Label to return on invalid race choice
    cout << "What is your race?\n"
         << "Human, Giant, Dryad, Elf, Tree\n"; 
    cin >> player.RaceName; // Race input
    Devine::PageBreak('-',40);
    if (player.RaceName == "Human" || player.RaceName == "human" || 
        player.RaceName == "H" || player.RaceName == "h"){
        cout << "The boring choice. Humans excel at being okay\n"
             << "at everything and great at nothing.\n" 
             << "\nDo you want to play as a human?\n";
        if (!Devine::YESno()){Devine::PageBreak('-',40); goto InvalidRaceChoice;}
        player.RaceName = "Human";
        Devine::AttributeMOD(0,0,1,1,1,1,player);
    }
    else if
       (player.RaceName == "Giant" || player.RaceName == "giant" || 
        player.RaceName == "G" || player.RaceName == "g"){
        cout << "The comically large human. Giants are your\n"
             << "go-to for flattening small countries.\n" 
             << "\nDo you want to play as a giant?\n";
        if (!Devine::YESno()){Devine::PageBreak('-',40); goto InvalidRaceChoice;}
        player.RaceName = "Giant";
        Devine::AttributeMOD(100,-20,3,-2,3,0,player);
    }
    else if
      (player.RaceName == "Dryad" || player.RaceName == "dryad"|| 
        player.RaceName == "D" || player.RaceName == "d"){
        cout << "The spirit of the forrest. Dryads are fairly\n" 
             << "competent, when they're not hugging trees.\n"
             << "\nDo you want to play as a dryad?\n";
        if (!Devine::YESno()){Devine::PageBreak('-',40); goto InvalidRaceChoice;}
        player.RaceName = "Dryad";
        Devine::AttributeMOD(25,5,1,1,0,0,player);
    }
    else if
      (player.RaceName == "Elf" || player.RaceName == "elf"|| 
        player.RaceName == "E" || player.RaceName == "e"){
        cout << "Masters of magic. Elves' hobbies include looking at\n"
             << "themselves and not sharing they're magical secrets.\n" 
             << "\nDo you want to play as a elf?\n";
        if (!Devine::YESno()){Devine::PageBreak('-',40); goto InvalidRaceChoice;}
        player.RaceName = "Elf";
        Devine::AttributeMOD(-20,10,-1,2,0,1,player);
    }
    else if
      (player.RaceName == "Tree" || player.RaceName == "tree"|| 
        player.RaceName == "T" || player.RaceName == "t"){
        cout << "Literally a tree. Not sure how you got here, but\n"
             << "you are here now. At least trees don't fell much.\n" 
             << "\nDo you want to play as a tree?\n";
        if (!Devine::YESno()){Devine::PageBreak('-',40); goto InvalidRaceChoice;}
        player.RaceName = "Tree";
        Devine::AttributeMOD(50,5,0,0,2,2,player);
    }
    else{
        cout << "This is an invalid choice\n";
        Devine::PageBreak('-',40);
        goto InvalidRaceChoice;
    }
    
    Devine::PageBreak('-',40);    

 InvalidBackgroundChoice:   // Label to return on invalid background choice
    cout << "Who were you before?\n"
         << "Bully, Lover, Explorer, Useless\n"; 
    cin >> player.Background; // Background input
    Devine::PageBreak('-',40);

    if (player.Background == "Bully" || player.Background == "bully"|| 
        player.Background == "B" || player.Background == "b"){
        cout << "You spent your early years perfecting the art of\n"
             << "being a jerk. Why would you do that?\n" 
             << "\nDo you want to play as a bully?\n";
        if (!Devine::YESno()){Devine::PageBreak('-',40); goto InvalidBackgroundChoice;}
        player.Background = "Bully";
        Devine::AttributeMOD(10,0,1,0,1,0,player); 
        Devine::PageBreak('-',40);
        Devine::AddItem(302,Inventory); // Adding Fingerless Gloves to inventory
    }
    else if
       (player.Background == "Lover" || player.Background == "lover"|| 
        player.Background == "L" || player.Background == "l"){
        cout << "You eloped with the daughter of a rival family.\n" 
             << "After tragedy struck, you're left lost and alone.\n"
             << "\nDo you want to play as a lover?\n";
        if (!Devine::YESno()){Devine::PageBreak('-',40); goto InvalidBackgroundChoice;}
        player.Background = "Lover";
        Devine::AttributeMOD(10,5,0,0,0,1,player);
        Devine::PageBreak('-',40);
        Devine::AddItem(303,Inventory); // Adding Lover's Pendant to inventory
    }
    else if
       (player.Background == "Explorer" || player.Background == "gnome"|| 
        player.Background == "E" || player.Background == "e"){
        cout << "Some call you the Cave Explorer. There is no\n" 
             << "place that you refuse to go and everyone knows.\n"
             << "\nDo you want to play as an explorer?\n";
        if (!Devine::YESno()){Devine::PageBreak('-',40); goto InvalidBackgroundChoice;}
        player.Background = "Explorer";
        Devine::AttributeMOD(0,0,1,1,0,0,player);
        Devine::PageBreak('-',40);
        Devine::AddItem(304,Inventory); // Adding Magic Paper to inventory
    }
    else if
      (player.Background == "Useless" || player.Background == "useless"|| 
        player.Background == "U" || player.Background == "u"){
        cout << "You were pretty much deemed useless in everything\n" 
             << "that you have tried. Better luck in the next life.\n"
             << "\nDo you want to play as a nobody?\n";
        if (!Devine::YESno()){Devine::PageBreak('-',40); goto InvalidBackgroundChoice;}
        player.Background = "Useless";
        Devine::AttributeMOD(-10,-5,-1,-1,0,0,player);
        Devine::PageBreak('-',40);
        Devine::AddItem(301,Inventory); // Adding Red Wristband to inventory
    }
    else{
        cout << "This is an invalid choice\n";
        goto InvalidBackgroundChoice;
    }

    Devine::PageBreak('-',40);
    cin.ignore();       // sometimes required for Devine::Pause() function to work
    Devine::Pause(40);  // Press enter to continue function

 InvalidProfessionChoice:       // Label to return on invalid profession choice
    cout << "What is your profession?\n"
         << "Warrior, Spellsword, Mage\n"; 
    cin >> player.Profession;
    Devine::PageBreak('-',40);

    if (player.Profession == "Warrior" || player.Profession == "warrior"|| 
        player.Profession == "W" || player.Profession == "w"){
        cout << "You solve problems with a big sword. Not a single\n" 
             << "whole person has disagreed with you.\n"
             << "\nDo you want to play as a warrior?\n";
        if (!Devine::YESno()){Devine::PageBreak('-',40); goto InvalidProfessionChoice;}
        player.Profession = "Warrior";
        Devine::AttributeMOD(25,-5,2,-1,1,0,player);
        Devine::PageBreak('-',40);
        Devine::AddItem(202,Inventory); // Adding Generic Leather Armor to inventory
        Devine::AddItem(101,Inventory); // Adding Stick to inventory
    }
    else if
       (player.Profession == "Spellsword" || player.Profession == "spellsword"|| 
        player.Profession == "S" || player.Profession == "s"){
        cout << "Can’t decide between stabbing things or setting\n"
             << "them on fire? Why not both?\n" 
             << "\nDo you want to play as a spellsword?\n";
        if (!Devine::YESno()){Devine::PageBreak('-',40); goto InvalidProfessionChoice;}
        player.Profession = "Spellsword";
        Devine::AttributeMOD(0,0,1,1,0,0,player);
        Devine::PageBreak('-',40);
        Devine::AddItem(203,Inventory); // Adding Generic Cloth Armor to inventory
        Devine::AddItem(102,Inventory); // Adding Tree Branch to inventory
    }
    else if
       (player.Profession == "Mage" || player.Profession == "mage"|| 
        player.Profession == "M" || player.Profession == "m"){
        cout << "The taste of magic makes you power hungery for more.\n" 
             << "Will you ever be satisfied with your destruction?\n"
             << "\nDo you want to play as an mage?\n";
        if (!Devine::YESno()){Devine::PageBreak('-',40); goto InvalidProfessionChoice;}
        player.Profession = "Mage";
        Devine::AttributeMOD(-20,10,-2,2,0,1,player);
        Devine::PageBreak('-',40);
        Devine::AddItem(201,Inventory); // Adding Generic Robes to inventory
        Devine::AddItem(103,Inventory); // Adding Fairy Wand to inventory
    }
    else{
        cout << "This is an invalid choice\n";
        Devine::PageBreak('-',40);
        goto InvalidProfessionChoice;
    }
    
    if (player.MaxMana < 0){player.MaxMana = 0;}    // Checking for any negatives numbers
    if (player.Damage < 0){player.Damage = 0;}      // after Attribute changes and 
    if (player.MDam < 0){player.MDam = 0;}          // setting them to 0 instead
    if (player.Defence < 0){player.Defence = 0;}
    if (player.MDef < 0){player.MDef = 0;}
    player.Health = player.MaxHealth;               
    player.Mana = player.MaxMana;

    Devine::PageBreak('-',40);
    cin.ignore();
    Devine::Pause(0);

    int menu = Devine::MainMenu(Inventory,player);




























































    /* 
     You can use this after Devine::MinusHealth() to end the game if dead
        if (!Alive){goto ENDGAME;}
    */


 
 ENDGAME:   // Label so you can use the goto() function to end the game
    cout << "\n";
    Devine::Title(" End of Game ", 80);
    cin.ignore();
    Devine::Pause(80);
    cout << "\n";
    Devine::sTitle(" Credits ", 60);
    cout << "\n"
         << " ---- Programers ---- \n"
         << "Stage 1: Devin Foster\n"
         << "Stage 2: YourName\n"           // Enter your names
         << "Stage 3: YourName\n\n";
    Devine::Pause(80);
    
 return 0;

} // End of Int main() 





















// Functions made by Devin - content
namespace Devine{ 

    // Function to print title block
    void Title(const string title, const int width){
     cout << setfill ('-') << setw (width) << "\n" 
          << setw (title.size()/2+width/2) << title << setw (width/2-title.size()/2) << "\n" 
          << setw (width) << "\n" << setfill (' ');
    }

    // Function to print small title block
    void sTitle(const string title, const int width){
     cout << setfill ('-') << setw (title.size()/2+width/2) << title << setw (width/2-title.size()/2) << "\n" << setfill (' ');
    }

    // Funcion to stop the program with a useless input
    // so that players can read and continue at will
    void Pause(const int width){
     cout << "Press Enter to continue  ";
     cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
     cout << setfill('-') << setw(width) << "\n" << setfill(' ');
    } // Function has issue that sometimes requires an extra 
      // cin.ignore for it to function correctly

    // Function to fill line with a char
    void PageBreak(const char fill, const int width){
     cout << setfill(fill) << setw(width) << "\n" << setfill(fill);
    }

    // Function to add health to player
    void AddHealthMana(const int Health, const int Mana, BaseStats::Player& P){
        P.Health += Health;
        P.Mana += Mana;
        if (P.Health > P.MaxHealth){
            P.Health = P.MaxHealth;
        }
        if (P.Mana > P.MaxMana){
            P.Mana = P.MaxMana;
        }
    }

    // Function to remove health from the player
    void MinusHealth(const int Minus, BaseStats::Player& P, bool Alive){
        P.Health -= Minus;
        if (P.Health <= 0){
            cout << "You have died\n";
            bool Alive = false;
        }
    }

    // Function to modify player attributes 
    void AttributeMOD(const int MaxHealth, const int MaxMana, const int Damage,
      const int MDam, const int Defence, const int MDef, BaseStats::Player& P){
        P.MaxHealth += MaxHealth; P.MaxMana += MaxMana; P.Damage += Damage;
        P.MDam += MDam; P.Defence += Defence; P.MDam += MDef;
    }

    // Function to add item to inventory
    void AddItem(const int ItemID, vector<int>& Inventory){
        Inventory.push_back(ItemID);
        cout << ItemName(ItemID) << " added to your inventory\n";
    }

    // Function to remove item from inventory
    void RemoveItem(const int ItemID, vector<int>& Inventory){
        for (vector<int>::iterator i = Inventory.begin(); i != Inventory.end(); i++){
            if (*i == ItemID){
                Inventory.erase(i);
                cout << ItemName(ItemID) << " removed from inventory\n";
                return;
            }
        }
    }

    // Function to retrieve name of item
    string ItemName(const int ItemID){

        int ItemType = ItemID/100;

        switch(ItemType){
            case 0:
                for (const ItemList::Items& misc : ItemList::misc) {
                    if (misc.ItemID == ItemID) {return misc.ItemName;}
                }
                break;
            case 1:
                for (const ItemList::Weapon& weapon : ItemList::weapons) {
                    if (weapon.ItemID == ItemID) {return weapon.ItemName;}
                }
                break;
            case 2:
                for (const ItemList::Armor& armor : ItemList::armors) {
                    if (armor.ItemID == ItemID) {return armor.ItemName;}
                }
                break;
            case 3:
                for (const ItemList::Accessory& accessory : ItemList::accessories) {
                    if (accessory.ItemID == ItemID) {return accessory.ItemName;}
                }
                break;
            case 4:
                for (const ItemList::Consumable& consumalbe : ItemList::consumables) {
                    if (consumalbe.ItemID == ItemID) {return consumalbe.ItemName;}
                }
        }
        return "Empty";
    }

    // Function to print item details
    void ItemDetail(const int ItemID){

        int ItemType = ItemID/100;

        switch(ItemType){
            case 0:
                for (const ItemList::Items& misc : ItemList::misc) {
                    if (misc.ItemID == ItemID) {
                        cout << "  ---- " << misc.ItemName << " ----\n"
                             << misc.ItemDesc << "\n";
                        break;
                    }
                }
            case 1:
                for (const ItemList::Weapon& weapon : ItemList::weapons) {
                    if (weapon.ItemID == ItemID) {
                        cout << "  ---- " << weapon.ItemName << " ----\n"
                             << "Weapon     Damage: " << weapon.Damage << "     Magic Damage: " << weapon.MDam << "\n"
                             << weapon.ItemDesc << "\n";
                        break;
                    }
                }
            case 2:
                for (const ItemList::Armor& armor : ItemList::armors) {
                    if (armor.ItemID == ItemID) {
                        cout << "  ---- " << armor.ItemName << " ----\n"
                             "Armor     Defence: " << armor.Defence << "     Magic Defence: " << armor.MDef << "\n"
                             << "Max Health: " << armor.MaxHealth << "     Max Mana: " << armor.MaxMana << "\n"
                             << armor.ItemDesc << "\n";
                        break;
                    }
                }
            case 3:
                for (const ItemList::Accessory& accessory : ItemList::accessories) {
                    if (accessory.ItemID == ItemID) {
                        cout << "  ---- " << accessory.ItemName << " ----\n"
                             << "Accessory     Damage: " << accessory.Damage << "     Magic Damage: " << accessory.MDam << "\n"
                             << "Defence: " << accessory.Defence << "     Magic Defence: " << accessory.MDef << "\n"
                             << "Max Health: " << accessory.MaxHealth << "     Max Mana: " << accessory.MaxMana << "\n"
                             << accessory.ItemDesc << "\n";
                        break;
                    }
                }
            case 4:
                for (const ItemList::Consumable& consumalbe : ItemList::consumables) {
                    if (consumalbe.ItemID == ItemID) {
                        cout << "  ---- " << consumalbe.ItemName << " ----\n"
                             << "Consumable     Add Health: " << consumalbe.AddHealth << "     Add Mana: " << consumalbe.AddMana << "\n"
                             << consumalbe.ItemDesc << "\n";        
                    }
                }
        }
        cin.ignore();          
        Devine::PageBreak('-',40);
        Pause(60);
    }

    // Function to check if the Inventory is full 
    bool InventoryFull(const BaseStats::Player& P, const vector<int>& Inventory){
        if (Inventory.size() >= P.BagSize ){return true;}
        return false;
    }

    // Function to move inventory item to equipped 
    void EquipItem(const int ItemID, vector<int>& Inventory, BaseStats::Player& P){
        int ItemType = ItemID/100;
        switch(ItemType){
            case 1:
                if (P.EquippedWeapon == 0){
                    RemoveItem(ItemID,Inventory);
                    P.EquippedWeapon = ItemID;
                    for (const ItemList::Weapon& weapon : ItemList::weapons) {
                        if (weapon.ItemID == ItemID) {
                            AttributeMOD(0,0, weapon.Damage, weapon.MDam, 0,0, P);
                            cout << weapon.ItemName << " equipped\n";
                        }                            
                    }
                } else {cout << "Uneqiup your weapon first";}
                break;
            case 2:
                if (P.EquippedArmor == 0){
                    RemoveItem(ItemID,Inventory);
                    P.EquippedArmor = ItemID;
                    for (const ItemList::Armor& armor : ItemList::armors) {
                        if (armor.ItemID == ItemID) {
                            AttributeMOD(armor.MaxHealth, armor.MaxMana, 0,0, armor.Defence, armor.MDef, P);
                            cout << armor.ItemName << " equipped\n";
                        }                            
                    }
                } else {cout << "Uneqiup your armor first";}
                break;
            case 3:
                if (P.EquippedAccessory == 0){
                    RemoveItem(ItemID,Inventory);
                    P.EquippedAccessory = ItemID;
                    for (const ItemList::Accessory& accessory : ItemList::accessories) {
                        if (accessory.ItemID == ItemID) {
                            AttributeMOD(accessory.MaxHealth, accessory.MaxMana, accessory.Damage, accessory.MDam, accessory.Defence, accessory.MDef, P);
                            cout << accessory.ItemName << " equipped\n";
                        }                            
                    }
                } else {cout << "Uneqiup your accessory first";}
                break;
            default: cout << "Invalid item type | Item must be a weapon, armor, or accessory\n";
        }
    }

    // Function to move equipped item to inventory
    void unEquipItem(const int ItemID, vector<int>& Inventory, BaseStats::Player& P){
        if (!InventoryFull(P,Inventory)){
            int ItemType = ItemID/100;
            switch(ItemType){
                case 1:
                    P.EquippedWeapon = 0;
                    for (const ItemList::Weapon& weapon : ItemList::weapons) {
                        if (weapon.ItemID == ItemID) {
                            AttributeMOD(0,0, -weapon.Damage, -weapon.MDam, 0,0, P);
                        }                            
                    }
                    break;
                case 2:
                    P.EquippedArmor = 0;
                    for (const ItemList::Armor& armor : ItemList::armors) {
                        if (armor.ItemID == ItemID) {
                            AttributeMOD(-armor.MaxHealth, -armor.MaxMana, 0,0, -armor.Defence, -armor.MDef, P);
                        }                            
                    }
                    break;
                case 3:
                    P.EquippedAccessory = 0;
                        for (const ItemList::Accessory& accessory : ItemList::accessories) {
                            if (accessory.ItemID == ItemID) {
                                AttributeMOD(-accessory.MaxHealth, -accessory.MaxMana, -accessory.Damage, -accessory.MDam, -accessory.Defence, -accessory.MDef, P);
                            }                            
                        }
            }  
            cout << ItemName(ItemID) << " unequipped\n";
            AddItem(ItemID,Inventory);
        } else {cout << "Inventory is full | Discard items to make room";}
    }

    // Function to take yes or no input | invalid input = false
    bool YESno(){
        string answer;
        cout << "y/n: ";
        cin >> answer;
        if (answer == "Yes" || answer == "yes" || answer == "Ye" || answer == "ye" ||
            answer == "Y" || answer == "y" || answer == "Yea" || answer == "yea" ||
            answer == "Ya" || answer == "ya"){
                return true;
            }
        return false;
    }

    // Function to take yes or no input | invalid input = true
    bool NOyes(){
        string answer;
        cout << "y/n: ";
        cin >> answer;
        if (answer == "No" || answer == "no" || answer == "N" || answer == "n" ||
            answer == "Na" || answer == "na" ){
                return false;
            }
        return true;
    }

    // Function for the main menu loop
    // 
    // The player stats and inventory loop until exit
    // All other options return an int 
    // For now: exit returns 0, Enderwind returns 1, and Other returns 2
    int MainMenu(vector<int>& Inventory, BaseStats::Player& P){
        bool Exit = false;
        do{
            string input = " ";
            Devine::PageBreak('*',80);
            Devine::sTitle("  Main Menu  ",60);
            cout << P.Name << "     Inventory     Enderwind     Other     exit\n";
            getline(cin, input);
            if (input == P.Name || input == "Character" || input == "character"){
                Devine::PageBreak('*',80);
                Devine::sTitle(("  " + P.Name + "  "),60);
                cout << "Race: " << P.RaceName << "     Background: " << P.Background << "     Profession: " << P.Profession << "\n"
                     << "Level: " << P.Level << "\n" 
                     << "Health: " << P.Health << "/" << P.MaxHealth << "     Mana: " << P.Mana << "/" << P.MaxMana << "\n"
                     << "Damage: " << P.Damage << "     Magic Damage: " << P.MDam << "\n"
                     << "Defence: " << P.Defence << "     Magic Defence: " << P.MDef << "\n";
            }
            else if (input == "Inventory" || input == "inventory" || input == "I" ||
                     input == "i"){
                Exit = false;
                do{ 
                    Devine::PageBreak('*',80);
                    Devine::sTitle(("  Inventory  "),60);
                    int count = 0;
                    int Slot = 1;
                    for (vector<int>::iterator i = Inventory.begin(); i != Inventory.end(); i++,count++,Slot++){
                        switch(count){
                            case 0:
                                cout << Slot << " " << ItemName(*i);
                                break;
                            case 1:
                                cout << setw(5) << Slot << " " << ItemName(*i);
                                break;
                            case 2: 
                                cout << setw(5) << Slot << " " << ItemName(*i) << "\n";
                                count = -1;
                        }
                    }
                    for (int i = Inventory.size(); i < P.BagSize; i++, count++) {
                        switch (count) {
                            case 0:
                                cout << i + 1 << " Empty";
                                break;
                            case 1:
                                cout << setw(5) << i + 1 << " Empty";
                                break;
                            case 2:
                                cout << setw(5) << i + 1 << " Empty" << "\n";
                                count = -1;
                        }
                    }
                    if (count != 0){cout << "\n";}
                    cout << "Equipped Weapon: " << ItemName(P.EquippedWeapon) << "\n"
                         << "Equipped Armor: " << ItemName(P.EquippedArmor) << "\n"
                         << "Equipped Accessory: " << ItemName(P.EquippedAccessory) << "\n";
                    PageBreak('-',60);
                    cout << "Detail     Use     Equip     Unequip     Disard     Exit\n";
                    cin >> input;
                    if (input == "Detail" || input == "detail"){

                        int In;
                        cout << "Enter number 1-" << P.BagSize << ", 0 for Equipped: ";
                        cin >> In;    
                        In = abs(In);
                        if (In<=Inventory.size()){
                            switch (In){
                                case 0:
                                    cout << "1 Weapon     2 Armor     3 Accessory: ";
                                    cin >> input;
                                    Devine::PageBreak('-',40);
                                    if (input == "Weapon" || input == "weapon" || input == "1"){
                                        ItemDetail(P.EquippedWeapon);
                                    }
                                    else if (input == "Armor" || input == "armor" || input == "2"){
                                        Devine::PageBreak('-',40);
                                        ItemDetail(P.EquippedArmor);
                                    }
                                    else if (input == "Accessory" || input == "Accessory" || input == "3"){
                                        Devine::PageBreak('-',40);
                                        ItemDetail(P.EquippedAccessory);                                        
                                    }else {"Invalid Input\n";}
                                    break;
                                default:
                                    Devine::PageBreak('-',40);
                                    ItemDetail(Inventory[In-1]);
                            }
                        } else {"Invalid Input\n";}
                        input = "Detail";
                    }
                    else if (input == "Use" || input == "use"){
                        int In;
                        cout << "Enter number 1-" << P.BagSize << ": ";
                        cin >> In;
                        In = abs(In);
                        if (In<=Inventory.size()){
                            if (In/100 == 4){
                                for (const ItemList::Consumable& consumable : ItemList::consumables) {
                                    if (consumable.ItemID == Inventory[In-1]) {
                                        AddHealthMana(consumable.AddHealth, consumable.AddMana,P);
                                        RemoveItem(Inventory[In-1], Inventory);
                                    }                            
                                }
                            } else {cout << "You can only use consumables\n";}
                        } else {cout << "Invalid Input\n";}
                    }
                    else if (input == "Equip" || input == "equip" || input == "E" || 
                             input == "e" ){

                        int In;
                        cout << "Enter number 1-" << P.BagSize << ": ";
                        cin >> In;
                        Devine::PageBreak('-',40);
                        In = abs(In);
                        if (In<=Inventory.size()){
                             EquipItem(Inventory[In-1], Inventory, P);
                        }else{cout << "Invalid Input\n";}
                    }
                    else if (input == "Unequip" || input == "unequip"){
                        cout << "1 Weapon     2 Armor     3 Accessory: ";
                        cin >> input;
                        Devine::PageBreak('-',40);
                        if (input == "Weapon" || input == "weapon" || input == "1"){
                            unEquipItem(P.EquippedWeapon,Inventory,P);
                        }
                        else if (input == "Armor" || input == "armor" || input == "2"){
                            unEquipItem(P.EquippedArmor,Inventory,P);
                        }
                        else if (input == "Accessory" || input == "Accessory" || input == "3"){
                            unEquipItem(P.EquippedAccessory,Inventory,P);                                        
                        }else {"Invalid Input\n";}
                    }                     
                    else if (input == "Discard" || input == "discard"){
                        int In;
                        cout << "Enter number 1-" << P.BagSize << ": ";
                        cin >> In;
                        In = abs(In);
                        if (In<=Inventory.size()){
                             RemoveItem(Inventory[In-1],Inventory);
                        } else {cout << "Invalid Input\n";}
                    }
                    else if (input == "Exit" || input == "exit" || input == "Back" ||
                     input == "back" ){
                        Exit = true;
                    } else {cout << "Invalid Input\n";}
                    
                    input = "Inventory";
                } while (Exit == false);
                Exit = false;
            }
            else if (input == "Enderwind" || input == "enderwind" || input == "Map" ||
                     input == "map" || input == "M" || input == "m" ){
                
                cout << "This feature is not made yet\n";
                return 1;
            }
            else if (input == "Other"){
                cout << "This feature is not made yet\n";
                return 2;
            }
            else if (input == "Exit" || input == "exit" || input == "Back" ||
                     input == "back" ){
                        return 0;
            }else {cout << "Invalid Input\n";}
            cin.ignore();
            Pause(60);
        }while(Exit == false);
     return 0;
    }



}
