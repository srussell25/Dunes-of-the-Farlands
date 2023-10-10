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
    std::string inputText;
    std::string outputText;
    std::tuple<std::string, game_object> parserOutput;
    game_object emptyGameObj;
    player_info player;

    // Main program loop
    while(true)
    {
        // Setting up all the game objects & player character
        initialize_game_objects();
        player = player_info();

        // Title card
        std::cout << "DUNES OF THE FARLANDS" << std::endl << "=====================" << std::endl << std::endl;
        std::cout << "Enter any key to start" << std::endl;

        // Make the program wait until the user inputs any character
        get_input();

        // Main gameplay loop; if player dies, break loop to restart
        while(!player.get_player_state()) 
        {
            // Get the player's current input
            inputText = get_input();

            // Send input to parser
            parserOutput = game_input_parser(inputText);

            // If there is invalid input, skip to next loop iteration
            if (get<1>(parserOutput) == emptyGameObj) 
            {
                std::cout << "Invalid input; type 'HELP' for a list of all commands." << std::endl;
                continue;
            }

            // Send currentAction & currentGameObject to mainAction, get output
            outputText = main_action(get<0>(parserOutput), get<1>(parserOutput), player);

            // Output text to terminal
            narrator(outputText);
        }

        // Game Over loop; if player answers no, quit the game
        std::cout << std::endl << "Game Over!" << std::endl;
        std::cin.ignore();
        if (!exit_seq("Try again?"))
        {
            break;
        }
        else
        {
            std::cin.ignore();
        }
    }
  
    return 0;
}