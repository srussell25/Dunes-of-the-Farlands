#ifndef OBJECTACTIONS_HPP
#define OBJECTACTIONS_HPP

#include "classesmisc.hpp"

// Add function description here
std::string use(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj_name == "chestkey")
    {
        if (player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "notimplemented") // figure out location for chest
        {
            return "You used the chest key.";
        }
        else
        {
            return "unimplemented fail state"; // add unique fail text
        }
    }
    else if (obj_name == "drink")
    {
        if (player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "tavern")
        {
            player_char.remove_inv_item(obj_name, true);
            return "Man, that was a pretty good drink!";
        }
        else if (player_char.get_inv_item(obj_name))
        {
            return "Hmm, I feel like I'm missing out by not "
            "drinking this in the tavern... maybe I should go back?";
        }
        else
        {
            return "unimplemented fail state"; // add unique fail text
        }
    }

    return "Invalid action & object combination; try again."; // Fallback return
}

// Add function description here
std::string take(game_object &obj, std::string obj_name, player_info &player_char)
{
    // Check item is not in player inventory already
    if (obj.get_object_loc() == "playerinventory")
    {
        return "Are you seriously trying to take an item from your own inventory?";
    }
    
    // Continue checks
    if (obj_name == "chestkey")
    {
        if (player_char.get_player_loc() == "notimplemented")
        {
            player_char.add_inv_item(obj);
            return "Key to the chest added to your inventory.";
        }
        else
        {
            return "unimplemented fail state"; // add unique fail text
        }
    }
    else if (obj_name == "drink")  
    {
        if (player_char.get_player_loc() == "tavern")
        {
            player_char.add_inv_item(obj);
            return "The drink was added to your inventory.";
        }
        else 
        {
            return "Take a drink? I don't see a drink around here, do you?";
        }
    }
    else if (obj_name == "clothes" || obj_name == "toys" || obj_name == "shoes") 
    {
        if (player_char.get_player_loc() == "general store")
        {
            return "The shopkeeper slaps your hand and says you need to pay for that before picking it up. "
            "You apologize and bow out of respect; luckily, she forgives you. Maybe you should try a different approach.";
        }
        else 
        {
            return "unimplemented fail state"; // add unique fail text
        }
    }
    else if (obj_name == "coffee")
    {
       if (player_char.get_player_loc() == "coffee shop")
        {
            player_char.set_player_state(false);
            return "You grab a coffee that was made for someone else. The server doesn't miss this, and immediately throws a "
            "wooden barrel at you. Out of surprise, you don't even try to dodge. The impact of the barrel breaks multiple bones, "
            "and you drop to the ground. Learn your manners, kids.";
        }
        else
        {
            return "unimplemented fail state"; // add unique fail text
        }
    }

    return "Invalid action & object combination; try again."; // Fallback return
}

// Add function description here
std::string go_to(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj_name == "oasis")
    {   
        if (player_char.get_player_loc() == "game start")
        {
            player_char.set_player_loc(obj);
            player_char.set_player_state(false);
            return "You make your way over to the oasis, but when you get there, a frog suddenly jumps onto your leg. "
            "It's a poisonous frog. You die in seconds.";
        }
        else
        {
            return "unimplemented fail state"; // add unique fail text
        }
    }
    else if (obj_name == "abandoned town")
    {
        if (player_char.get_player_loc() == "game start" || player_char.get_player_loc() == "tavern")
        {
            player_char.set_player_loc(obj);
            return "You arrive at the town named Nekhem. The town isn't necessarily abandoned,"
            " but it's overrun by thugs and bandits. The walls are broken, and people have"
            " malicious looks on their faces. You see a tavern called the Sand Dune Saloon nearby,"
            " but your gaze also happens upon an old lady who seems to be struggling.";
        }
        else
        {
            return "unimplemented fail state"; // add unique fail text
        }
    }
    else if (obj_name == "tavern")
    {
        if (player_char.get_player_loc() == "abandoned town")
        {
            player_char.set_player_loc(obj);
            return "You enter into the tavern. You try to go up to the bar to ask for directions,"
            " but the bar is heavily crowded, and you end up accidentally stepping on a stranger's foot."
            " He stands up, along with his pals, and draws his sword; you've come across a bandit and his crew!";
        }
        else
        {
            return "unimplemented fail state"; // add unique fail text
        }
    }

    return "Invalid action & object combination; try again."; // Fallback return
}

