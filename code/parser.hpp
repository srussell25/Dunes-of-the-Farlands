#ifndef PARSER_HPP
#define PARSER_HPP

#include "gameobjects.hpp"

// NOTE: list of all commands: go to, look at, examine, attack, take, 
// throw item, read, open, unlock, put, talk to, inventory, help, exit

// TODO: Completely rewrite this function, it's currently way too hardcoded
// This function takes in user input & parses it
std::tuple<std::string, game_object> game_input_parser(std::string input)
{
    std::string returnStr;
    game_object returnObj;
    int iterVal;

    if (input.empty())
    {
       return std::tuple<std::string, game_object>{returnStr, returnObj};
    }

    if (input.size() > 4 && input.substr(0, 4) == "use ")
    {
        returnStr = "use";
        iterVal = 4;
    }
    else if (input.size() > 5 && input.substr(0, 5) == "take ")
    {
        returnStr = "take";
        iterVal = 5;
    }
    else if (input.size() > 5 && input.substr(0, 5) == "grab ")
    {
        returnStr = "grab";
        iterVal = 5;
    }
    else if (input.size() > 6 && input.substr(0, 6) == "go to ")
    {
        returnStr = "go to";
        iterVal = 6;
    }
    else if (input.size() > 8 && input.substr(0, 8) == "look at ")
    {
        returnStr = "look at";
        iterVal = 8;
    }
    else if (input.size() > 5 && input.substr(0, 5) == "read ")
    {
        returnStr = "read";
        iterVal = 5;
    }
    else if (input.size() > 8 && input.substr(0, 8) == "talk to ")
    {
        returnStr = "talk to";
        iterVal = 8;
    }
    else if (input.size() > 7 && input.substr(0, 7) == "attack ")
    {
        returnStr = "attack";
        iterVal = 7;
    }
    else if (input.size() >= 4 && input.substr(0, 4) == "help")
    {
        returnStr = "help";
        return std::tuple<std::string, game_object>{returnStr, returnObj};
    }
    else if (input.size() >= 9 && input.substr(0, 9) == "inventory")
    {
        returnStr = "inventory";
        return std::tuple<std::string, game_object>{returnStr, returnObj};
    }
    else if (input.size() >= 4 && input.substr(0, 4) == "exit")
    {
        returnStr = "exit";
        return std::tuple<std::string, game_object>{returnStr, returnObj};
    }
    else
    {
        return std::tuple<std::string, game_object>{returnStr, returnObj};
    }

    if (input.size() >= (iterVal + 14) && input.substr(iterVal, iterVal + 14) == "abandoned town")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), find_object("abandoned town"));
    }
    else if (input.size() >= (iterVal + 5) && input.substr(iterVal, iterVal + 5) == "oasis")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), find_object("oasis"));
    }
    else if (input.size() >= (iterVal + 6) && input.substr(iterVal, iterVal + 6) == "tavern")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), find_object("tavern"));
    }
    else if (input.size() >= (iterVal + 6) && input.substr(iterVal, iterVal + 6) == "bandit")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), find_object("bandit"));
    }
    else if (input.size() >= (iterVal + 8) && input.substr(iterVal, iterVal + 8) == "old lady")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), find_object("old lady"));
    }
    else if (input.size() >= (iterVal + 5) && input.substr(iterVal, iterVal + 5) == "sword")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), find_object("sword"));
    }
    else if (input.size() >= (iterVal + 6) && input.substr(iterVal, iterVal + 6) == "shield")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), find_object("shield"));
    }
    else if (input.size() >= (iterVal + 9) && input.substr(iterVal, iterVal + 9) == "chest key")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), find_object("chestkey"));
    }
    else if (input.size() >= (iterVal + 5) && input.substr(iterVal, iterVal + 5) == "chest")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), find_object("chest"));
    }
    else if (input.size() >= (iterVal + 4) && input.substr(iterVal, iterVal + 4) == "note")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), find_object("note"));
    }
    else if (input.size() >= (iterVal + 5) && input.substr(iterVal, iterVal + 5) == "drink")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), find_object("drink"));
    }
    else if (input.size() >= (iterVal + 7) && input.substr(iterVal, iterVal + 7) == "barkeep")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), find_object("barkeep"));
    }

    return std::tuple<std::string, game_object>{returnStr, returnObj};
}

#endif