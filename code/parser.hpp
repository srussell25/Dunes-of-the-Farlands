#ifndef PARSER_HPP
#define PARSER_HPP

#include "gameobjects.hpp"

// TODO: Write a better explanation for this function
// This function takes in user input & parses it
std::tuple<std::string, game_object> game_input_parser(std::string input)
{
    std::string returnStr;
    game_object returnObj;

    // code goes here

    return std::tuple<std::string, game_object>{returnStr, returnObj};
}

#endif