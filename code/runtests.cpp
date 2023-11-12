// Add necessary includes & imports here
#include "catch.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <set>
#include <optional>
#include <math.h>

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

STUDENT_TEST("Check parser behavior with valid inputs.")
{
    initialize_parser();
    initialize_game_objects();
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};

    // Check that string_splitter acts as expected
    CHECK(string_splitter("haha yes temp") == (std::vector<std::string>) {"haha", "yes", "temp"});

    // Check if unique commands are returned
    parser_output = game_input_parser("inventory");
    CHECK(parser_output.first == "inventory");
    CHECK(parser_output.second == specificvars::empty_object);
    parser_output = game_input_parser("help");
    CHECK(parser_output.first == "help");
    CHECK(parser_output.second == specificvars::empty_object);
    parser_output = game_input_parser("credits");
    CHECK(parser_output.first == "credits");
    CHECK(parser_output.second == specificvars::empty_object);
    parser_output = game_input_parser("exit");
    CHECK(parser_output.first == "exit");
    CHECK(parser_output.second == specificvars::empty_object);

    // Check if regular commands are returned
    parser_output = game_input_parser("read note"); // No predicates
    CHECK(parser_output.first == "read");
    CHECK(parser_output.second == find_object("note"));
    parser_output = game_input_parser("attack the bandit"); // One pred
    CHECK(parser_output.first == "attack");
    CHECK(parser_output.second == find_object("bandit"));
    parser_output = game_input_parser("go to the oasis"); // Two pred
    CHECK(parser_output.first == "go");
    CHECK(parser_output.second == find_object("oasis"));
    parser_output = game_input_parser("attack old lady"); // No pred., obj. has a space
    CHECK(parser_output.first == "attack");
    CHECK(parser_output.second == find_object("old lady"));
    parser_output = game_input_parser("look at abandoned town"); // One pred., obj. has a space
    CHECK(parser_output.first == "look");
    CHECK(parser_output.second == find_object("abandoned town"));
    parser_output = game_input_parser("talk to the old lady"); // Two pred., obj. has a space
    CHECK(parser_output.first == "talk");
    CHECK(parser_output.second == find_object("old lady"));
    parser_output = game_input_parser("go to sarabi's egyptian cuisine"); // One pred., obj. has two spaces & special char
    CHECK(parser_output.first == "go");
    CHECK(parser_output.second == find_object("sarabi's egyptian cuisine"));
}

STUDENT_TEST("Check parser behavior with invalid inputs.")
{
    initialize_parser();
    initialize_game_objects();
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};
    std::pair<std::string, std::reference_wrapper<game_object>> default_output = parser_output;

    // Check special cases
    parser_output = game_input_parser("");
    CHECK(parser_output == default_output);
    parser_output = game_input_parser(" ");
    CHECK(parser_output == default_output);
    parser_output = game_input_parser("  ");
    CHECK(parser_output == default_output);
    parser_output = game_input_parser("  ");
    CHECK(parser_output == default_output);

    // Check general invalid cases
    parser_output = game_input_parser("go.to the tavern");
    CHECK(parser_output == default_output);
    parser_output = game_input_parser("goto tavern");
    CHECK(parser_output == default_output);
    parser_output = game_input_parser("tavern go to");
    CHECK(parser_output == default_output);
    parser_output = game_input_parser("eat a burger");
    CHECK(parser_output == default_output);
    parser_output = game_input_parser("look at the tavern.");
    CHECK(parser_output.first == "look");
    CHECK(parser_output.second == specificvars::empty_object);
    parser_output = game_input_parser("look at the witch");
    CHECK(parser_output.first == "look");
    CHECK(parser_output.second == specificvars::empty_object);

    // Extra spaces test w/ two predicates
    parser_output = game_input_parser(" go to the oasis");
    CHECK(parser_output == default_output);
    parser_output = game_input_parser("go  to the oasis");
    CHECK(parser_output.first == "go");
    CHECK(parser_output.second == specificvars::empty_object);
    parser_output = game_input_parser("go to  the oasis");
    CHECK(parser_output.first == "go");
    CHECK(parser_output.second == specificvars::empty_object);
    parser_output = game_input_parser("go to the  oasis");
    CHECK(parser_output.first == "go");
    CHECK(parser_output.second == specificvars::empty_object);
    parser_output = game_input_parser("go to the oasis ");
    CHECK(parser_output.first == "go");
    CHECK(parser_output.second == specificvars::empty_object);

    // Extra spaces test w/ one predicate and a space in the object's name
    parser_output = game_input_parser(" look at abandoned town");
    CHECK(parser_output == default_output);
    parser_output = game_input_parser("look  at abandoned town");
    CHECK(parser_output.first == "look");
    CHECK(parser_output.second == specificvars::empty_object);
    parser_output = game_input_parser("look at  abandoned town");
    CHECK(parser_output.first == "look");
    CHECK(parser_output.second == specificvars::empty_object);
    parser_output = game_input_parser("look at abandoned  town");
    CHECK(parser_output.first == "look");
    CHECK(parser_output.second == specificvars::empty_object);
    parser_output = game_input_parser("look at abandoned town ");
    CHECK(parser_output.first == "look");
    CHECK(parser_output.second == specificvars::empty_object);
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
    initialize_parser();
    initialize_game_objects();
    player_info player = player_info("new");
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};

    // Check that the bandit is alive
    CHECK(find_object("bandit").get_object_flag("is_alive"));

    // Simulate gameplay loop
    parser_output = game_input_parser("go to abandoned town");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "abandoned town");

    parser_output = game_input_parser("go to tavern");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "tavern");

    parser_output = game_input_parser("attack bandit");
    main_action(parser_output.first, (parser_output.second).get(), player);

    // Check that the bandit is dead
    CHECK_FALSE(find_object("bandit").get_object_flag("is_alive"));
}

