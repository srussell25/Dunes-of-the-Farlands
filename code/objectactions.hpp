#ifndef OBJECTACTIONS_HPP
#define OBJECTACTIONS_HPP

#include "classesmisc.hpp"

/// @brief Finds the result of the player interacting with a `game_object` via the in-game "use" command
/// @param obj The `game_object`, passed by ref., that the player is interacting with
/// @param obj_name The name of the `game_object` the player is interacting with
/// @param player_char An instance of `player_info`, passed by ref., denoting the player's current state
/// @return A string describing the results of the player's action
/// @note This function is called whenever the player uses the similar "drink" command
std::string use(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj_name == "whiskey")
    {
        if (player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "tavern")
        {
            player_char.remove_inv_item(obj_name, true);
            return "Man, that was a pretty good whiskey! You thank the barkeep for the free drink.";
        }
        else if (player_char.get_inv_item(obj_name))
        {
            return "You get the feeling you're missing out by not drinking the "
            "whiskey in the tavern. Maybe you should go back?";
        }
        else
        {
            return "You don't have any " + obj_name + ".";
        }
    }
    else if (obj_name == "coffee")
    {
        if (player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "coffee shop")
        {
            player_char.remove_inv_item(obj_name, true);
            return "Now that was a refreshing cup of coffee! No wonder why the locals come to Coco's for their coffee.";
        }
        else if (player_char.get_inv_item(obj_name))
        {
            player_char.remove_inv_item(obj_name, true);
            return "The coffee you recieved has cooled by now and doesn't taste any good. Maybe you should've drank it when it was still hot.";
        }
        else
        {
            return "You don't have any " + obj_name + ".";
        }
    }
    else if (obj_name == "armor of torren")
    {
        if (player_char.get_inv_item(obj_name))
        {
            if (!player_char.get_player_flag("wearing_armor"))
            {
                player_char.set_player_flag("wearing_armor", true);
                return "You are now wearing the Armor of Torren. You feel a tad bit safer in this armor.";
            }
            else
            {
                return "You've already equipped the armor; you can't equip it twice.";
            }
        }
        else
        {
            return "You don't have any armor to put on.";
        }
    }
    else if (obj_name == "fire potion")
    {
        if (player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "spyro's lair")
        {
            player_char.remove_inv_item(obj_name, true);
            player_char.set_player_state(false);

            return "The potion you used on Spyro caused him to absorb the fire within his"
            "skin and melts you into a crisp.";
        }
        else if (player_char.get_player_loc() != "spyro's lair")
        {
            return "It's not time to use this potion just yet. Try again at somewhere more dangerous.";
        }
        else 
        {
            return "You don't have any " + obj_name + ".";
        }
    }
    else if (obj_name == "confusion potion")
    {
        if (player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "spyro's lair")
        {
            player_char.set_player_flag("the_confuser", true);
            player_char.set_player_flag("throne_available", true);
            player_char.remove_inv_item(obj_name, true);

            return "You grab the confusion potion out of your inventory, unscrew the bottle, "
            "and chuck it at Spyro. He begins to visibly shake, forgetting where he is, and "
            "collapses on the floor. He's still alive, but the potion was so strong that he "
            "can't put up any fight. The path to King Akhem's throne is now clear...";
        }
        else if (player_char.get_player_loc() != "spyro's lair")
        {
            return "It's not time to use this potion just yet. Try again at somewhere more dangerous.";
        }
        else 
        {
            return "You don't have any " + obj_name + ".";
        }
    }
    else if (obj_name == "hunger potion")
    {
        if (player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "spyro's lair")
        {
            player_char.remove_inv_item(obj_name, true);
            player_char.set_player_state(false);

            return "The potion you used on Spyro made him hungry. Hungry for flesh. You don't last very long.";
        }
       else if (player_char.get_player_loc() != "spyro's lair")
        {
            return "It's not time to use this potion just yet. Try again at somewhere more dangerous.";
        }
        else 
        {
            return "You don't have any " + obj_name + ".";
        }
    }
    else if (obj_name == "strength potion")
    {
        if (player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "spyro's lair")
        {
            player_char.set_player_flag("is_strong", true);
            player_char.remove_inv_item(obj_name, true);

            return "You can feel your strength increase as you drink the potion. The power it gives you "
            "is immense. That sphynx is about to go down and you're going to make sure of it.";
        }
        else if (player_char.get_player_loc() != "spyro's lair")
        {
            return "It's not time to use this potion just yet. Try again at somewhere more dangerous.";
        }
        else 
        {
            return "You don't have any " + obj_name + ".";
        }
    }

    return "Invalid action & object combination; try again.";
}

