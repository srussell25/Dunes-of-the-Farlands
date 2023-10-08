// Add necessary includes & imports here
#include "catch.hpp"
#include <iostream>
#include <string>

class items
{
    private:
        std::string item_description = "description goes here";
    public:
        std::string get_description() 
        {
            return item_description;
        }
        void use(auto parsedObject)
        {
            // unimplemented
        }
        void take(auto parsedObject)
        {
            // unimplemented
        }
        void look(auto parsedObject)
        {
            // unimplemented
        }
        void examine(auto parsedObject)
        {
            // unimplemented
        }
        void open(auto parsedObject)
        {
            // unimplemented
        }
        void read(auto parsedObject)
        {
            // unimplemented
        }
        void throwItem(auto parsedObject)
        {
            // unimplemented
        }
        void unlock(auto parsedObject)
        {
            // unimplemented
        }
        void put(auto parsedObject)
        {
            // unimplemented
        }
};

class locations
{
    private:
        std::string location_description = "description goes here";
        bool has_seen_location = false;
    public:
        std::string get_description() 
        {
            return location_description;
        }
        void go_to(auto parsedObject)
        {
            has_seen_location = true;
            // unimplemented
        }
        void look(auto parsedObject)
        {
            // unimplemented
        }
        void leave(auto parsedObject)
        {
            // unimplemented
        }
        void examine(auto parsedObject)
        {
            // unimplemented
        }
};

class characters 
{
    private:
        std::string charcter_description = "description goes here";
    public:
        std::string get_description() 
        {
            return charcter_description;
        }
        void look(auto parsedObject)
        {
            // unimplemented
        }
        void examine(auto parsedObject)
        {
            // unimplemented
        }
        void attack(auto parsedObject)
        {
            // unimplemented
        }
        void talk_to(auto parsedObject)
        {
            // unimplemented
        }
};

// example objects
items sword;
items sheild;
items potion;
items key;
items chest;
items note;

locations town;
locations cave;
locations tavern;

characters bandit;
