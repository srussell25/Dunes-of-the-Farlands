// Add necessary includes & imports here
#include <iostream>
#include <string>
#include "objectactions.hpp"
#include "main.cpp"
#include "catch.hpp"

// Generic starter code for each file
// all of these are items/weapons that can get in game. some are placehoder items.
// the default state of the items are false unless you start the game with them.
//items
class items {
    public:

    std::string item_description = "description goes here";


    void use(T parsedObject){

    }
    void take(T parsedObject){

    }
    void look(T parsedObject){

    }
    void examine(T parsedObject){

    }
    void open(T parsedObject){

    }
    void read(T parsedObject){

    }
    void Throw(T parsedObject){

    }
    void unlock(T parsedObject){

    }
    void put(T parsedObject){

    }

}
items sword;
items sheild;
items potion;
items key;
items chest;
items note;





//locations
 
class locations{
    std::string location_description = "description goes here";
    
    void go_to(T parsedObject){

    }
    void look(T parsedObject){

    }
    void leave(T parsedObject){

    }
    void examine(T parsedObject){

}

}

locations town;
locations cave;
locations tavern;


bool has_seen_location = false; // used for if we want a big explination of a area and we move player back and forth from locations

//characters

class characters {
    std::string charcter_description = "description goes here";

    void look(T parsedObject){

    }
    void examine(T parsedObject){

    }
    void attack(T parsedObject){

    }

    void talk_to(T parsedObject){

    }

}
characters bandit;





// Generic starter code for each file
int function3(int x)
{
    return x;

}