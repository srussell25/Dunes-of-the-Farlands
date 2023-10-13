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

/* NOTE: Don't include this test until flags have been re-implemented & the test is redone.
STUDENT_TEST("Check to see that flags are properly set during gameplay")
{
    initialize_game_objects();
    player_info player = player_info("new");
    std::tuple<std::string, game_object> parserOutput = {"go to", abandonedTown};

    main_action(get<0>(parserOutput), get<1>(parserOutput), player);

    std::cout << "Current Object #1: " + mainObjects.at(11).get_object_name() << std::endl;
    std::cout << "Current Object #2: " + mainObjects.at(7).get_object_name() << std::endl;

    CHECK_FALSE(oldLady.get_object_flag("near_character") == "near_character");
    CHECK(mainObjects.at(11).get_object_flag("near_character") == "near_character");
    CHECK_FALSE(abandonedTown.get_object_flag("at_location") == "at_location");
    CHECK(mainObjects.at(7).get_object_flag("at_location") == "at_location");
}
*/

STUDENT_TEST("Check to see that find_object exhibits proper behavior.")
{
    initialize_game_objects();
    CHECK(find_object("old lady") != game_object());
    CHECK(find_object("this doesn't exist") == game_object());
}