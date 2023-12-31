#include "catch.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <set>
#include <optional>
#include <math.h>

#include "ui.hpp"
#include "parser.hpp"
#include "gameobjects.hpp"
#include "objectactions.hpp"
#include "classesmisc.hpp"

int main()
{
    std::string input_text;
    std::string output_text;
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};
    player_info player;

    bool first_startup = true;

    while(true) // Outer loop; used so that the program can be "restarted"
    {
        initialize_game_objects(); // Refresh objects & player to original state
        player = player_info("new");

        if (first_startup)
        {
            display_titlecard();
            std::cout << center_text("Press Enter to Start", 88) << std::endl;
            get_input(); // Make the program wait until the user inputs any character
            first_startup = false;
        }
        else
        {
            std::cout << std::endl << std::endl;
            display_titlecard();
            std::cout << std::endl << generate_border() << std::endl;
        }

        // Intro text
        narrator("You awake in a sandy desert. Your head is throbbing, and you don't remember much. "
        "What you do know, however, is that your name is Vir Khabar, a human. "
        "When your vision starts to come back to you, you sit up slowly to check if anything is around you. "
        "You spot a town that appears to be 'abandoned' in the north, "
        "but also see what appears to be an oasis nearby.");

        while(player.get_player_state() || player.get_player_finish()) // Inner loop; iterates after each command
        {
            input_text = get_input();
            parser_output = game_input_parser(input_text);

            if (parser_output.first == "help") // Check for special commands or invalid input
            {
                word_wrapper(word_breaker("Regular commands: use, take/get/grab, go, leave, look/examine, "
                "read, talk, attack. \nSpecial commands: inventory, location, help, credits, exit."));
                continue;
            }
            else if (parser_output.first == "inventory")
            {
                display_inventory(player);
                continue;
            }
            else if (parser_output.first == "location")
            {
                display_location(player);
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
                    std::cout << generate_border();
                    continue;
                }
            }
            else if (parser_output.first == "leave")
            {
                parser_output = {"go", std::ref(find_object(player.get_player_loc_prev()))};
            }
            else if (parser_output.second == specificvars::empty_object) 
            {
                std::cout << "Invalid input; type 'help' for a list of all commands." << std::endl;
                std::cout << generate_border() << std::endl;
                continue;
            }

            output_text = main_action(parser_output.first, (parser_output.second).get(), player);

            if (player.get_player_flag("npc_is_talking"))
            {
                npc_text(output_text, (parser_output.second).get().get_object_name());
                player.remove_player_flag("npc_is_talking");
            }
            else
            {
                narrator(output_text);
            }
        }

        if (player.get_player_finish()) // If game is finished, display credits & then quit the program
        {
            std::cout << center_text("The End. You completed the game!") << std::endl;
            display_credits();
            break;
        }

        std::cout << center_text("Game Over!") << std::endl; // Yes/no loop; quits program on "no"
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