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

// NOTE: This file is meant for running tests; build this seperately from main.cpp.

STUDENT_TEST("Check to see that find_object exhibits proper behavior.")
{
    initialize_game_objects();

    CHECK(find_object("game start") == specificvars::main_objects.at(0));
    CHECK_FALSE(find_object("tavern") == specificvars::empty_object);
    CHECK(find_object("fake object") == specificvars::empty_object);

    // Try to find game_object(s) w/ synonyms for names
    CHECK_FALSE(find_object("nekhem") == specificvars::empty_object);
    CHECK_FALSE(find_object("lady") == specificvars::empty_object);
    CHECK_FALSE(find_object("king") == specificvars::empty_object);
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
    parser_output = game_input_parser("leave"); // Faux-regular command, is changed in main.cpp
    CHECK(parser_output.first == "leave");
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

STUDENT_TEST("Testing the 'word_breaker' function.")
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

STUDENT_TEST("Testing the 'center_text' function.")
{
    CHECK(center_text("Hello, World", 14) == " Hello, World ");
    CHECK(center_text("Text is Too Large for given Line Length", 7) == "Text is Too Large for given Line Length");
    CHECK(center_text("Uneven Line Length", 19) == "Uneven Line Length"); //center_displacement = 1/2, rounds down to 0 spaces added
    CHECK(center_text("", 14) == "              ");
    CHECK(center_text("Negative Line Length :(", -14) == "Negative Line Length :(");
}

STUDENT_TEST("Testing the 'generate_border' function.")
{
    CHECK(generate_border(10) == "==========");
    CHECK(generate_border(0) == "");
    CHECK(generate_border(-10) == "");
    CHECK(generate_border() == "========================================================================================");
}

STUDENT_TEST("Check to see that game_object flags can be retrieved, added, & removed.")
{
    initialize_game_objects();

    CHECK_FALSE(find_object("game start").get_object_flag("temp_flag")); // Empty flag map
    CHECK(find_object("bandit").get_object_flag("is_alive")); // Non-empty flag map

    find_object("tavern").set_object_flag("temp_flag", true); // Empty flag map
    CHECK(find_object("tavern").get_object_flag("temp_flag"));
    find_object("old lady").set_object_flag("temp_flag", true); // Non-empty flag map
    CHECK(find_object("old lady").get_object_flag("temp_flag"));

    find_object("barkeep").remove_object_flag("is_alive"); // Non-empty flag map
    CHECK_FALSE(find_object("barkeep").get_object_flag("is_alive"));
}

STUDENT_TEST("Flag Set Check #1: Attacking the bandit in the tavern.")
{
    initialize_parser();
    initialize_game_objects();
    player_info player = player_info("new");
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};

    CHECK(find_object("bandit").get_object_flag("is_alive")); // Bandit is alive

    parser_output = game_input_parser("go to abandoned town"); // Simulate gameplay loop
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "abandoned town");

    parser_output = game_input_parser("go to tavern");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "tavern");

    parser_output = game_input_parser("attack bandit");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK_FALSE(find_object("bandit").get_object_flag("is_alive")); // Bandit is dead
}

STUDENT_TEST("Flag Set Check #2: Recognizing the old lady's status.")
{
    initialize_parser();
    initialize_game_objects();
    player_info player = player_info("new");
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};

    CHECK(find_object("old lady").get_object_flag("is_alive")); // Old lady is alive & not known to be evil
    CHECK_FALSE(find_object("old lady").get_object_flag("known_evil"));

    parser_output = game_input_parser("go to abandoned town"); // Simulate gameplay loop
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "abandoned town");

    parser_output = game_input_parser("attack the old lady");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(find_object("old lady").get_object_flag("is_alive")); // Can't be attacked yet

    parser_output = game_input_parser("look at the old lady");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(find_object("old lady").get_object_flag("known_evil")); // Now known to be evil

    parser_output = game_input_parser("attack the old lady");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK_FALSE(find_object("old lady").get_object_flag("is_alive")); // Old lady is dead
}

STUDENT_TEST("Inventory Check #1: Taking the whiskey from the barkeep and drinking it.")
{
    initialize_parser();
    initialize_game_objects();
    player_info player = player_info("new");
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};

    CHECK_FALSE(find_object("whiskey") == specificvars::empty_object); // Drink exists
    CHECK_FALSE(player.get_inv_item("whiskey")); // Is not in the player's inventory
    CHECK(find_object("whiskey").get_object_loc() == "tavern"); // Is located in the tavern

    parser_output = game_input_parser("go to abandoned town"); // Simulate gameplay loop
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "abandoned town");

    parser_output = game_input_parser("go to tavern");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "tavern");

    parser_output = game_input_parser("attack bandit");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("take whiskey");
    main_action(parser_output.first, (parser_output.second).get(), player);

    CHECK_FALSE(find_object("whiskey") == specificvars::empty_object); // Drink exists
    CHECK(player.get_inv_item("whiskey")); // Is in the player's inventory
    CHECK_FALSE(find_object("whiskey").get_object_loc() == "tavern"); // Is not located in the tavern

    parser_output = game_input_parser("drink whiskey");
    main_action(parser_output.first, (parser_output.second).get(), player);

    CHECK(find_object("whiskey") == specificvars::empty_object); // Drink doesn't exist
    CHECK_FALSE(player.get_inv_item("whiskey")); // Is not in the player's inventory
}

