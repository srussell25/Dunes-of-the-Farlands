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
        player = player_info("new");

        // Title card
        std::cout << "DUNES OF THE FARLANDS" << std::endl << "=====================" << std::endl << std::endl;
        std::cout << "Enter any letter to start!" << std::endl;

        // Make the program wait until the user inputs any character
        get_input();

        // Intro text
        std::cout << "You awake in a sandy desert. Your head is throbbing, and you don't remember much."
        " What you do know, however, is that your name is Vir Khabar, a human."
        " When your vision starts to come back to you, you sit up slowly to check if anything is around you."
        " You spot a town that appears to be 'abandoned' in the north." << std::endl;

        // Main gameplay loop; if player dies, break loop to restart
        while(true) 
        {
            // Get the player's current input
            inputText = get_input();

            // Send input to parser
            parserOutput = game_input_parser(inputText);

            // If there is invalid input, skip to next loop iteration
            if (get<1>(parserOutput) == emptyGameObj) 
            {
                std::cout << "Invalid input; type 'help' for a list of all commands." << std::endl;
                continue;
            }

            // Send currentAction & currentGameObject to mainAction, get output
            outputText = main_action(get<0>(parserOutput), get<1>(parserOutput), player);

            // Output text to terminal
            narrator(outputText);

            // Nested break for the loop to ensure all text is outputted to the console.
            if (!player.get_player_state())
            {
                break;
            }
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