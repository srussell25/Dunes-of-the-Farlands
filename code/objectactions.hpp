#ifndef OBJECTACTIONS_HPP
#define OBJECTACTIONS_HPP

#include "playercharacter.hpp"

std::string use(game_object obj, player_info &playerChar)
{
    if (obj.get_object_name() == "chestKey")
    {
        return "You used the chestKey.";
    }
    else if (obj.get_object_name() == "drink")
    {
        if (obj.get_object_flag("at_object") == "at_object")
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

std::string take(game_object obj, player_info &playerChar)
{
    if (obj.get_object_name() == "chestKey")
    {
        playerChar.add_item(obj);
        return "Key to the chest added to your inventory.";
    }
    else if (obj.get_object_name() == "drink")  
    {
        if (obj.get_object_flag("at_object") == "at_object")
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
std::string go_to(game_object obj, player_info &playerChar)
{
    if (obj.get_object_name() == "oasis")
    {
        if (playerChar.get_location().get_object_name() == "gameStart")
        {
            playerChar.set_location(oasis);
            playerChar.set_player_state(false);
            return "You make your way over to the oasis, but when you get there, a frog suddenly jumps onto your leg. "
            "It's a poisonous frog. You die in seconds.";
        }
    }
    else if (obj.get_object_name() == "abandonedTown")
    {
        if (playerChar.get_location().get_object_name() == "gameStart")
        {
            playerChar.set_location(abandonedTown); 
            oldLady.add_object_flag("nearCharacter");
            abandonedTown.add_object_flag("at_town");
            gameStart.remove_object_flag("at_start");
            return "You arrive at the town named Nekhem. The town isn't necessarily abandoned,"
            " but it's overrun by thugs and bandits. The walls are broken, and people have"
            " malicious looks on their faces. You see a tavern called the Sand Dune Saloon nearby,"
            " but your gaze also happens upon an old lady who seems to be struggling. What do you do?";
        }
    }
    else if (obj.get_object_name() == "tavern")
    {
        if (playerChar.get_location().get_object_name() == "abandonedTown")
        {
            barkeep.add_object_flag("nearCharacter");
            bandit.add_object_flag("nearCharacter");
            tavern.add_object_flag("at_tavern");
            drink.add_object_flag("at_object");
            abandonedTown.remove_object_flag("at_town");
            oldLady.remove_object_flag("nearCharacter");   
            return "You enter into the tavern. You try to go up to the bar to ask for directions,"
            " but the bar is heavily crowded, and you end up accidentally stepping on a stranger's foot."
            " He stands up, along with his pals, and draws his sword; you've come across a bandit and his crew!"
            " What do you do?";
        }
    }
    return "Invalid action & object combination; try again.";
}

std::string talk_to(game_object obj, player_info &playerChar)
{
    if (obj.get_object_name() == "bartender" || obj.get_object_name() == "barkeep" )
    {
        if (obj.get_object_flag("nearCharacter") == "nearCharacter")
        {
        return "hey im the bartender of the Sand Dune Saloon. here is a drink. there is nothing here for you at the is town unless you want to get yourself kill"
        "i would recommend going to east to the Farlands, but be on your guard. Some of the people in that area are no good.";

        }
    }
    else if (obj.get_object_flag("oldlady") == "oldlady")
    {
        if (obj.get_object_flag("nearCharacter") == "nearCharacter")
        {
            playerChar.set_player_state(false);
            return "you try to talk to the old lady but then she stabs you and takes your stuff. looks like the lady wasn't week after all";
        }
    }
    return "Invalid action & object combination; try again.";
}


// If there is an object to look at, call this function for the description.
std::string look(game_object obj, player_info &playerChar)
{
    if (obj.get_object_flag("at object") == "at object")
    {
        return obj.get_object_description();
    }
    return "Invalid action & object combination; try again.";
}

// Should give a more in depth description of an object - not fully implemented as of now.
std::string examine(game_object obj, player_info &playerChar)
{
    if (obj.get_object_flag("at object") == "at object")
    {
        return obj.get_object_description();
    }
    return "Invalid action & object combination; try again.";
}

// Attack the character, then check for the specified character
std::string attack(game_object obj, player_info &playerChar)
{
    if (obj.get_object_type() == "character" && obj.get_object_flag("nearCharacter") == "nearCharacter")
    {
        if(obj.get_object_name() == "bandit")
        {
            bandit.remove_object_flag("is_alive");
            return "You take out your sword, and with a mighty slash, you defeat the bandit."
            " His 'friends' take one look at you and decide to run away. Meanwhile, the rest"
            " of the bar doesn't seem to take any notice of your actions, except for the bartender."
            " He beckons you over to the bar, and sets a drink down in front of you.";
        }
        else if(obj.get_object_name() == "oldLady")
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

//read things like books, notes, etc.
std::string read(game_object obj, player_info &playerChar)
{
    if (obj.get_object_type() == "item")
    {
        if (obj.get_object_name() == "note" && obj.get_object_flag("at_tavern") == "at_tavern")
        {
            return obj.get_object_description();
        }
    }
    return "Invalid action & object combination; try again.";
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
    else if (act == "take" || act == "get" || "grab")
    {
        result = take(obj, playerChar);
    }
    else if (act == "go to")
    {
        result = go_to(obj, playerChar);
    }
    else if (act == "look")
    {
        result = look(obj, playerChar);
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