/// @brief Finds the result of the player interacting with a `game_object` via the in-game "take" command
/// @param obj The `game_object`, passed by ref., that the player is interacting with
/// @param obj_name The name of the `game_object` the player is interacting with
/// @param player_char An instance of `player_info`, passed by ref., denoting the player's current state
/// @return A string describing the results of the player's action
/// @note This function is called whenever the player uses the similar "grab" or "take" commands
std::string take(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj.get_object_loc() == "playerinventory")
    {
        return "Are you seriously trying to take an item from your own inventory?";
    }
    
    if (obj_name == "whiskey")  
    {
        if (player_char.get_player_loc() == "tavern" && obj.get_object_loc() == "tavern")
        {
            player_char.add_inv_item(obj);
            return "The drink was added to your inventory. Always nice to have some whiskey.";
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
            return "There are no " + obj_name + " around you, try looking in another location."; 
        }
    }
    else if (obj_name == "coffee")
    {
        if (player_char.get_player_loc() == "coffee shop" && obj.get_object_loc() == "coffee shop")
        {
            player_char.set_player_state(false);
            return "You grab a coffee that was made for someone else. The server doesn't miss this, and immediately throws a "
            "wooden barrel at you. Out of surprise, you don't even try to dodge. The impact of the barrel breaks multiple bones, "
            "and you drop to the ground. Learn your manners, kids.";
        }
        else
        {
            return "There's no coffee near you. Sorry, but you can't get your caffeine fix just yet.";
        }
    }
    else if (obj_name == "armor of torren")
    {
        if (player_char.get_player_loc() == "general store" && obj.get_object_loc() == "general store" && player_char.get_player_flag("offered_armor"))
        {
            player_char.add_inv_item(obj);
            player_char.set_player_flag("has_armor", true);

            return "The Armor of Torren was added to your inventory. Maybe this armor could come in handy?";
        }
        else
        {
            return "What kind of armor are you talking about?";
        }
    }
    else if (obj_name == "book")
    {
        if (player_char.get_player_loc() == "potion room")
        {
            return "Can't you see the note? It says don't take the book, ya bozo. Read, don't take.";
        }
        else 
        {
            return "There aren't any books at your current location. Try looking somewhere else.";
        }
    }
    else if (obj_name == "spyro")
    {
        if (player_char.get_player_loc() == "spyro's lair")
        {
            player_char.set_player_state(false);
            return "You try and grab Spyro by the leg, to which he responds by kicking you away - "
            "away into a wall I should specify, killing you instantly. Nice job there, pal.";
        }
        else 
        {
            return "Spyro? Who are you talking about?";
        }
    }
    else if (obj_name == "king akhem")
    {
        if (player_char.get_player_loc() == "king's throne")
        {
            player_char.set_player_state(false);
            return "You attempt to grab King Akhem by the arm. He flings you off like a piece of "
            "spaghetti, and you're immediately swarmed by all the guards. Did you really think "
            "that was going to work?";
        }
        else 
        {
            return "King Akhem is not at your location. Maybe you will meet him some day.";
        }
    }
    else if (obj_name == "paper")
    {
        if (player_char.get_player_loc() == "side gate" && obj.get_object_loc() == "side gate")
        {
            player_char.add_inv_item(obj);
            return "The paper was added to your inventory. It seems to have some important script, "
            "maybe you should try reading it?";
        }
        else 
        {
            return "The item '" + obj_name + "' is not in this location. Try something else.";
        }
    }
    else if (obj_name == "fire potion")
    {
        if (player_char.get_player_loc() == "potion room" && !player_char.get_player_flag("has_potion"))
        {
            player_char.add_inv_item(obj);
            player_char.set_player_flag("has_potion", true);
            return "Fire potion has been added to inventory";
        }
        else if (player_char.get_player_loc() == "potion room" && player_char.get_player_flag("has_potion"))
        {
            return "Sorry, you already took a potion. You only have one slot in your inventory for a potion.";
        }
        else
        {
            return "The item '" + obj_name + "' is not in this location. Try something else.";
        }
    }
    else if (obj_name == "confusion potion")
    {
        if (player_char.get_player_loc() == "potion room" && !player_char.get_player_flag("has_potion"))
        {
            player_char.add_inv_item(obj);
            player_char.set_player_flag("has_potion", true);
            return "Confusion potion has been added to inventory";
        }
        else if (player_char.get_player_loc() == "potion room" && player_char.get_player_flag("has_potion"))
        {
            return "Sorry, you already took a potion. You only have one slot in your inventory for a potion.";
        }
        else
        {
            return "The item '" + obj_name + "' is not in this location. Try something else.";
        }
    }
    else if (obj_name == "hunger potion")
    {
        if (player_char.get_player_loc() == "potion room" && !player_char.get_player_flag("has_potion"))
        {
            player_char.add_inv_item(obj);
            player_char.set_player_flag("has_potion", true);
            return "Hunger potion has been added to inventory";
        }
        else if (player_char.get_player_loc() == "potion room" && player_char.get_player_flag("has_potion"))
        {
            return "Sorry, you already took a potion. You only have one slot in your inventory for a potion.";
        }
        else
        {
            return "The item '" + obj_name + "' is not in this location. Try something else.";
        }
    }
    else if (obj_name == "strength potion")
    {
        if (player_char.get_player_loc() == "potion room" && !player_char.get_player_flag("has_potion"))
        {
            player_char.add_inv_item(obj);
            player_char.set_player_flag("has_potion", true);
            return "strength potion has been added to inventory";
        }
        else if (player_char.get_player_loc() == "potion room" && player_char.get_player_flag("has_potion"))
        {
            return "Sorry, you already took a potion. You only have one slot in your inventory for a potion.";
        }
        else
        {
            return "The item '" + obj_name + "' is not in this location. Try something else.";
        }
    }
    
    return "This action cannot be performed here. Try something else.";
}

