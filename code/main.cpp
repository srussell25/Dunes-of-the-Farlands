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
#include "playercharacter.hpp"

int main()
{
    // Setting up all the game objects
    initialize_game_objects();

    // TODO: Check if the player is alive in the game loop; 
    // if not (due to a gameplay event), re-instance 
    // this variable and restart the game.
    player_info player = player_info();
    
    std::string inputText;
    std::string outputText;
    std::tuple<std::string, game_object> parserOutput;
    game_object emptyGameObj;

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

        // If there is invalid input, skip to next loop iteration
        if (get<1>(parserOutput) == emptyGameObj) {
            std::cout << "Invalid input; type 'HELP' for a list of all commands." << std::endl;
            continue;
        }

        // Send currentAction & currentGameObject to mainAction, get output
        outputText = main_action(get<0>(parserOutput), get<1>(parserOutput), player);

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