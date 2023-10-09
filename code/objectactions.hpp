#ifndef OBJECTACTIONS_HPP
#define OBJECTACTIONS_HPP

#include "playercharacter.hpp"

std::string use(game_object obj, player_info &playerChar)
{
    if (obj.get_object_name() == "key")
    {
        return "You used the key.";
    }
    
    return "";
}

std::string take(game_object obj, player_info &playerChar)
{
    if (obj.get_object_name() == "key")
    {
        playerChar.add_item(obj);
        return "Key added to inventory.";
    }

    return "";
}

// This function will take in an action as a string and the current 
// game object being called upon; it will then check the name of the 
// action via a set of if statements doing string comparisons, and once 
// it finds a match, it will send the game object through to a 
// dedicated function for the action being called upon.
std::string main_action(std::string act, game_object obj, player_info &playerChar) 
{
    std::string result = "";
    
    if (act == "use")
    { 
        result = use(obj, playerChar);
    }
    else if (act == "take")
    {
        result = take(obj, playerChar);
    }

    return result;
}

#endif