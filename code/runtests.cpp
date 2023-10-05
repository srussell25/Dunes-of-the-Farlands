// This file is meant for running tests; build seperately from project file
#include "catch.hpp"
#include "ui.hpp"
#include "parser.hpp"
#include "gameobjects.hpp"
#include "objectactions.hpp"
#include "actions.hpp"

// Example test for ui.hpp
STUDENT_TEST("function1 test for ui.hpp") {
    CHECK(function1(2) == 2);
}