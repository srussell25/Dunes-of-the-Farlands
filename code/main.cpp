//  Add necessary includes & imports here
#include <iostream>
#include "catch.hpp"

//  Including every header file we made for the project
#include "ui.hpp"
#include "parser.hpp"
#include "gameobjects.hpp"
#include "objectactions.hpp"
#include "actions.hpp"

//  TODO: Replace template with actual types once types are defined
//  Struct containing all info about the player; should be instanced upon game start.
template <typename T>
class player_info 
{
    private:
        T location;
        std::set<T> inventory = {};
        std::set<T> flags = {};

    public:
        void setLocation(T loc) 
        {
            location = loc;
        }
        T getLocation() 
        {
            return location;
        }
        void addItem(T item) 
        {
            inventory.add(item);
        }
        void removeItem(T item) 
        {
            inventory.erase(item);
        }
        T findItem(T item) 
        {
            return inventory.find(item);
        }
        void addFlag(T flag) 
        {
            flags.add(flag);
        }
        void removeFlag(T flag) 
        {
            flags.erase(flag);
        }
        T findFlag(T flag) 
        {
            return flags.find(flag);
        }
};

//  TODO: Replace template with actual types once types are defined
template <typename T>
int main()
{
    std::cout << "Hello from the project starter code!\n";
    
    player_info<T> player;
    T parsedAction;
    T parsedObject;
    
    return 0;
}