STUDENT_TEST("Movement Check #1: Going from the start of the game to the Farlands.")
{
    initialize_parser();
    initialize_game_objects();
    player_info player = player_info("new");
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};

    parser_output = game_input_parser("go to the abandoned town"); // Simulate gameplay loop
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "abandoned town");

    parser_output = game_input_parser("go to the saloon");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "tavern");

    parser_output = game_input_parser("attack bandit");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("talk to the bartender");
    main_action(parser_output.first, (parser_output.second).get(), player);
    
    parser_output = {"go", std::ref(find_object(player.get_player_loc_prev()))}; // Simulate 'leave' command within 'main.cpp'
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "abandoned town");

    parser_output = game_input_parser("go to the farlands");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "farlands");
}

STUDENT_TEST("Movement Check #2: Going to the coffee shop and then returning to the city square.")
{
    initialize_parser();
    initialize_game_objects();
    player_info player = player_info("new");
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};

    parser_output = game_input_parser("go to the abandoned town"); // Simulate gameplay loop
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "abandoned town");

    parser_output = game_input_parser("go to the saloon");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "tavern");

    parser_output = game_input_parser("attack bandit");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("talk to the bartender");
    main_action(parser_output.first, (parser_output.second).get(), player);
    
    parser_output = {"go", std::ref(find_object(player.get_player_loc_prev()))}; // Simulate 'leave' command within 'main.cpp'
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "abandoned town");

    parser_output = game_input_parser("go to the farlands");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "farlands");

    parser_output = game_input_parser("talk to the lookouts");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("go to the city square");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "city square");

    parser_output = game_input_parser("go to the coffee shop");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "coffee shop");

    parser_output = {"go", std::ref(find_object(player.get_player_loc_prev()))}; // 'leave' command
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "city square");
}

STUDENT_TEST("Final Check: Completing the entire game.")
{
    initialize_parser();
    initialize_game_objects();
    player_info player = player_info("new");
    std::pair<std::string, std::reference_wrapper<game_object>> parser_output = {"", specificvars::empty_object};

    parser_output = game_input_parser("go to the abandoned town"); // Simulate gameplay loop
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "abandoned town");

    parser_output = game_input_parser("go to the saloon");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "tavern");

    parser_output = game_input_parser("attack bandit");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("talk to the bartender");
    main_action(parser_output.first, (parser_output.second).get(), player);
    
    parser_output = {"go", std::ref(find_object(player.get_player_loc_prev()))}; // Simulate 'leave' command within 'main.cpp'
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "abandoned town");

    parser_output = game_input_parser("go to the farlands");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "farlands");

    parser_output = game_input_parser("talk to the lookouts");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("go to the city square");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "city square");

    parser_output = game_input_parser("go to the coffee shop");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "coffee shop");

    parser_output = game_input_parser("talk to the locals");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = {"go", std::ref(find_object(player.get_player_loc_prev()))}; // 'leave' command
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "city square");

    parser_output = game_input_parser("go to the restaurant");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "sarabi's egyptian cuisine");

    parser_output = game_input_parser("talk to the locals");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = {"go", std::ref(find_object(player.get_player_loc_prev()))}; // 'leave' command
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "city square");

    parser_output = game_input_parser("go to the general store");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "general store");

    parser_output = game_input_parser("talk to the shopkeeper");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("take the armor of torren");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("use the armor of torren");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = {"go", std::ref(find_object(player.get_player_loc_prev()))}; // 'leave' command
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "city square");

    parser_output = game_input_parser("go to the palace");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "palace");

    parser_output = game_input_parser("go to the side gate");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "side gate");

    parser_output = game_input_parser("attack the guard");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("take the paper");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("read the paper");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("go inside the palace");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "inside palace");

    parser_output = game_input_parser("go to the potion room");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "potion room");

    parser_output = game_input_parser("read the book");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("take the strength potion");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = {"go", std::ref(find_object(player.get_player_loc_prev()))}; // 'leave' command
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "inside palace");

    parser_output = game_input_parser("go to spyro's lair");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "spyro's lair");

    parser_output = game_input_parser("use the strength potion");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("go to the king's throne");
    main_action(parser_output.first, (parser_output.second).get(), player);
    CHECK(player.get_player_loc() == "king's throne");

    parser_output = game_input_parser("attack king akhem");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("attack king akhem");
    main_action(parser_output.first, (parser_output.second).get(), player);

    parser_output = game_input_parser("attack king akhem");
    main_action(parser_output.first, (parser_output.second).get(), player);

    CHECK(player.get_player_flag("finished_game")); // should be true
}
