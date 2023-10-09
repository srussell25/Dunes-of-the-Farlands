// Add necessary includes & imports here
#include "catch.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <tuple>

// Including every header file we made for the project
#include "ui.hpp"
#include "parser.hpp"
#include "gameobjects.hpp"
#include "objectactions.hpp"

// Class containing all info about the player; should be instanced upon game start.
class player_info 
{
    private:
        game_object currentLocation;
        std::vector<game_object> inventory = {};
        std::vector<std::string> flags = {};
        std::vector<game_object>::iterator invIter;
        std::vector<std::string>::iterator flagIter;
        bool isAlive = true;
    
    public:
        void set_location(game_object location)
        {
            currentLocation = location;
        }
        game_object get_location()
        {
            return currentLocation;
        }
        void add_item(game_object item)
        {
            inventory.insert(inventory.end(), item);
        }
        void remove_item(game_object item)
        {
            invIter = std::find(inventory.begin(), inventory.end(), item);
            inventory.erase(invIter);
        }
        game_object find_item(game_object item) 
        {
            return *std::find(inventory.begin(), inventory.end(), item);
        }
        void add_flag(std::string flag) 
        {
            flags.insert(flags.end(), flag);
        }
        void remove_flag(std::string flag) 
        {
            flagIter = std::find(flags.begin(), flags.end(), flag);
            flags.erase(flagIter);
        }
        std::string find_flag(std::string flag) 
        {
            return *std::find(flags.begin(), flags.end(), flag);
        }
        bool get_player_state()
        {
            return isAlive;
        }
        void set_player_state(bool state)
        {
            isAlive = state;
        }
};

int main()
{
    // Setting up all the game objects
    initialize_game_objects();

    // TODO: Check if the player is alive in the game loop; if not (due to a gameplay event), re-instance this variable and restart the game.
    player_info player;
    
    std::string inputText;
    std::string outputText;
    std::tuple<std::string, game_object> parserOutput;

    // Title card
    std::cout << "DUNES OF THE FARLANDS" << std::endl << "=====================" << std::endl << std::endl;
    std::cout << "Enter any key to start" << std::endl;

    // Make the program wait until the user inputs any character
    get_input();

    while(true)
    { 
        // Get the player's current input
        inputText = get_input();
    
        // Send input to parser
        parserOutput = game_input_parser(inputText);

        // Send currentAction & currentGameObject to mainAction, get output
        outputText = main_action(get<0>(parserOutput), get<1>(parserOutput));

        // Output text to terminal
        narrator(outputText);

        /*
        Exit program if player input is "EXIT"
        if (input == "EXIT")
        {
            if (exit_seq() == true)
            {
                exit(0);
            }
            else
            {
                std::cin.ignore();
            }
        }
        */
    }
  
    return 0;
}