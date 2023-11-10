// Add necessary includes & imports here
#include "catch.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <stdlib.h> // just include so screen can be cleared from within main loop
#include <unordered_map>
#include <set>

// Including every header file we made for the project
#include "ui.hpp"
#include "parser.hpp"
#include "gameobjects.hpp"
#include "objectactions.hpp"
#include "classesmisc.hpp"

// TODO: Go through every function declaration in the program and 
// change the comment to match Prof. Kaiser's the style guide.
// His instructions are - describe behavior at a high level, 
// including parameters & return values, preconditions/assumptions,
// and error conditions. Also, check all inline comments.

int main()
{
    std::string input_text;
    std::string output_text;
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};
    player_info player;

    initialize_parser();
    std::system("clear"); //just clears the console to make game startup cleaner

    //this is so that the main loop can be restarted
    //without requiring the user to go through the
    //'press enter to start' prompt again
    bool first_startup = true; 

    // Main program loop
    while(true)
    {
        // Initializing game objects & player character to a specific state
        initialize_game_objects();
        player = player_info("new");

        // Display the title card
        display_titlecard();

        if (first_startup)
        {
        // Make the program wait until the user inputs any character
        std::cout << center_text("Press Enter to Start", 88 /*width of the titlecard*/) << std::endl;
        get_input();
        first_startup = false;
        }
        else
        {
            std::cout<<std::endl<<std::endl;
            std::cout<<generate_border()<<std::endl;
        }

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
            input_text = get_input();

            // Send input to parser
            parser_output = game_input_parser(input_text);

            // If there is invalid input or a special command, skip to next loop iteration
            if (parser_output.first == "help")
            {
                word_wrapper(word_breaker("Available commands: use, take, get, grab, go to, look at, read, talk to, attack, inventory, help, credits, exit."));
                continue;
            }
            else if (parser_output.first == "inventory")
            {
                display_inventory(player);
                continue;
            }
            else if (parser_output.first == "credits")
            {
                display_credits();
                continue;
            }
            else if (parser_output.first == "exit")
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
            else if (parser_output.second == specificvars::empty_object) 
            {
                std::cout << "Invalid input; type 'help' for a list of all commands."<<std::endl;
                std::cout << generate_border() << std::endl;
                continue;
            }

            // Send currentAction & currentGameObject to mainAction, get output
            output_text = main_action(parser_output.first, (parser_output.second).get(), player);

            // Output text to terminal
            narrator(output_text);
        }

        // Game Over loop; if player answers no, quit the game
        std::cout << center_text("Game Over!") << std::endl;
        if (!exit_seq("Would you like to try again?"))
        {
            break;
        }
        else
        {
            std::cin.ignore();
            std::system("clear"); //clears the screen when restarting after dying
        }
    }
  
    return 0;
}