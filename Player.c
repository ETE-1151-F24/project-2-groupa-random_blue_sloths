#include <iostream>
#include "Player.h"
using namespace std;

Player::Player(const std::string& name) : Name(name), Type(0), Magic(0) {}

void Player::choosePlayerType() {
    cout << "Choose your player type:" << endl;
    cout << "0. Player1";
    cout << "1. Player2";
    int choice;
    cin >> choice;

    if (choice == 0) {
        Type = 0;
        Magic = 0;
    } else if (choice == 1) {
        Type = 1;
        Magic = 10;
    } else {
        std::cout << "Invalid choice, defaulting to Player1";
        Type = 0;
        Magic = 0;
    }
}

void Player::displayPlayerStats() {
    cout << "Player Name: " << Name << "\n";
    cout << "Player Type: ";
    if (Type == 0) {
        cout << "Player1";
    } else {
        cout << "Player2";
    }
    cout << "Magic: " << Magic << "\n";
}