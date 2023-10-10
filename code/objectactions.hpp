#ifndef OBJECTACTIONS_HPP
#define OBJECTACTIONS_HPP

#include "playercharacter.hpp"

std::string use(game_object &obj, player_info &playerChar)
{
    if (obj.get_object_name() == "chestKey")
    {
        return "You used the chestKey.";
    }
    else if (obj.get_object_name() == "drink")
    {
        if (obj.get_object_flag("at_location") == "at_location")
        {
            playerChar.remove_item(obj);
            return "Man, that was a pretty good drink!";
        }
        else
        {
            return "Hmm, I feel like I'm missing out by not "
            "drinking this in the tavern... maybe I should go back?";
        }
    }
    return "Invalid action & object combination; try again.";
}

std::string take(game_object &obj, player_info &playerChar)
{
    if (obj.get_object_name() == "chestKey")
    {
        playerChar.add_item(obj);
        return "Key to the chest added to your inventory.";
    }
    else if (obj.get_object_name() == "drink")  
    {
        if (obj.get_object_flag("at_location") == "at_location")
        {
            playerChar.add_item(obj);
            return "The drink was added to your inventory.";
        }
        else 
        {
            return "Take a drink? I don't see a drink around here, do you?";
        }
    }
    return "Invalid action & object combination; try again.";
}

std::string go_to(game_object &obj, player_info &playerChar)
{
    if (obj.get_object_name() == "oasis")
    {
        if (playerChar.get_location() == gameStart)
        {
            playerChar.set_location(oasis);
            playerChar.set_player_state(false);
            return "You make your way over to the oasis, but when you get there, a frog suddenly jumps onto your leg. "
            "It's a poisonous frog. You die in seconds.";
        }
    }
    else if (obj.get_object_name() == "abandoned town")
    {
        if (playerChar.get_location() == gameStart)
        {
            playerChar.set_location(abandonedTown); 
            oldLady.add_object_flag("near_character");
            abandonedTown.add_object_flag("at_location");
            gameStart.remove_object_flag("at_start");
            return "You arrive at the town named Nekhem. The town isn't necessarily abandoned,"
            " but it's overrun by thugs and bandits. The walls are broken, and people have"
            " malicious looks on their faces. You see a tavern called the Sand Dune Saloon nearby,"
            " but your gaze also happens upon an old lady who seems to be struggling.";
        }
    }
    else if (obj.get_object_name() == "tavern")
    {
        if (playerChar.get_location() == abandonedTown)
        {
            barkeep.add_object_flag("near_character");
            bandit.add_object_flag("near_character");
            tavern.add_object_flag("at_location");
            drink.add_object_flag("at_location");
            abandonedTown.remove_object_flag("at_location");
            oldLady.remove_object_flag("near_character");   
            return "You enter into the tavern. You try to go up to the bar to ask for directions,"
            " but the bar is heavily crowded, and you end up accidentally stepping on a stranger's foot."
            " He stands up, along with his pals, and draws his sword; you've come across a bandit and his crew!";
        }
    }
    return "Invalid action & object combination; try again.";
}

std::string talk_to(game_object &obj, player_info &playerChar)
{
    if (obj.get_object_name() == "barkeep" )
    {
        if (playerChar.get_location() == tavern)
        {
        return "Welcome to the Sand Dune Saloon. I'm the barkeep. Here's a drink, it's on the house; I can tell you're good people."
        " I must warn you though: there is nothing worth staying for at this town, that is, unless you want to get yourself killed by"
        " one of the locals. If I were you, I'd recommend heading east of here, to the Farlands. It's quite the dangerous area in its"
        " own right, but you'll find more to do over in that region.";
        }
    }
    else if (obj.get_object_name() == "old lady")
    {
        if (playerChar.get_location() == abandonedTown)
        {
            playerChar.set_player_state(false);
            return "You try to talk to the old lady, but as you walk over, she suddenly turns around and stabs you."
            " She takes all of your items, and then runs off. Looks like she didn't need any help after all...";
        }
    }
    return "Invalid action & object combination; try again.";
}

// If there is an object to look at, call this function for the description.
std::string look_at(game_object &obj, player_info &playerChar)
{
    //if (obj.get_object_flag("at_start") == "at_start" || obj.get_object_flag("at_location") == "at_location" || obj.get_object_flag("near_character") == "near_character")
    //{
        return obj.get_object_description();
    //}
    //else
    //{
    //    return "It seems like you can't see any " + obj.get_object_name();
    //}
}

// Check for the specified character, then attack if possible; else, return fail message
std::string attack(game_object &obj, player_info &playerChar)
{
    if (obj.get_object_type() == "character" && playerChar.get_location() == tavern)
    {
        if(obj.get_object_name() == "bandit")
        {
            bandit.remove_object_flag("is_alive");
            return "You take out your sword, and with a mighty slash, you defeat the bandit."
            " His 'friends' take one look at you and decide to run away. Meanwhile, the rest"
            " of the bar doesn't seem to take any notice of your actions, except for the barkeep."
            " He beckons you over to the bar, and sets a drink down in front of you.";
        }
        else if(obj.get_object_name() == "old lady")
        {
            return "Attacking an old lady? You can't be serious!";
        }
        else if(obj.get_object_name() == "barkeep")
        {
            return "Hey, you've only just met the guy, have some self discipline!";
        }
    }
    return "Invalid action & object combination; try again.";
}

// Read things like books, notes, etc.
std::string read(game_object &obj, player_info &playerChar)
{
    if (obj.get_object_type() == "item")
    {
        if (obj.get_object_flag("at_location") == "at_location")
        {
            return obj.get_object_description();
        }
    }
    
    return "There's nothing to read over here.";
}

// This function will take in an action as a string and the current 
// game object being called upon; it will then check the name of the 
// action via a set of if statements doing string comparisons, and once 
// it finds a match, it will send the game object through to a 
// dedicated function for the action being called upon.
std::string main_action(std::string act, game_object &obj, player_info &playerChar) 
{
    std::string result = "";
    
    if (act == "use")
    { 
        result = use(obj, playerChar);
    }
    else if (act == "take" || act == "get" || act == "grab")
    {
        result = take(obj, playerChar);
    }
    else if (act == "go to")
    {
        result = go_to(obj, playerChar);
    }
    else if (act == "look at")
    {
        result = look_at(obj, playerChar);
    }
    else if (act == "read")
    {
        result = read(obj, playerChar);
    }
    else if (act == "talk to")
    {
        result = talk_to(obj, playerChar);
    }
    else
    {
        result = "This action has not been implemented yet, sorry!";
    }
    return result;
}

#endif