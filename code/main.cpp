// Add necessary includes & imports here
#include "catch.hpp"
#include <iostream>
#include <set>

// Including every header file we made for the project
#include "ui.hpp"
#include "parser.hpp"
#include "gameobjects.hpp"
#include "objectactions.hpp"
#include "actions.hpp"

// Class containing all info about the player; should be instanced upon game start.
class player_info 
{
    private:
        int location;

        // TODO: Replace "items" with generic gameObject class, replace flags with generic flags class
        std::set<items> inventory = {};
        std::set<items> flags = {};

    public:
        void setLocation(auto loc) 
        {
            location = loc;
        }
        auto getLocation() 
        {
            return location;
        }
        void addItem(auto item) 
        {
            inventory.insert(item);
        }
        void removeItem(auto item) 
        {
            inventory.erase(item);
        }
        auto findItem(auto item) 
        {
            return inventory.find(item);
        }
        void addFlag(auto flag) 
        {
            flags.insert(flag);
        }
        void removeFlag(auto flag) 
        {
            flags.erase(flag);
        }
        auto findFlag(auto flag) 
        {
            return flags.find(flag);
        }
};

int main()
{
    // TODO: Check if the player is alive in the game loop; if not (due to a gameplay event), re-instance this variable and restart the game 
    player_info player;
    
    // TODO: Make generic gameAction class and gameObject class, uncomment the below lines with these new classes
    //gameAction parsedAction;
    //gameObject parsedObject;

    // title card
    std::cout <<"DUNES OF THE FARLANDS"<<std::endl<<"====================="<<std::endl<<std::endl;
    
    std::cout<<"Enter any key to start" << std::endl;

    // this is just here to make the execution wait until the user inputs any character
    std::string startSeq;
    startSeq = getInput();

    while(true)
    {
        // function to display current story event
        //unimplemented
      
        // gets player input to story event
        std::string input;
        input = getInput();

        // simply converts input into uppercase for easy matching
        std::transform(input.begin(), input.end(), input.begin(), ::toupper);
        
        // parse input
        if (input == "EXIT")
        {
            if (exitSeq() == true)
                exit(0);
            else
                std::cin.ignore();
        }
    }
  
    return 0;
}