/// @brief Finds the result of the player interacting with a `game_object` via the in-game "go" command
/// @param obj The `game_object`, passed by ref., that the player is interacting with
/// @param obj_name The name of the `game_object` the player is interacting with
/// @param player_char An instance of `player_info`, passed by ref., denoting the player's current state
/// @return A string describing the results of the player's action
std::string go_to(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj_name == player_char.get_player_loc())
    {
        return "What are you doing? You're already here!";
    }
    else if (obj_name == "game start")
    {
        player_char.set_player_loc(obj_name);
        return "Congratulations! You're back at where you started.";
    }
    else if (obj_name == "oasis")
    {   
        player_char.set_player_loc(obj_name);
        player_char.set_player_state(false);

        return "You make your way over to the oasis, but when you get there, "
        "a frog suddenly jumps onto your leg. It's a poisonous frog. You die in seconds.";
    }
    else if (obj_name == "abandoned town")
    {
        if (!obj.get_object_flag("been_to"))
        {        
            obj.set_object_flag("been_to", true);
            obj.set_object_desc("What previously seemed to be an abandoned town is, "
            "sadly, a town that has been taken over by thugs and bandits.");
            player_char.set_player_loc(obj_name);

            return "You arrive at the town named Nekhem. The town isn't necessarily abandoned, "
            "but it's overrun by thugs and bandits. The walls are broken, and people have "
            "malicious looks on their faces. You see a tavern called the Sand Dune Saloon nearby, "
            "but your gaze also happens upon an old lady who seems to be struggling.";
        }
        else if (find_object("bandit").get_object_flag("is_alive"))
        {
            player_char.set_player_state(false);

            return "You turn away from the bandit to leave the tavern, and he takes that "
            "chance to stab you in the back. Now seriously, what else did you expect would happen there?";
        }
        else
        {
            player_char.set_player_loc(obj_name);
            
            return "You're back at the center of Nekhem. It's still overrun by thugs and "
            "bandits, and the Sand Dune Saloon hasn't moved either.";
        }
    }
    else if (obj_name == "tavern")
    {
        if (!obj.get_object_flag("been_to"))
        {
            obj.set_object_flag("been_to", true);
            obj.set_object_desc("Well, it's definitely a tavern. You've got a barkeep, "
            "some drinks, and some truly awful customers. A classic combo.");
            player_char.set_player_loc(obj_name);

            return "You enter into the tavern. You try to go up to the bar to ask for directions, "
            "but the bar is heavily crowded, and you end up accidentally stepping on a stranger's foot. "
            "He stands up, along with his pals, and draws his sword; you've come across a bandit and his crew!";
        }
        else
        {
            player_char.set_player_loc(obj_name);

            return "You arrive back at the tavern. What do you want to do?";
        }
    }
    else if (obj_name == "farlands")
    {
        if (!obj.get_object_flag("been_to"))
        {
            obj.set_object_flag("been_to", true);
            player_char.set_player_loc(obj_name);

            return "When arriving at the outer gates of the Farlands, you see that this place is surrounded by a "
            "huge sandstone wall that seems to surround the entire city. Spews of fire are emitted from a large stone "
            "statue of what appears to be the city's god, Atum the Almighty. Your only way into the city is through the "
            "doors, guarded by two lookouts who do not seem all that friendly.";
        }
        else
        {
            player_char.set_player_loc(obj_name);
            return "You arrive at the outer gates of the Farlands once again. The massive sandstone walls are still just "
            "as impressive as the first time, and the lookouts guarding the gate are still just as unfriendly.";
        }
    }
    else if (obj_name == "city square")
    {
        if (player_char.get_player_flag("talked_to_lookouts") && !obj.get_object_flag("been_to"))
        {
            obj.set_object_flag("been_to", true);
            player_char.set_player_loc(obj_name);

            return "You walk into the packed city square of the Farlands. The city square appears to be "
            "quite busy, but all of the locals seem down for some reason. This might be something worth checking out.";
        }
        else if (obj.get_object_flag("been_to"))
        {
            player_char.set_player_loc(obj_name);

            return "You arrive back at the city square. What do you want to do?";
        }
        else 
        {
            return "Nice try, but you haven't talked to the lookouts yet. "
            "Unless you want to get yourself killed, you should try talking to them first.";
        }
    }
    else if (obj_name == "coffee shop")
    {
        player_char.set_player_loc(obj_name);

		return "You walk through the front door of the coffee shop and are greeted by the "
        "nice smell of coffee. There are some friendly-looking locals hanging about, "
        "as well as some cups of coffee on the counter. What do you want to do?";
	}
    else if (obj_name == "general store")
    {
        player_char.set_player_loc(obj_name);

        return "You enter the general store named Nunu's General Store. There is a shopkeeper "
        "standing behind a desk, while clothes, toys, and shoes line the shelves within the store. "
        "What do you want to do?";
    }
    else if (obj_name == "sarabi's egyptian cuisine")
    {
        player_char.set_player_loc(obj_name);
        
        return "You enter the restaurant. Smells quite good, at least in your opinion. There are many locals "
        "around, enjoying their meals - maybe you should try and talk to them?";
    }
    else if (obj_name == "palace")
    {
        if (player_char.get_inv_item("armor of torren") && !player_char.get_player_flag("cannot_leave"))
        {
            player_char.set_player_loc(obj_name);
            if (player_char.get_player_flag("wearing_armor"))
            {
                return "You arrive at the walls surrounding the King's palace. On first glance, the place seems heavily guarded - "
                "you get the feeling it won't be easy to go inside the palace. If you want to get in, you'll probably need to find "
                "another entrance...";
            }
            else
            {
                return "You arrive at the walls surrounding the King's palace. On first glance, the place seems heavily guarded - "
                "you get the feeling it won't be easy to go inside the palace. If you want to get in, you'll probably need to find "
                "another entrance. You're feeling even more vulnerable than normal, though - maybe you should take advantage of that armor?";
            }
        }
        else if (!player_char.get_inv_item("armor of torren"))
        {
            return "You may be missing a improtant item. Maybe you should look around the city a little more.";
        }
        else if (player_char.get_player_flag("cannot_leave"))
        {
            return "You already alerted the guard at the side gate to your presence. Going back now would result in certain death.";
        }
    }
    else if (obj_name == "side gate")
    {
        player_char.set_player_loc(obj_name);

        return "You sneak around, moving to the gate at the side of the wall, and you come across "
        "a lone guard in front of an entrance to the inside of the palace. Now, what will you do next?";
    }
    else if (obj_name == "inside palace" && player_char.get_player_flag("knocked_guard_out"))
    {   
        if (player_char.get_player_flag("read_note"))
        {
            obj.set_object_flag("has_been", true);
            player_char.set_player_loc(obj_name);
            return "The inside of the palace is surprinsingly empty. Barely any furniture, guards, and a handful of torches "
            "lead to the potion room and Spyro's lair.";
        }
        else if (obj.get_object_flag("has_been"))
        {
            player_char.set_player_loc(obj_name);
            return "You are back at the main section of the palace.";
        }
        else
        {
            obj.set_object_flag("has_been", true);
            player_char.set_player_loc(obj_name);
            return "The inside of the palace is surprinsingly empty. Barely any furniture, guards, and a handful of torches "
            "that lead to two doors. Well, now you have a choice. Door one, or door two? Choose wisely...";
        }
    }
    else if (obj_name == "potion room")
    {
        if (player_char.get_player_flag("read_note"))
        {
            obj.set_object_flag("been_to", true);
            player_char.set_player_loc(obj_name);
            return "You head to the potion room, and as the name suggests, there are a lot of potions in the room. Try having a look around.";
        }
        else if (obj.get_object_flag("has_been"))
        {
            player_char.set_player_loc(obj_name);
            return "You are back at the potion room.";
        }
        else
        {
            player_char.set_player_loc(obj_name);
            return "You enter door one, and to your surprise, you see this room is full of potions. Try having a look around.";
        }
    }
    else if (obj_name == "spyro's lair")
    {
        if (player_char.get_player_flag("read_note") && !player_char.get_player_flag("has_potion"))
        {
            player_char.set_player_loc(obj_name);
            player_char.set_player_state(false);
            return "You enter Spyro's Lair. You see Spyro, the most powerful Sphynx in the land takes his "
            "claws and rips your flesh to shreds. Maybe you should try following the paper's instruction said next time.";
        }
        else if (!player_char.get_player_flag("read_note") && !player_char.get_player_flag("has_potion"))
        {
            player_char.set_player_loc(obj_name);
            player_char.set_player_state(false);
            return "You enter door two and you see a giant Sphynx. This sphynx takes his claws and rips your flesh to shreds. "
            "Maybe you would have known more about the layout of the palace if you had read the note.";
        }
        else if (player_char.get_player_flag("read_note") && player_char.get_player_flag("has_potion"))
        {
            player_char.set_player_loc(obj_name);
            return "You head to Spyro's lair to fight him with your potion. You feel more prepared now. You make eye contact with the huge creature, "
            "and a chill rushes down your neck. You should probably think about your next move carefully...";
        }
        else if (!player_char.get_player_flag("read_note") && player_char.get_player_flag("has_potion"))
        {
            player_char.set_player_loc(obj_name);
            return "You head into room number two with your potions. You feel more prepared to take on whatever is ahead of you. You make " 
            "eye contact with a huge Sphynx, and a chill rushes down your neck. You should probably think about your next move carefully...";
        }
    }
    else if (obj_name == "king's throne")
    {
        if (player_char.get_player_flag("read_note") && player_char.get_player_flag("throne_available"))
        {
            player_char.set_player_loc(obj_name);
            return "You walk into the throne room and see King Akhem. He doesn't look surprised to see you. "
            "'Face me, if you dare... heathen.' He stands in a battle stance before you.";
        }
        else if (!player_char.get_player_flag("read_note") && player_char.get_player_flag("throne_available"))
        {
            player_char.set_player_loc(obj_name);
            return "You walk into the ominous room and see King Akhem. He doesn't look surprised to see you. "
            "'Face me, if you dare... heathen.' He stands in a battle stance before you.";
        }
    }
    return "Location has not been implemented yet.";
}

