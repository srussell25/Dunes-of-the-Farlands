// Add necessary includes & imports here
#include "catch.hpp"
#include <iostream>
#include <algorithm>

// Including every header file we made for the project
#include "ui.hpp"
#include "parser.hpp"
#include "gameobjects.hpp"
#include "objectactions.hpp"
#include "actions.hpp"

// Class containing all info about the player; should be instanced upon game start.
class player_info 
{
    // TODO: Replace any marked strings (the ones with asterisks) with references to 
    //       gameObjects instead once gameObjects is implemented
    private:
        std::string location; // *
        std::vector<std::string> inventory = {}; // *
        std::vector<std::string> flags = {};
        std::vector<std::string>::iterator invIter; // *
        std::vector<std::string>::iterator flagIter;
        bool isAlive = true;
    public:
        void setLocation(std::string loc) // *
        {
            location = loc;
        }
        std::string getLocation() // *
        {
            return location;
        }
        void addItem(std::string item) // *
        {
            inventory.insert(inventory.end(), item);
        }
        void removeItem(std::string item) // *
        {
            invIter = std::find(inventory.begin(), inventory.end(), item);
            inventory.erase(invIter);
        }
        std::string findItem(std::string item) 
        {
            return *std::find(inventory.begin(), inventory.end(), item);
        }
        void addFlag(std::string flag) 
        {
            flags.insert(flags.end(), flag);
        }
        void removeFlag(std::string flag) 
        {
            flagIter = std::find(flags.begin(), flags.end(), flag);
            flags.erase(flagIter);
        }
        std::string findFlag(std::string flag) 
        {
            return *std::find(flags.begin(), flags.end(), flag);
        }
        bool getPlayerState()
        {
            return isAlive;
        }
        void setPlayerState(bool state)
        {
            isAlive = state;
        }
};

int main()
{
    // TODO: Check if the player is alive in the game loop; if not (due to a gameplay event), re-instance this variable and restart the game 
    player_info player;
    
    // TODO: Replace std::string with gameObject for currentObject once gameObject is implemented
    std::string currentAction;
    std::string currentGameObject;

    // Title card
    std::cout <<"DUNES OF THE FARLANDS"<<std::endl<<"====================="<<std::endl<<std::endl;
    
    std::cout<<"Enter any key to start" << std::endl;

    // This is to make the execution wait until the user inputs any character
    std::string startSeq;
    startSeq = getInput();

    while(true)
    {
        // Function to display current story event
        // unimplemented
      
        // Gets player input to story event
        std::string input;
        input = getInput();

        // Simply converts input into uppercase for easy matching
        std::transform(input.begin(), input.end(), input.begin(), ::toupper);
        
        // Parse input
        if (input == "EXIT")
        {
            if (exitSeq() == true)
            {
                exit(0);
            }
            else
            {
                std::cin.ignore();
            }
        }
    }
  
    return 0;
}