// Add necessary includes & imports here
#include <iostream>
#include <string>

// Generic starter code for each file
// all of these are items/weapons that can get in game. some are placehoder items.
// the default state of the items are false unless you start the game with them.
//weapons
bool has_sword = true;
bool has_sheild = true; 

//items

bool has_key = false;
bool hasP_potion = false;

//locations
/*player location can be a string that gets updated and checked for actions or
it can be a bunch off bool variables for every place that turn true when your their.*/ 

//  string player_location = ""; or bool place = false;(if not their),  place = true(if their)
bool has_seen_location = false; // used for if we want a big explination of a area and we move player back and forth from locations

//charcters 
// these can be bools for maybe if they are alive or in the current location.

bool example_guy = false;//could be dead or not in the current place your in

void function3()
{
    
    std::cout << "Function not yet implemented\n";
}