/// \brief Checks if the player can reach a location from where they are currently positioned; if true, sends 
/// control to the `go_to` function for more checks and a descriptive return. If `go_to` moves the player, this 
/// function then also determines the new set of locations the player can reach using sets from `specificvars`
/// @param obj The `game_object`, passed by ref., that the player is interacting with
/// @param obj_name The name of the `game_object` the player is interacting with
/// @param player_char An instance of `player_info`, passed by ref., denoting the player's current state
/// @return A string describing the results of the player's action
std::string go(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj.get_object_type() != "location")
    {
        return "Yeah, that's not a location. Try again.";
    }

    std::string return_str;
    std::string prev_loc = player_char.get_player_loc();

    if (player_char.get_player_loc_set().contains(obj_name))
    {
        return_str = go_to(obj, obj_name, player_char);
    }
    else
    {
        return_str = "You can't reach that location from here.";
    }

    std::string new_loc = player_char.get_player_loc();

    if (prev_loc != new_loc) // Check if player's location is different
    {
        if (new_loc == "game start")
        {
            player_char.set_player_loc_set(specificvars::location_set_one);
        }
        else if (new_loc == "abandoned town")
        {
            player_char.set_player_loc_set(specificvars::location_set_two);
        }
        else if (new_loc == "farlands")
        {
            player_char.set_player_loc_set(specificvars::location_set_three);
        }
        else if (new_loc == "city square")
        {
            player_char.set_player_loc_set(specificvars::location_set_four);
        }
        else if (new_loc == "palace")
        {
            player_char.set_player_loc_set(specificvars::location_set_five);
        }
        else if (new_loc == "inside palace")
        {
            player_char.set_player_loc_set(specificvars::location_set_six);
        }
        else if (new_loc == "spyro's lair")
        {
            player_char.set_player_loc_set(specificvars::location_set_seven);
        }
    }

    return return_str;
}

