// Add necessary includes & imports here
#include "catch.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>

// Including every header file we made for the project
#include "ui.hpp"
#include "parser.hpp"
#include "gameobjects.hpp"
#include "objectactions.hpp"
#include "classesmisc.hpp"

int main()
{
    std::string inputText;
    std::string outputText;
    std::pair<std::string, std::reference_wrapper<game_object>> parserOutput = {"", specificvars::emptyObject};
    player_info player;

    // Main program loop
    while(true)
    {
        // Initializing game objects & player character to a specific state
        initialize_game_objects();
        player = player_info("new");

        // Title card
        std::cout << "\nDUNES OF THE FARLANDS\n=====================\nPress enter to start!\n\n";

        // Make the program wait until the user inputs any character
        get_input();

        // Intro text
        narrator("You awake in a sandy desert. Your head is throbbing, and you don't remember much."
        " What you do know, however, is that your name is Vir Khabar, a human."
        " When your vision starts to come back to you, you sit up slowly to check if anything is around you."
        " You spot a town that appears to be 'abandoned' in the north,"
        " but also see what appears to be an oasis nearby.");

        // Main gameplay loop; if player dies, break loop to restart
        while(player.get_player_state()) 
        {
            // Get the player's current input
            inputText = get_input();

            // Send input to parser
            parserOutput = game_input_parser(inputText);

            // If there is invalid input or a special command, skip to next loop iteration
            if (parserOutput.first == "help")
            {
                std::cout << "\nAvailable commands: use, take, get, grab, go to, look at, read, talk to, attack, inventory, help, exit.\n";
                continue;
            }
            else if (parserOutput.first == "inventory")
            {
                narrator(player.get_inv_string());
                continue;
            }
            else if (parserOutput.first == "exit")
            {
                if (exit_seq() == true)
                {
                    exit(0);
                }
                else
                {
                    std::cin.ignore();
                    continue;
                }
            }
            else if (parserOutput.second == specificvars::emptyObject) 
            {
                std::cout << "\nInvalid input; type 'help' for a list of all commands.\n";
                continue;
            }

            // Send currentAction & currentGameObject to mainAction, get output
            outputText = main_action(parserOutput.first, (parserOutput.second).get(), player);

            // Output text to terminal
            narrator(outputText);
        }

        // Game Over loop; if player answers no, quit the game
        std::cout << "\nGame Over!\n";
        if (!exit_seq("Would you like to try again?"))
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