#ifndef PARSER_HPP
#define PARSER_HPP

#include "gameobjects.hpp"

// TODO: Write a better explanation for this function
// This function takes in user input & parses it
std::tuple<std::string, game_object> game_input_parser(std::string input)
{
    std::string returnStr;
    game_object returnObj;

    if (input.empty())
    {
       return std::tuple<std::string, game_object>{returnStr, returnObj};
    }

    return std::tuple<std::string, game_object>{returnStr, returnObj};
}

// NOTE: list of all commands: go to, look at, examine, attack, take, 
// throw item, read, open, unlock, put, talk to, inventory, help, exit

#endif