/// @brief Finds the result of the player interacting with a `game_object` via the in-game "talk" command
/// @param obj The `game_object`, passed by ref., that the player is interacting with
/// @param obj_name The name of the `game_object` the player is interacting with
/// @param player_char An instance of `player_info`, passed by ref., denoting the player's current state
/// @return A string describing the results of the player's action
std::string talk_to(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj_name == "barkeep")
    {
        if (player_char.get_player_loc() == "tavern")
        {
            if (find_object("bandit").get_object_flag("is_alive"))
            {
                player_char.set_player_state(false);
                return "Considering the number of bandits, you probably should've guessed the barkeep wasn't going to do "
                "anything. While you try to get the barkeep's attention, the lead bandit takes the initiative and slashes "
                "at you. Luckily for you, he only cut off your head. Oh, wait, I've just been informed that's actually "
                "quite bad. Well, at least your death was quick.";
            }
            else if (!obj.get_object_flag("talked_to"))
            {
                obj.set_object_flag("talked_to", true);
                player_char.set_player_flag("npc_is_talking", true);
                return "Welcome to the Sand Dune Saloon. Sorry about the bandit, this town's been getting worse by the day, and it's hard to "
                "get any help around here. Take this drink, it's on the house - might not be much of a reward, but no-one can pass up a good "
                "drink, eh? Anyways. I gotta warn you, if you had any plans to stay around here, it'd be best to change them unless you want "
                "to keep fighting off bandits. My advice? I'd head east of here, to the Farlands. Admittedly, it's also quite the dangerous "
                "place, but I think you'd enjoy a lower risk of getting your head cut off anytime you try to walk in a building.";
            }
            else
            {
                player_char.set_player_flag("npc_is_talking", true);
                return "Ah, it's our saviour again! Welcome back to the Sand Dune Saloon. How are ya holding up? Been to the Farlands yet?";
            }
        }
        else
        {
            return "There is no barkeep in this area, are you looking for a drink or something?";
        }
    }
    else if (obj_name == "bandit")
    {
        if (player_char.get_player_loc() == "tavern" && obj.get_object_flag("is_alive"))
        {
            return "You try to talk to the bandit, but all he wants to talk about is how he wants to kill you and call you obscenities.";
        }
        else if (!obj.get_object_flag("is_alive"))
        {
            return "I don't think you can talk to the dead, so stop trying to talk to the dead bandit.";
        }
        else 
        {
            return "There is no bandit in this location. Why would you want to talk to a bandit right now?";
        }
    }
    else if (obj_name == "old lady")
    {
        if (player_char.get_player_loc() == "abandoned town" && obj.get_object_flag("is_alive"))
        {
            player_char.set_player_state(false);
            return "You try to talk to the old lady, but as you walk over, she suddenly turns around and stabs you. "
            "She takes all of your items, and then runs off. Looks like she didn't need any help after all...";
        }
        else if (!obj.get_object_flag("is_alive")) 
        {
            return "I don't think the 'old lady' wants to talk to you.";
        }
        else
        {
            return "What old lady are you talking about?"; 
        }
    }
    else if (obj_name == "locals")
    {
		if (player_char.get_player_loc() == "sarabi's egyptian cuisine")
        {
            return "You pass by a woman and her friend talking over food. Before you even think about eavesdropping, "
            "she does the hard work for you by loudly stating that she can't stand King Akhem. 'I don't care if "
            "I get arrested by saying this!', she rages. 'People like him are lesser than the dirt under my feet "
            "when I step foot outside!'";
        }
        else if (player_char.get_player_loc() == "coffee shop")
		{
            player_char.add_inv_item(find_object("coffee"));
            return "You come across a man who is having a coffee. You ask if you can sit down, "
            "and he accepts. He orders you a coffee as well. You guys make small talk about where you " 
            "are both from and what to do in the Farlands. He lets you know that you should not go near the "
            "Palace unless you want to get in trouble. He says that King Akhem will kill anyone who gets in "
            "his way and will obtain power by any means possible. You thank him for his time, and get up from "
            "the table with your coffee.";
        }
        else
        {
            return "There are no locals in the area that you are in. Maybe try looking somewhere else.";
        }
    }
    else if (obj_name == "shopkeeper")
    {
        if (player_char.get_player_loc() == "general store")
        {
            if (!player_char.get_player_flag("offered_armor"))
            {
                player_char.set_player_flag("offered_armor", true);

                return "You approach the shopkeeper and say hello. She gives a shy hello back and asks what she "
                "could do for you. You begin to ask about the town and what it has to offer. She replies saying "
                "that she doesn't like this town because of King Akhem, and that she wishes that someone would put "
                "a stop to him. She takes notice that you are somewhat of a warrior and sees that you lack any type of "
                "armor. She pulls out the Armor of Torren, and says, 'You must take this and find a way to defeat King "
                "Akhem, I just know that you are the chosen one. Please, you are our only hope. Take this gift.' She "
                "holds out the armor for you to take.";
            }
            else
            {
                return "You approach the shopkeeper and say hello. She gives a shy hello back and asks what she "
                "could do for you. You begin to ask about the town and what it has to offer. She replies saying "
                "that she doesn't like this town because of King Akhem, and that she wishes that someone would put "
                "a stop to him.";
            }
        }
        else
        {
            return "You're not at a store; where do you expect to see a shopkeeper?";
        }
    }
    else if (obj_name == "lookouts")
    {
        if (player_char.get_player_loc() == "farlands") 
        {
            if (!player_char.get_player_flag("talked_to_lookouts"))
            {
                player_char.set_player_flag("talked_to_lookouts", true);

                return "You politely ask if you can get into the city. The lookouts ask you what your "
                "business is here. You say that you are just passing by. One of them responds with 'If you "
                "cause any trouble here, we will find you. You've been warned'. These guys have such great "
                "manners, don't they? Well, either way, congratulations! You've managed to reach the Farlands. "
                "You should probably head inside to the city square before the lookouts change their mind about you.";
            }
            else
            {
                return "You politely ask if you can get into the city. The lookouts ask you what your "
                "business is here. You say that you are just passing by. One of them responds with 'If you "
                "cause any trouble here, we will find you. You've been warned'.";
            }
        }
        else
        {
            return "There aren't any lookouts at your current location.";
        }
    }
    else if (obj_name == "guards")
    {
        if (player_char.get_player_loc() == "palace")
        {
            player_char.set_player_state(false);
            return "You attempt to talk to the big group of guards who are patrolling the palace and, without warning, "
            "you find yourself surrounded. These guards are really effective at keeping intruders out, huh?";
        }
        else 
        {
            return "There aren't any guards at your current location. Maybe you'll see some later?";
        }
    }
    else if (obj_name == "guard")
    {
        if (player_char.get_player_loc() == "side gate")
        {
            player_char.set_player_flag("cannot_leave", true);
            return "You're not supposed to be here, and the guard knows that. 'State your business citizen, "
            "or I will have to arrest you for failing to obey the laws of King Akhem', he says. Well, great "
            "job, the guard now knows you're here. You can't leave now, so you better make your next actions count.";
        }
        else
        {
            return "There's no guard at your current location. Maybe you'll see one later, who knows?";
        }
    }
    else if (obj_name == "spyro")
    {
        if (player_char.get_player_loc() == "spyro's lair")
        {
            if (obj.get_object_flag("is_alive"))
            {
                player_char.set_player_state(false);
                return "You try to talk to Spyro to distract him. You say, 'What's that over there?' and point to "
                "a wall. He does not fall for that trick, and flies toward you to bite your head off.";    
            }
            else
            {
                return "You have already killed the mighty creature. It can no longer talk.";
            }
        }
    }
    else if (obj_name == "king akhem")
    {
        if (player_char.get_player_loc() == "king's throne")
        {
            player_char.set_player_state(false);
            return "You try and talk to King Akhem to distract him. Unfortunately, he does "
            "not pay attention to your silly games, and strikes you in the face with his "
            "huge hammer. You die instantly.";
        }
        else
        {
            return "You are not at the King's Throne yet. Look at you, trying to sneak in without "
            "doing the other side missions first. For shame, for shame.";
        }
    }
    else if (obj.get_object_type() != "location")
    {
        return "You don't see any " + obj_name + " to talk to.";
    }
    return "Invalid action & object combination; try again.";
}

