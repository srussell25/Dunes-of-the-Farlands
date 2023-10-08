// Add necessary includes & imports here
#include <iostream>
#include "catch.hpp"
#include <string>

//  Including files from other parts of the project
#include "main.cpp"
#include "objectactions.hpp"

//  All of these are items/weapons that can get in game; some are placeholder items.
//  The default state of the items are false unless you start the game with them.

class items 
{
    public:
    std::string item_description = "description goes here";
    void use(T parsedObject)
    {

    }
    void take(T parsedObject)
    {

    }
    void look(T parsedObject)
    {

    }
    void examine(T parsedObject)
    {

    }
    void open(T parsedObject)
    {

    }
    void read(T parsedObject)
    {

    }
    void throw(T parsedObject)
    {

    }
    void unlock(T parsedObject)
    {

    }
    void put(T parsedObject)
    {

    }
}

items sword;
items sheild;
items potion;
items key;
items chest;
items note;
 
class locations
{
    public:
    std::string location_description = "description goes here";
    void go_to(T parsedObject)
    {

    }
    void look(T parsedObject)
    {

    }
    void leave(T parsedObject)
    {

    }
    void examine(T parsedObject)
    {
    
    }
}

bool has_seen_location = false; // used for if we want a big explination of a area and we move player back and forth from locations
locations town;
locations cave;
locations tavern;

class characters 
{
    public:
    std::string charcter_description = "description goes here";
    void look(T parsedObject)
    {

    }
    void examine(T parsedObject)
    {

    }
    void attack(T parsedObject)
    {

    }
    void talk_to(T parsedObject)
    {

    }
}

characters bandit;
