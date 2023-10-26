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

// NOTE: This file is meant for running tests; build this seperately from main.cpp.

STUDENT_TEST("Check to see that find_object exhibits proper behavior.")
{
    initialize_game_objects();
    CHECK(find_object("game start") == mainObjects.at(0));
    CHECK(find_object("this doesn't exist") == game_object());
}

STUDENT_TEST("Check to see that object flags are added to an object correctly")
{
    initialize_game_objects();

    // Add flag to object with non-empty vector
    find_object("game start").add_object_flag("temp_flag");
    CHECK(find_object("game start").get_object_flag("temp_flag") == "temp_flag");

    // Add flag to object with empty vector
    find_object("old lady").add_object_flag("at_location");
    CHECK(find_object("old lady").get_object_flag("at_location") == "at_location");
}

/*  Test won't work with new non-flag location system; modify test to check another flag
STUDENT_TEST("Check to see that flags are properly set during gameplay")
{
    initialize_game_objects();
    player_info player = player_info("new");
    std::tuple<std::string, game_object> parserOutput = {"go to", find_object("abandoned town")};

    main_action(get<0>(parserOutput), get<1>(parserOutput), player);
    
    CHECK(find_object("old lady").get_object_flag("at_location") == "at_location");
    CHECK(find_object("abandoned town").get_object_flag("at_location") == "at_location");
}
*/