/// @brief Finds the result of the player interacting with a `game_object` via the in-game "look" command
/// @param obj The `game_object`, passed by ref., that the player is interacting with
/// @param obj_name The name of the `game_object` the player is interacting with
/// @param player_char An instance of `player_info`, passed by ref., denoting the player's current state
/// @return A string describing the results of the player's action
/// @note This function is called whenever the player uses the similar "examine" command
std::string look_at(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (player_char.get_player_loc() == "coffee shop" && obj_name == "locals")
    {
        obj.set_object_loc("coffee shop");
        obj.set_object_desc("These locals seem like they have had a long day. People have dirt all on their "
        "clothes and in their hair, many are sleeping at the tables they're sitting at. However, the people seem "
        "to have smiles on their faces.");
        return obj.get_object_desc();
    }
    else if (player_char.get_player_loc() == "sarabi's egyptian cuisine" && obj_name == "locals")
    {
        obj.set_object_loc("sarabi's egyptian cuisine");
        obj.set_object_desc("These locals seem to be wealthier than those at the coffee shop. They look at "
        "you and scoff as if you are not worthy enough to be in the restaurant itself. Who do they think they "
        "are?");
        return obj.get_object_desc();
    }
    else if (player_char.get_player_loc() == "abandoned town" && obj_name == "old lady")
    {
        obj.set_object_flag("known_evil", true);
        return obj.get_object_desc();
    }
    else if (obj_name == "around")
    {
        return find_object(player_char.get_player_loc()).get_object_desc();
    }
    else if (obj.get_object_loc() == "playerinventory" ||
        (player_char.get_player_loc() == obj_name) ||
        (player_char.get_player_loc() == obj.get_object_loc()) ||
        player_char.get_player_loc_set().contains(obj.get_object_name()))
    {
        return obj.get_object_desc();
    }
    else
    {
        return "You can't see any " + obj_name + ".";
    }
}

