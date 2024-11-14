/*
This file has functions for the leveling 
mechanics and misc formatting
*/

#include <iostream>
#include "D_Misc.hpp"
#include "Player.hpp"
using namespace std;


namespace Level{ 

    void GainExp(Player& P, const int amount){
        const int ExpCap = P.Level*50+50;
        P.Exp+=amount;
        cout << "You have gained " << amount << " Experience\n";
        if(P.Exp>=ExpCap){
            P.Exp=P.Exp%ExpCap;
            LevelUp(P);
        }
    }

    void LevelUp(Player& P){
        P.Level+=1;
        cout << "LEVEL UP\n"
             << "You are now Level " << P.Level << "\n";
    }   

} // Ending namespace Level


namespace Format{

    void PageBreak(){
        cout << "-------------------------------------------------------------\n"; 
    }

    void Pause(){
        cout << "Press Enter to continue  ";
        cin.ignore();cin.ignore();
    }

} // Ending namespace Format

