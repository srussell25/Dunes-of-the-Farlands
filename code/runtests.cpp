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
    CHECK(find_object("game start") == specificvars::mainObjects.at(0));
    CHECK_FALSE(find_object("tavern") == specificvars::emptyObject);
    CHECK(find_object("fake object") == specificvars::emptyObject);
}

STUDENT_TEST("Check to see that game_object flags can be retrieved, added, & removed.")
{
    initialize_game_objects();

    // Try to find game_object flags, check that the return values match expected behavior
    CHECK_FALSE(find_object("game start").get_object_flag("temp_flag") == "temp_flag"); // empty flag vector
    CHECK(!find_object("game start").get_object_flag("temp_flag").empty()); // correct behavior
    CHECK(find_object("bandit").get_object_flag("is_alive") == "is_alive"); // non-empty flag vector

    // Try to add a flag to a game_object, check if successful
    find_object("tavern").add_object_flag("temp_flag");
    CHECK(find_object("tavern").get_object_flag("temp_flag") == "temp_flag"); // empty flag vector
    find_object("old lady").add_object_flag("temp_flag");
    CHECK(find_object("old lady").get_object_flag("temp_flag") == "temp_flag"); // non-empty flag vector

    // Try to remove a flag from a game_object, check if successful
    find_object("barkeep").remove_object_flag("is_alive");
    CHECK_FALSE(find_object("barkeep").get_object_flag("is_alive") == "is_alive"); // non-empty flag vector
}

STUDENT_TEST("Flag Set Check #1: Attacking the bandit in the tavern.")
{
    initialize_game_objects();
    player_info player = player_info("new");
    std::pair<std::string, game_object&> parserOutput(std::string(), specificvars::emptyObject);
    
    // Check that the bandit exists and is alive (has "is_alive" flag)
    CHECK(find_object("bandit").get_object_flag("is_alive") == "is_alive");
    CHECK(!find_object("bandit").get_object_flag("is_alive").empty()); // alternate style of check

    // Simulate gameplay loop
    parserOutput = {"go to", find_object("abandoned town")};
    main_action(parserOutput.first, parserOutput.second, player);

    parserOutput = {"go to", find_object("tavern")};
    main_action(parserOutput.first, parserOutput.second, player);

    parserOutput = {"attack", find_object("bandit")};
    main_action(parserOutput.first, parserOutput.second, player);

    // Check that the bandit exists and is dead (no "is_alive" flag)
    CHECK(find_object("bandit").get_object_flag("is_alive") != "is_alive");
    CHECK(find_object("bandit").get_object_flag("is_alive").empty()); // alternate style of check
}

STUDENT_TEST("Inventory Check #1: Taking the drink from the barkeep and using it.")
{
    initialize_game_objects();
    player_info player = player_info("new");
    std::pair<std::string, game_object&> parserOutput(std::string(), specificvars::emptyObject);

    // Check that the drink exists, is not in the player inventory, & is located in the tavern
    CHECK_FALSE(find_object("drink") == specificvars::emptyObject);
    CHECK(player.get_inv_item("drink"));
    CHECK(find_object("drink").get_object_loc() == "tavern");

    // Simulate gameplay loop
    parserOutput = {"go to", find_object("abandoned town")};
    main_action(parserOutput.first, parserOutput.second, player);

    parserOutput = {"go to", find_object("tavern")};
    main_action(parserOutput.first, parserOutput.second, player);

    parserOutput = {"attack", find_object("bandit")};
    main_action(parserOutput.first, parserOutput.second, player);

    parserOutput = {"take", find_object("drink")};
    main_action(parserOutput.first, parserOutput.second, player);

    // Check that the drink exists, is added to the player inventory, & is not located in the tavern
    CHECK_FALSE(find_object("drink") == specificvars::emptyObject);
    CHECK_FALSE(player.get_inv_item("drink"));
    CHECK_FALSE(find_object("drink").get_object_loc() == "tavern");

    parserOutput = {"use", find_object("drink")};
    main_action(parserOutput.first, parserOutput.second, player);

    // Check that the drink does not exist, is not in the player inventory, & is not located in the tavern
    CHECK(find_object("drink") == specificvars::emptyObject);
    CHECK(player.get_inv_item("drink"));
    CHECK_FALSE(find_object("drink").get_object_loc() == "tavern");
}