/// @brief Finds the result of the player interacting with a `game_object` via the in-game "attack" command
/// @param obj The `game_object`, passed by ref., that the player is interacting with
/// @param obj_name The name of the `game_object` the player is interacting with
/// @param player_char An instance of `player_info`, passed by ref., denoting the player's current state
/// @return A string describing the results of the player's action
std::string attack(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj.get_object_type() == "character")
    {
        if (player_char.get_player_loc() == "abandoned town")
        {
            if (obj_name == "old lady")
            { 
                if (!obj.get_object_flag("known_evil"))
                {
                    return "Attacking an old lady? You can't be serious!";
                }
                else if (!obj.get_object_flag("is_alive"))
                {
                    return "The 'old lady' is already dead, you don't need to keep attacking them anymore.";
                }
                else
                {
                    obj.remove_object_flag("is_alive");
                    return "This old lady's disguise isn't going to fool you. You murder the "
                    "old lady in broad daylight yet no-one bats an eye - as you expected, the "
                    "'old lady' was a bandit in a disguise trying to steal money from "
                    "unsuspecting victims.";
                }
            }
        }
        else if (player_char.get_player_loc() == "tavern")
        {
            if (obj_name == "bandit")
            {
                if (obj.get_object_flag("is_alive"))
                {
                    obj.remove_object_flag("is_alive");
                    return "You take out your sword, and with a mighty slash, you defeat the bandit. "
                    "His 'friends' take one look at you and decide to run away. Meanwhile, the rest "
                    "of the bar doesn't seem to take any notice of your actions, except for the barkeep. "
                    "He beckons you over to the bar, and sets a drink down in front of you.";
                }
                else if (!obj.get_object_flag("is_alive"))
                {
                    return "He's already dead, are you losing it?";
                }
            }
            else if (obj_name == "barkeep")
            {
                return "Hey, you've only just met the guy, have some self discipline!";
            }
        }
        else if (player_char.get_player_loc() == "farlands")
        {
            if (obj_name == "lookouts")
            {
                player_char.set_player_state(false);
                return "Attacking two lookouts at one time? Bold move. They might "
                "just be lookouts, but they are still much stronger than someone "
                "with just a sword and some mediocre skills. They strike you down "
                "before you can even land a single hit.";
            }
        }
        else if (player_char.get_player_loc() == "palace")
        {
            if (obj_name == "guards")
            {
                player_char.set_player_state(false);
                return "You attempt to attack the guards head on. However, they stab you multiple "
                "times, killing you. Did you really think that you were strong enough to take on "
                "multiple palace soldiers? Feeble minded...";
            }
        }
        else if (player_char.get_player_loc() == "side gate")
        {
            if (obj_name == "guards")
            {
                player_char.set_player_state(false);
                return "You attempt to attack the guards from the side. Considering you're only "
                "one person, trying to flank them doesn't work. The guards surround and stab you "
                "before you can even blink.";
            }
            else if (obj_name == "guard") 
            {
                if (!obj.get_object_flag("is_unconscious"))
                {
                    obj.set_object_desc("This is the guard you just knocked out to get inside the palace.");
                    obj.set_object_flag("is_unconscious", true);
                    player_char.set_player_flag("knocked_guard_out", true);
                    find_object("paper").set_object_loc("side gate");

                    return "The guard sees that his toga is becoming loose and drops his sword to "
                    "tighten it. You use this opportunity to hit the guard upside the head with "
                    "the end of your sword, rendering him unconscious. As he hits the ground, "
                    "you notice a paper falls out of his toga.";
                }
                else
                {
                    return "I don't think it's a good idea to kill this guard. His friends might "
                    "come look for him later. It'd be in your best interest to try something else.";
                }
            }
        }
        else if (obj_name == "shopkeeper")
        {
            if (player_char.get_player_loc() == "general store")
            {
                player_char.set_player_state(false);
                return "Your sword is strong. However, the shopkeeper takes one of the wooden toys and "
                "hits you square in the temple, knocking you out. Nice job, buddy.";
            }
            else 
            {
                return "There's no shopkeeper at your location. Maybe try looking in a store, eh?";
            }
        }
        else if (obj_name == "locals")
        {
            if (player_char.get_player_loc() == "coffee shop")
            {
                return "Why are you trying to attack someone who hasn't done anything to you? \n"
                "I'm going to let you try again...";
            }
            else if (player_char.get_player_loc() == "sarabi's egyptian cuisine")
            {
                obj.remove_object_flag("is_alive");

                return "The local was unarmed and not a threat. Thus, you take your sword "
                "out and stab at her chest. She dies in front of you slowly and says, 'Why…?' while "
                "slowly closing her eyes. Do you feel happy about killing the innocent? Shameful…";
            }
            else if (player_char.get_player_loc() == "sarabi's egyptian cuisine" && !obj.get_object_flag("is_alive"))
            {
                return "You have already killed the poor local here. Move on you before you get arrested "
                "- and besides, you're scaring people now.";
            }
            else 
            {
                return "There are no locals nearby. Scratch that, why would you even try to attack the locals?";
            }
        }
        else if (obj_name == "spyro")
        {
            if (player_char.get_player_loc() == "spyro's lair")
            {
                if (player_char.get_player_flag("is_strong") && !obj.get_object_flag("is_injured"))
                {
                    obj.set_object_flag("is_injured", true);
                    player_char.set_player_flag("throne_available", true);

                    return "With the stregnth you gain from the strength potion, you gain strength throughout"
                    "your body, and you use this strength to jump up 10 feet into the air and slash"
                    "Spyro's neck. He is badly wounded, but he pleads for his life.\n Do you want to"
                    "spare his life and advance to the King's Throne?";
                }
                else if (player_char.get_player_flag("is_strong") && obj.get_object_flag("is_injured"))
                {
                    obj.remove_object_flag("is_alive");

                    return "You decide to stab Spyro in the heart. While his blood oozing from his chest, "
                    "he lets out a loud roar in pain. His body slowly stops moving, and his eyes close. You "
                    "have slain the mighty beast, and remove your sword out of his body. The path to King "
                    "Akhem's Throne is now clear. Continue your journey.";
                }
                else if (player_char.get_player_flag("the_confuser"))
                {
                    obj.remove_object_flag("is_alive");

                    return "While Spyro is confused, you see this as a great opportunity to attack him. "
                    "You slice off his head, and the sphynx is no more. You feel a bit hollow, though - "
                    "it wasn't a very fair fight.";
                }
                else if (!obj.get_object_flag("is_alive"))
                {
                    return "Come on now, don't mutilate the beast's body anymore. Let him rest now.";
                }
                else if (!player_char.get_player_flag("is_strong") || !player_char.get_player_flag("the_confuser"))
                {
                    player_char.set_player_state(false);

                    return "You attacked the sphynx head on without using any potions. You were immediately ripped to shreads.";
                }
            }
            else
            {
                return "I don't see Spyro here. What are you trying to attack? You must be losing it.";
            }
        }
        else if (obj_name == "king akhem")
        {
            if (player_char.get_player_loc() == "king's throne")
            {
                if (!player_char.get_player_flag("wearing_armor") && (!obj.get_object_flag("attacked_one") && !obj.get_object_flag("final_attack")))
                {
                    obj.set_object_flag("attacked_one", true);
                    player_char.set_player_state(false);
                    return "You pull out your sword and charge at King Akhem. He dodges the first attack."
                    "However, he charges at you and attempts to strike you in the chest with his colossal hammer."
                    "He strikes you at the center of your skull, killing you instantly.";
                }
                else if (player_char.get_player_flag("wearing_armor"))
                {
                    obj.set_object_flag("attacked_one", true);
                    player_char.remove_player_flag("wearing_armor");
                    return "You pull out your sword and charge at King Akhem. He dodges the first attack. "
                    "However, he charges at you and attempts to strike you in the chest with his colossal hammer. "
                    "You then dodge out of the way at the last second, but he shatters your armor. "
                    "It might've been quite rubbish, but the armor saved your life from his mighty blow.";
                }
                else if (obj.get_object_flag("attacked_one"))
                {
                    obj.remove_object_flag("attacked_one");
                    obj.set_object_flag("final_attack", true);

                    return "Instead of taking him head on, you circle behind him for an attack from the rear. "
                    "He takes a while to spin around to defend himself, and you take this opportunity to slash him "
                    "in the nape. This causes him to gush out blood.";
                }
                else if (obj.get_object_flag("final_attack"))
                {
                    obj.remove_object_flag("final_attack");
                    obj.remove_object_flag("is_alive");
                    player_char.set_player_flag("finished_game", true);
                    return "King Akhem has fallen on one knee. His body has gone cold, and he is panting trying "
                    "to get the blood from his nape to stop leaking out of his body. Quickly, you slice at his legs "
                    "and arms, and stab him in the heart. King Akhem has fallen. The citizens of the Farlands rejoice "
                    "now that King Akhem's rule is finished. You are declared a hero, and you live the rest of your "
                    "life happy in the Farlands.";
                }
            }
            else 
            {
                return "I don't see King Akhem here.";
            }
        }        
    }
    else if (obj.get_object_type() == "item")
    {
        return "Hey, you never know if you might need that item later on. Try something else first.";
    }

    return "Whatever you are trying to attack, it's not here. Go look somewhere else.";
}