STUDENT_TEST("Inventory Check #1: Taking the whiskey from the barkeep and drinking it.")
{
    initialize_parser();
    initialize_game_objects();
    player_info player = player_info("new");
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};

    // Check that the drink exists, is not in the player's inventory, & is located in the tavern
    CHECK_FALSE(find_object("whiskey") == specificvars::empty_object);
    CHECK_FALSE(player.get_inv_item("whiskey"));
    CHECK(find_object("whiskey").get_object_loc() == "tavern");

    // Simulate gameplay loop
    parser_output = game_input_parser("go to abandoned town");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "abandoned town");

    parser_output = game_input_parser("go to tavern");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "tavern");

    parser_output = game_input_parser("attack bandit");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("take whiskey");
    main_action(parser_output.first, (parser_output.second).get(), player);

    // Check that the drink exists, is added to the player's inventory, & is not located in the tavern
    CHECK_FALSE(find_object("whiskey") == specificvars::empty_object);
    CHECK(player.get_inv_item("whiskey"));
    CHECK_FALSE(find_object("whiskey").get_object_loc() == "tavern");

    parser_output = game_input_parser("drink whiskey");
    main_action(parser_output.first, (parser_output.second).get(), player);

    // Check that the drink does not exist & is not in the player's inventory
    CHECK(find_object("whiskey") == specificvars::empty_object);
    CHECK_FALSE(player.get_inv_item("whiskey"));
    CHECK_FALSE(find_object("whiskey").get_object_loc() == "tavern");
}

//UI Method Tests//

STUDENT_TEST("Word Breaker Test")
{
    std::vector<std::string> hello_world = {"Hello,", "World"};
    std::vector<std::string> empty_test = {""};
    std::vector<std::string> num_test = {"123", "4567"};
    std::vector<std::string> special_char_test = {"\n;#%&"};
    std::vector<std::string> extra_spaces_test = {"extra", "spaces"};

    CHECK(word_breaker("Hello, World") == hello_world);
    CHECK(word_breaker("") == empty_test);
    CHECK(word_breaker("123 4567") == num_test);
    CHECK(word_breaker("\n;#%&") == special_char_test);
    CHECK(word_breaker("extra     spaces") == extra_spaces_test);
}

STUDENT_TEST("Center Text Test")
{
    CHECK(center_text("Hello, World", 14) == " Hello, World ");
    CHECK(center_text("Text is Too Large for given Line Length", 7) == "Text is Too Large for given Line Length");
    CHECK(center_text("Uneven Line Length", 19) == "Uneven Line Length"); //center_displacement = 1/2 in this calc which should round down to 0 spaces added
    CHECK(center_text("", 14) == "              ");
    CHECK(center_text("Negative Line Length :(", -14) == "Negative Line Length :(");
}

STUDENT_TEST("Border Generation Test")
{
    CHECK(generate_border(10) == "==========");
    CHECK(generate_border(0) == "");
    CHECK(generate_border(-10) == "");
    CHECK(generate_border() == "========================================================================================");
}
