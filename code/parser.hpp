#ifndef PARSER_HPP
#define PARSER_HPP

#include "gameobjects.hpp"

// NOTE: list of all commands: go to, look at, examine, attack, take, 
// throw item, read, open, unlock, put, talk to, inventory, help, exit

// TODO: Completely rewrite this function, it's currently way too hardcoded
// This function takes in user input & parses it
std::pair<std::string, std::reference_wrapper<game_object>> game_input_parser(std::string input)
{
    std::string return_str;
    std::reference_wrapper<game_object> return_obj = specificvars::empty_object;
    int iter_val;

    if (input.empty())
    {
       return {return_str, return_obj};
    }

    if (input.size() > 4 && input.substr(0, 4) == "use ")
    {
        return_str = "use";
        iter_val = 4;
    }
    else if (input.size() > 5 && input.substr(0, 5) == "take ")
    {
        return_str = "take";
        iter_val = 5;
    }
    else if (input.size() > 5 && input.substr(0, 5) == "grab ")
    {
        return_str = "grab";
        iter_val = 5;
    }
    else if (input.size() > 6 && input.substr(0, 6) == "go to ")
    {
        return_str = "go to";
        iter_val = 6;
    }
    else if (input.size() > 8 && input.substr(0, 8) == "look at ")
    {
        return_str = "look at";
        iter_val = 8;
    }
    else if (input.size() > 5 && input.substr(0, 5) == "read ")
    {
        return_str = "read";
        iter_val = 5;
    }
    else if (input.size() > 8 && input.substr(0, 8) == "talk to ")
    {
        return_str = "talk to";
        iter_val = 8;
    }
    else if (input.size() > 7 && input.substr(0, 7) == "attack ")
    {
        return_str = "attack";
        iter_val = 7;
    }
    else if (input.size() >= 4 && input.substr(0, 4) == "help")
    {
        return_str = "help";
        return {return_str, return_obj};
    }
    else if (input.size() >= 9 && input.substr(0, 9) == "inventory")
    {
        return_str = "inventory";
        return {return_str, return_obj};
    }
    else if (input.size() >= 4 && input.substr(0, 4) == "exit")
    {
        return_str = "exit";
        return {return_str, return_obj};
    }
    else if (input.size() >= 7 && input.substr(0, 7) == "credits")
    {
        return_str = "credits";
        return {return_str, return_obj};
    }
    else
    {
        return {return_str, return_obj};
    }

    if (input.size() >= (iter_val + 14) && input.substr(iter_val, iter_val + 14) == "abandoned town")
    {
        return_obj = find_object("abandoned town");
    }
    else if (input.size() >= (iter_val + 5) && input.substr(iter_val, iter_val + 5) == "oasis")
    {
        return_obj = find_object("oasis");
    }
    else if (input.size() >= (iter_val + 6) && input.substr(iter_val, iter_val + 6) == "tavern")
    {
        return_obj = find_object("tavern");
    }
    else if (input.size() >= (iter_val + 6) && input.substr(iter_val, iter_val + 6) == "bandit")
    {
        return_obj = find_object("bandit");
    }
    else if (input.size() >= (iter_val + 8) && input.substr(iter_val, iter_val + 8) == "old lady")
    {
        return_obj = find_object("old lady");
    }
    else if (input.size() >= (iter_val + 5) && input.substr(iter_val, iter_val + 5) == "sword")
    {
        return_obj = find_object("sword");
    }
    else if (input.size() >= (iter_val + 6) && input.substr(iter_val, iter_val + 6) == "shield")
    {
        return_obj = find_object("shield");
    }
    else if (input.size() >= (iter_val + 9) && input.substr(iter_val, iter_val + 9) == "chest key")
    {
        return_obj = find_object("chestkey");
    }
    else if (input.size() >= (iter_val + 5) && input.substr(iter_val, iter_val + 5) == "chest")
    {
        return_obj = find_object("chest");
    }
    else if (input.size() >= (iter_val + 4) && input.substr(iter_val, iter_val + 4) == "note")
    {
        return_obj = find_object("note");
    }
    else if (input.size() >= (iter_val + 5) && input.substr(iter_val, iter_val + 5) == "drink")
    {
        return_obj = find_object("drink");
    }
    else if (input.size() >= (iter_val + 7) && input.substr(iter_val, iter_val + 7) == "barkeep")
    {
        return_obj = find_object("barkeep");
    }

    return {return_str, return_obj};
}

#endif