/// @brief Finds the result of the player interacting with a `game_object` via the in-game "read" command
/// @param obj The `game_object`, passed by ref., that the player is interacting with
/// @param obj_name The name of the `game_object` the player is interacting with
/// @param player_char An instance of `player_info`, passed by ref., denoting the player's current state
/// @return A string describing the results of the player's action
std::string read(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj_name == "paper" && player_char.get_player_loc() == "side gate" && player_char.get_player_flag("knocked_guard_out"))
    {
        player_char.set_player_flag("read_note", true);
        return obj.get_object_desc();
    }
    else if (obj.get_object_name() == "book" && player_char.get_player_loc() == obj.get_object_loc())
    {
        return "Potion Room Project Log: \nFire Potion: When the liquid is exposed to air, the liquid turns into flying fire. \n"
        "This is a prototype, so we must be careful testing it (Color: Red. \n Smell: hot coals).\n "
        "Hunger Potion: When this is thrown at someone or consumed by mouth, the victim will become"
        "famished. (Color: Yellow. \n Smell: baked chicken and fresh bread) \n"
        "When this potion is thrown at someone, they will enter a state of amnesia, as well as"
        "forget the reason that they are fighting you. This will give you the chance to sneak past them"
        "to do something else. (Color: Green. \n Smell: herbs and greens)\n"
        "When this potion is splashed on the skin or consumed by mouth, your muscles begin to expand, "
        "and you will feel like a mighty warrior. (Color: Purple. \n Smell: blood, sweat and tears)\n";
    }
    else
    {
        return "There's nothing to read over here.";
    }
}

/// \brief Determines which function should be called to get the appropriate 
/// results of whatever action the player has decided to take during gameplay
/// @param act A string containing the name of the command that the player has chosen
/// @param obj The `game_object`, passed by ref., that the player is interacting with
/// @param player_char An instance of `player_info`, passed by ref., denoting the player's current state
/// @return A string describing what has happened to the player
std::string main_action(std::string act, game_object &obj, player_info &player_char) 
{
    std::string result = "";
    std::string obj_name = obj.get_object_name();
    
    if (act == "use" || act == "drink")
    { 
        result = use(obj, obj_name, player_char);
    }
    else if (act == "take" || act == "get" || act == "grab")
    {
        result = take(obj, obj_name, player_char);
    }
    else if (act == "go")
    {
        result = go(obj, obj_name, player_char);
    }
    else if (act == "look" || act == "examine")
    {
        result = look_at(obj, obj_name, player_char);
    }
    else if (act == "read")
    {
        result = read(obj, obj_name, player_char);
    }
    else if (act == "talk")
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