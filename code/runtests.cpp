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

STUDENT_TEST("Check to see that flags are properly set during gameplay")
{
    initialize_game_objects();
    player_info player = player_info("new");
    std::tuple<std::string, game_object> parserOutput = {"go to", find_object("abandoned town")};

    main_action(get<0>(parserOutput), get<1>(parserOutput), player);

    // std::cout << "Current Object #1: " + find_object("old lady").get_object_name() << std::endl;
    // std::cout << "Current Object #2: " + find_object("abandoned town").get_object_name() << std::endl;
    
    CHECK(find_object("old lady").get_object_flag("at_location") == "at_location");
    CHECK(find_object("abandoned town").get_object_flag("at_location") == "at_location");
}

STUDENT_TEST("Check to see that find_object exhibits proper behavior.")
{
    initialize_game_objects();
    CHECK(find_object("old lady") != game_object());
    CHECK(find_object("this doesn't exist") == game_object());
}