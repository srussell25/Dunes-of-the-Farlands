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

// NOTE: This file is meant for running tests; build this seperately from main.cpp.

STUDENT_TEST("Check to see that find_object exhibits proper behavior.")
{
    initialize_game_objects();

    // Try to find game_object, check that the return values match expected behavior
    CHECK(find_object("game start") == specificvars::main_objects.at(0));
    CHECK_FALSE(find_object("tavern") == specificvars::empty_object);
    CHECK(find_object("fake object") == specificvars::empty_object);
}

STUDENT_TEST("Check to see that game_object flags can be retrieved, added, & removed.")
{
    initialize_game_objects();

    // Try to find game_object flags, check that the return values match expected behavior
    CHECK_FALSE(find_object("game start").get_object_flag("temp_flag")); // empty flag map
    CHECK(find_object("bandit").get_object_flag("is_alive")); // non-empty flag map

    // Try to add a flag to a game_object, check if successful
    find_object("tavern").set_object_flag("temp_flag", true); // empty flag map
    CHECK(find_object("tavern").get_object_flag("temp_flag"));
    find_object("old lady").set_object_flag("temp_flag", true); // non-empty flag map
    CHECK(find_object("old lady").get_object_flag("temp_flag"));

    // Try to remove a flag from a game_object, check if successful
    find_object("barkeep").remove_object_flag("is_alive"); // non-empty flag map
    CHECK_FALSE(find_object("barkeep").get_object_flag("is_alive"));
}

STUDENT_TEST("Flag Set Check #1: Attacking the bandit in the tavern.")
{
    initialize_game_objects();
    player_info player = player_info("new");
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};

    // Check that the bandit is alive
    CHECK(find_object("bandit").get_object_flag("is_alive"));

    // Simulate gameplay loop
    parser_output = {"go to", find_object("abandoned town")};
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "abandoned town");

    parser_output = {"go to", find_object("tavern")};
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "tavern");

    parser_output = {"attack", find_object("bandit")};
    main_action(parser_output.first, (parser_output.second).get(), player);

    // Check that the bandit is dead
    CHECK_FALSE(find_object("bandit").get_object_flag("is_alive"));
}

STUDENT_TEST("Inventory Check #1: Taking the drink from the barkeep and using it.")
{
    initialize_game_objects();
    player_info player = player_info("new");
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};

    // Check that the drink exists, is not in the player inventory, & is located in the tavern
    CHECK_FALSE(find_object("drink") == specificvars::empty_object);
    CHECK_FALSE(player.get_inv_item("drink"));
    CHECK(find_object("drink").get_object_loc() == "tavern");

    // Simulate gameplay loop
    parser_output = {"go to", find_object("abandoned town")};
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "abandoned town");

    parser_output = {"go to", find_object("tavern")};
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "tavern");

    parser_output = {"attack", find_object("bandit")};
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = {"take", find_object("drink")};
    main_action(parser_output.first, (parser_output.second).get(), player);

    // Check that the drink exists, is added to the player inventory, & is not located in the tavern
    CHECK_FALSE(find_object("drink") == specificvars::empty_object);
    CHECK(player.get_inv_item("drink"));
    CHECK_FALSE(find_object("drink").get_object_loc() == "tavern");

    parser_output = {"use", find_object("drink")};
    main_action(parser_output.first, (parser_output.second).get(), player);

    // Check that the drink does not exist, is not in the player inventory, & is not located in the tavern
    CHECK(find_object("drink") == specificvars::empty_object);
    CHECK_FALSE(player.get_inv_item("drink"));
    CHECK_FALSE(find_object("drink").get_object_loc() == "tavern");
}