// Add function description here
std::string talk_to(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj_name == "barkeep")
    {
        if (player_char.get_player_loc() == "tavern")
        {
            return "Welcome to the Sand Dune Saloon. I'm the barkeep. Here's a drink, it's on the house; I can tell you're good people."
            " I must warn you though: there is nothing worth staying for at this town, that is, unless you want to get yourself killed by"
            " one of the locals. If I were you, I'd recommend heading east of here, to the Farlands. It's quite the dangerous area in its"
            " own right, but you'll find more to do over in that region.";
        }
        else
        {
            return "unimplemented fail state"; // add unique fail text
        }
    }
    else if (obj_name == "old lady")
    {
        if (player_char.get_player_loc() == "abandoned town")
        {
            player_char.set_player_state(false);
            return "You try to talk to the old lady, but as you walk over, she suddenly turns around and stabs you."
            " She takes all of your items, and then runs off. Looks like she didn't need any help after all...";
        }
        else
        {
            return "unimplemented fail state"; // add unique fail text
        }
    }

    return "Invalid action & object combination; try again."; // Fallback return
}

// If there is an object to look at, call this function for the description.
std::string look_at(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (player_char.get_player_loc() == obj_name)
    {
        return obj.get_object_desc();
    }
    else
    {
        return "It seems like you can't see any " + obj_name;
    }
}

// Check for the specified character, then attack if possible; otherwise, return a fail message.
std::string attack(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj.get_object_type() == "character")
    {
        if (player_char.get_player_loc() == "abandoned town")
        {
            if (obj_name == "old lady" && obj.get_object_flag("known_evil"))
            {
                return "Attacking an old lady? You can't be serious!";
            }
            // add text for if you discover the old lady is 'evil'
        }
        else if (player_char.get_player_loc() == "tavern")
        {
            if (obj_name == "bandit")
            {
                if (obj.get_object_flag("is_alive"))
                {
                    obj.remove_object_flag("is_alive");
                    return "You take out your sword, and with a mighty slash, you defeat the bandit."
                    " His 'friends' take one look at you and decide to run away. Meanwhile, the rest"
                    " of the bar doesn't seem to take any notice of your actions, except for the barkeep."
                    " He beckons you over to the bar, and sets a drink down in front of you.";
                }
            }
            else if (obj_name == "barkeep")
            {
                return "Hey, you've only just met the guy, have some self discipline!";
            }
        }
        // add more cases here
    }
    else if (obj.get_object_type() == "item")
    {
        // add text related to attacking items here
    }

    return "Invalid action & object combination; try again."; // Fallback return
}

// Read things like books, notes, etc.
std::string read(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj.get_object_type() == "item" && player_char.get_player_loc() == obj.get_object_loc())
    {
        return obj.get_object_desc();
    }
    else
    {
        return "There's nothing to read over here.";
    }
}

// This function will take in an action as a string and the current 
// game object being called upon; it will then check the name of the 
// action via a set of if statements doing string comparisons, and once 
// it finds a match, it will send the game object through to a 
// dedicated function for the action being called upon.
std::string main_action(std::string act, game_object &obj, player_info &player_char) 
{
    std::string result = "";
    std::string obj_name = obj.get_object_name();
    
    if (act == "use")
    { 
        result = use(obj, obj_name, player_char);
    }
    else if (act == "take" || act == "get" || act == "grab")
    {
        result = take(obj, obj_name, player_char);
    }
    else if (act == "go to")
    {
        result = go_to(obj, obj_name, player_char);
    }
    else if (act == "look at")
    {
        result = look_at(obj, obj_name, player_char);
    }
    else if (act == "read")
    {
        result = read(obj, obj_name, player_char);
    }
    else if (act == "talk to")
    {
        result = talk_to(obj, obj_name, player_char);
    }
    else if (act == "attack")
    {
        result = attack(obj, obj_name, player_char);
    }
    else
    {
        result = "This action has not been implemented yet, sorry!";
    }

    return result;
}

#endif