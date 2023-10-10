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

    if (input.size() > 3 && input.substr(0, 2) == "use")
    {
        returnStr = "use";
        iterVal = 2;
    }
    else if (input.size() > 4 && input.substr(0, 3) == "take")
    {
        returnStr = "take";
        iterVal = 3;
    }
    else if (input.size() > 4 && input.substr(0, 3) == "grab")
    {
        returnStr = "grab";
        iterVal = 3;
    }
    else if (input.size() > 5 && input.substr(0, 4) == "go to")
    {
        returnStr = "go to";
        iterVal = 4;
    }
    else if (input.size() > 4 && input.substr(0, 3) == "look")
    {
        returnStr = "look";
        iterVal = 3;
    }
    else if (input.size() > 4 && input.substr(0, 3) == "read")
    {
        returnStr = "read";
        iterVal = 3;
    }
    else if (input.size() > 7 && input.substr(0, 6) == "talk to")
    {
        returnStr = "talk to";
        iterVal = 6;
    }
    else
    {
        return std::tuple<std::string, game_object>{returnStr, returnObj};
    }

    if (input.size() >= (iterVal + 15) && input.substr(iterVal, 13) == "abandoned town")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), abandonedTown);
    }
    else if (input.size() >= (iterVal + 6) && input.substr(iterVal, 4) == "oasis")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), oasis);
    }
    else if (input.size() >= (iterVal + 7) && input.substr(iterVal, 5) == "tavern")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), tavern);
    }
    else if (input.size() >= (iterVal + 7) && input.substr(iterVal, 5) == "bandit")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), bandit);
    }
    else if (input.size() >= (iterVal + 9) && input.substr(iterVal, 7) == "old lady")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), oldLady);
    }
    else if (input.size() >= (iterVal + 6) && input.substr(iterVal, 4) == "sword")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), sword);
    }
    else if (input.size() >= (iterVal + 7) && input.substr(iterVal, 5) == "shield")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), shield);
    }
    else if (input.size() >= (iterVal + 10) && input.substr(iterVal, 8) == "chest key")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), chestkey);
    }
    else if (input.size() >= (iterVal + 6) && input.substr(iterVal, 4) == "chest")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), chest);
    }
    else if (input.size() >= (iterVal + 5) && input.substr(iterVal, 3) == "note")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), note);
    }
    else if (input.size() >= (iterVal + 6) && input.substr(iterVal, 4) == "drink")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), drink);
    }
    else if (input.size() >= (iterVal + 8) && input.substr(iterVal, 6) == "barkeep")
    {
        returnObj = *std::find(mainObjects.begin(), mainObjects.end(), barkeep);
    }

    return std::tuple<std::string, game_object>{returnStr, returnObj};
}

#endif