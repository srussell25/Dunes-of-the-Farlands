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
#include "classesmisc.hpp"

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

            // If there is invalid input, skip to next loop iteration
            if (get<0>(parserOutput) == "help")
            {
                std::cout << "\nAvailable commands: use, take, get, grab, go to, look at, read, talk to, attack, inventory, help, exit.\n";
                continue;
            }
            else if (get<0>(parserOutput) == "inventory")
            {
                // TODO: Fix inventory lookup & return
                std::cout << "\nYour inventory is currently empty.\n";
                continue;
            }
            else if (get<0>(parserOutput) == "exit")
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
            else if (get<1>(parserOutput) == emptyGameObj) 
            {
                std::cout << "\nInvalid input; type 'help' for a list of all commands.\n";
                continue;
            }

            // Send currentAction & currentGameObject to mainAction, get output
            outputText = main_action(get<0>(parserOutput), get<1>(parserOutput), player);

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