/*
This file is used for declaring the map, 
leveling, and save mechanics. 
*/

// these is needed for header files 
#ifndef Devine_h 
#define Devine_h

#include<iostream>



namespace Map{ 

    class Location{
    public:
        int ID;
        string Name;
        bool Shop;
        bool Rest;

        Location(int _ID,string _Name,bool _Shop,bool _Rest)
            : ID(_ID),Name(_Name), Shop(_Shop), Rest(_Rest) {}
    };



} // Ending namespace Map



namespace Level{ 

    void Increase();


} // Ending namespace Level



namespace Save{
    

} // Ending namespace Save





#endif // This is needed for header files 
