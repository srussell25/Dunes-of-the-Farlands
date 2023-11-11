#ifndef OBJECTACTIONS_HPP
#define OBJECTACTIONS_HPP

#include "classesmisc.hpp"

// Add proper function description here
std::string use(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj_name == "whiskey")
    {
        if (player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "tavern")
        {
            player_char.remove_inv_item(obj_name, true);
            return "Man, that was a pretty good whiskey!";
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
    /* TODO: Use whiskey as a template for coffee - remember, you get it after talking to the locals in the coffee shop
    else if (obj_name == "coffee")
    {
        if (player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "tavern")
        {
            player_char.remove_inv_item(obj_name, true);
            return "Man, that was a pretty good whiskey!";
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
    */
    else if(obj_name == "fire potion")
    {
        if(player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "spyro's lair")
        {
            player_char.set_player_state(false);
            player_char.remove_inv_item(obj_name, true);

            return "The potion you used on Spyro caused him to absorb the fire within his"
            "skin and melts you into a crisp.";
        }
        else
        {
            return "I don't think this is the best place to use it. I think you should use the potion"
            "where Spyro is.";
        }
    }
    else if(obj_name == "confusion potion")
    {
        if(player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "spyro's lair")
        {
            player_char.set_player_flag("the_confuser", true);
            player_char.remove_inv_item(obj_name, true);

            return "You grab the confusion potion out of your inventory, unscrew the bottle,"
            "and chunk it at Spyro. This causes him to get dizzy, forget where he is, and fall into confusion."
            "You quickly use this opportunity to sneak into King Akhem's throne room.";
        }
        else
        {
            return "I don't think this is the best place to use it. I think you should use the potion"
            "where Spyro is.";
        }
    }
    else if(obj_name == "hunger potion")
    {
        if(player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "spyro's lair")
        {
            player_char.set_player_state(false);
            player_char.remove_inv_item(obj_name, true);

            return "The potion you used on Spyro caused him to get hungry and he eats you.";
        }
        else
        {
            return "I don't think this is the best place to use it. I think you should use the potion"
            "where Spyro is.";
        }
    }
    else if(obj_name == "strength potion")
    {
        if(player_char.get_inv_item(obj_name) && player_char.get_player_loc() == "spyro's lair")
        {
            player_char.set_player_state(false);
            return "Your strength doubles, and your muscles grow exponentially. You can now jump higher,"
            "run faster, and your testosterone levels plummet.";
        }
        else
        {
            return "I don't think this is the best place to use it. I think you should use the potion"
            "where Spyro is.";
        }
    }
    return "Invalid action & object combination; try again.";
}

// Add proper function description here
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
            return "unimplemented fail state"; // add unique fail text
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
            return "unimplemented fail state"; // add unique fail text (check if player already has coffee?)
        }
    }
    else if(obj_name == "armor of torren")
    {
        if (player_char.get_player_loc() == "general store" && obj.get_object_loc() == "general store")
        {
            // needs to be implemented
            // check that the shopkeeper has asked you to take it; use a flag
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
            return "Can't you see the note? It says don't take the book, ya bozo.";
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
    }
    else if (obj_name == "paper")
    {
        if (player_char.get_player_loc() == "side gate" && obj.get_object_loc() == "side gate")
        {
            player_char.add_inv_item(obj);
            return "The paper was added to your inventory. It seems to have some important script, "
            "maybe you should try reading it?";
        }
    }
    else if(obj_name == "fire potion")
    {
        if(player_char.get_player_loc() == "potion room" && player_char.get_player_flag("has_potion") == false)
        {
            player_char.add_inv_item(obj);
            player_char.set_player_flag("has_potion", true);
            return "Fire potion has been added to inventory";
        }
        else if(player_char.get_player_loc() == "potion room" && player_char.get_player_flag("has_potion"))
        {
            return "Sorry, you already took a potion. You only have one slot in your inventory for a potion.";
        }
        else
        {
            return "The item 'fire potion' is not in this location. Try something else.";
        }
    }
    else if(obj_name == "confusion potion")
    {
        if(player_char.get_player_loc() == "potion room" && player_char.get_player_flag("has_potion") == false)
        {
            player_char.add_inv_item(obj);
            player_char.set_player_flag("has_potion", true);
            return "Confusion potion has been added to inventory";
        }
        else if(player_char.get_player_loc() == "potion room" && player_char.get_player_flag("has_potion"))
        {
            return "Sorry, you already took a potion. You only have one slot in your inventory for a potion.";
        }
        else
        {
            return "The item 'confusion potion' is not in this location. Try something else.";
        }
    }
    else if(obj_name == "hunger potion")
    {
        if(player_char.get_player_loc() == "potion room" && player_char.get_player_flag("has_potion") == false)
        {
            player_char.add_inv_item(obj);
            player_char.set_player_flag("has_potion", true);
            return "Hunger potion has been added to inventory";
        }
        else if(player_char.get_player_loc() == "potion room" && player_char.get_player_flag("has_potion"))
        {
            return "Sorry, you already took a potion. You only have one slot in your inventory for a potion.";
        }
        else
        {
            return "The item 'hunger potion' is not in this location. Try something else.";
        }
    }
    else if(obj_name == "strength potion")
    {
        if(player_char.get_player_loc() == "potion room" && player_char.get_player_flag("has_potion") == false)
        {
            player_char.add_inv_item(obj);
            player_char.set_player_flag("has_potion", true);
            return "strength potion has been added to inventory";
        }
        else if(player_char.get_player_loc() == "potion room" && player_char.get_player_flag("has_potion"))
        {
            return "Sorry, you already took a potion. You only have one slot in your inventory for a potion.";
        }
        else
        {
            return "The item 'strength potion' is not in this location. Try something else.";
        }
    }
    
    return "This action cannot be performed here. Try something else.";
}

// Add proper function description here
std::string go_to(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj_name == "oasis")
    {   
        player_char.set_player_loc(obj_name);
        player_char.set_player_state(false);
        return "You make your way over to the oasis, but when you get there, "
        "a frog suddenly jumps onto your leg. It's a poisonous frog. You die in seconds.";
    }
    else if (obj_name == "abandoned town")
    {
        obj.set_object_flag("been_to", true);
        player_char.set_player_loc(obj_name);
        return "You arrive at the town named Nekhem. The town isn't necessarily abandoned, "
        "but it's overrun by thugs and bandits. The walls are broken, and people have "
        "malicious looks on their faces. You see a tavern called the Sand Dune Saloon nearby, "
        "but your gaze also happens upon an old lady who seems to be struggling.";
    }
    else if (obj_name == "tavern")
    {
        obj.set_object_flag("been_to", true);
        player_char.set_player_loc(obj_name);
        return "You enter into the tavern. You try to go up to the bar to ask for directions, "
        "but the bar is heavily crowded, and you end up accidentally stepping on a stranger's foot. "
        "He stands up, along with his pals, and draws his sword; you've come across a bandit and his crew!";
    }
    else if (obj_name == "farlands")
    {
        obj.set_object_flag("been_to", true);
        player_char.set_player_loc(obj_name);
        return "When arriving at the outer gates of the Farlands, you see that this place is surrounded by a "
        "huge sandstone wall that seems to surround the entire city. Spews of fire are emitted from a large stone "
        "statue of what appears to be the city's god, Atum the Almighty. Your only way into the city is through the "
        "doors, guarded by two lookouts who do not seem all that friendly.";
    }
    else if (obj_name == "coffee shop")
    {
        obj.set_object_flag("been_to", true);
        player_char.set_player_loc(obj_name);
		return "You enter the coffee shop by walking through the front door.";
	}
    else if (obj_name == "general store")
    {
        obj.set_object_flag("been_to", true);
        player_char.set_player_loc(obj_name);
        return "You enter the store.";
    }
    else if (obj_name == "sarabi's egyptian cuisine")
    {
        obj.set_object_flag("been_to", true);
        player_char.set_player_loc(obj_name);
        return "You enter the restaurant. Smells good in here.";
    }
    else if (obj_name == "palace")
    {
        obj.set_object_flag("been_to", true);
        player_char.set_player_loc(obj_name);
        return "You arrive at the walls surrounding the King's palace. On first glance, the place seems heavily guarded - "
        "you get the feeling it won't be easy to go inside the palace. Try to find a in...";
    }
    /* TODO: Change the following so that the player enters 'inside palace' first, gets dialogue, and then has to choose which place to go to
    else if (obj_name == "inside palace")
    {   
        player_char.set_player_loc(obj_name);
        // check if the player read the note, give different dialogue for the following rooms if the player didn't read it
        return "";
    }
    else if (obj_name == "potion room")
    {
        obj.set_object_flag("been_to", true);
        if (player_char.get_player_flag("knocked_guard_out"))
        {
            player_char.set_player_loc(obj_name);
            return "you enter the palace and head to the potion room. As you may expect there are a lot of potions in this room. "
            "maybe you can look around?";
        }
    }
    else if (obj_name == "spyro's lair")
    {
        obj.set_object_flag("been_to", true);
        if (player_char.get_player_flag("knocked_guard_out"))
        {
            player_char.set_player_loc(obj_name);
            player_char.set_player_state(false);
            return "you enter the palace and enter Spyro's Lair. You see Spyro, the most powerful Sphynx in the land takes his"
            "claws and rips your flesh to shreds. Maybe you should try following the paper's instruction said next time.";
        }
        else if (player_char.get_player_flag("has_potion") && player_char.get_player_loc() == "potion room")
        {
            return "You head to Spyro's lair to fight him with your potion. You feel more prepared now. You make eye contact with the huge creature,"
            "and a chill rushes down your neck. You should probably think about your next move carefully...";
        }
        else if (player_char.get_player_loc() == "potion room" && player_char.get_player_flag("has_potion") == false)
        {
            player_char.set_player_state(false);
            return "You go into the Spyro's lair unprepared with no potions to use. Since you are not as strong as you think you are,"
            "he rips up your body limb from limb, with only a your skull remaining.";
        }
    }
    else if (obj_name == "king's throne")
    {
        obj.set_object_flag("been_to", true);
        if (player_char.get_player_flag("throne_available") || player_char.get_player_flag("the_confuser"))
        {
            player_char.set_player_loc(obj_name);
            return "You walk into the throne room and see King Akhem. He doesn't look surprised to see you."
            "'Face me, if you dare... heathen.' He stands in a battle stance before you.";
        }
        else
        {
            return "You cannot head to this location just yet. Try something else.";
        }
    }
    */
    return "Location has not been implemented yet.";
}

// Add proper function description here
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
        else if (new_loc == "town square")
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
    }

    return return_str;
}

// Add proper function description here
std::string talk_to(game_object &obj, std::string obj_name, player_info &player_char)
{// add a function for bandit and check flag "is_alive" and do the same for old lady
    if (obj_name == "barkeep")
    {
        if (player_char.get_player_loc() == "tavern")
        {
            obj.set_object_flag("talked_to", true);
            return "Welcome to the Sand Dune Saloon. I'm the barkeep. Here's a drink, it's on the house; I can tell you're good people. "
            "I must warn you though: there is nothing worth staying for at this town, that is, unless you want to get yourself killed by "
            "one of the locals. If I were you, I'd recommend heading east of here, to the Farlands. It's quite the dangerous area in its "
            "own right, but you'll find more to do over in that region.";
        }
        else
        {
            return "The barkeep is in the tavern, not here.";
        }
    }
    else if (obj_name == "old lady")
    {
        if (player_char.get_player_loc() == "abandoned town")
        {
            player_char.set_player_state(false);
            return "You try to talk to the old lady, but as you walk over, she suddenly turns around and stabs you. "
            "She takes all of your items, and then runs off. Looks like she didn't need any help after all...";
        }
        else
        {
            return "The old lady is not in this area."; 
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
            return "You approach the shopkeeper and say hello. She gives a shy hello back and asks what she "
            "could do for her. You begin to ask about the town and what it has to offer. She replies saying "
            "that she doesn't like this town because of King Akhem, and that she wishes that someone would put "
            "a stop to him. She takes notice that you are somewhat of a warrior and sees that you lack any type of "
            "armor. She pulls out the Armor of Torren, and says, 'You must take this and find a way to defeat King "
            "Akhem, you are the chosen one. Please... you are our only hope. Here, please take this gift.' You "
            "are offered to take the armor.";
            
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
            /* TODO: Rewrite so that a flag is set which allows the player to move into the city square; change the dialogue to match
            player_char.set_player_loc("city square");
            return "You politely ask if you can get into the city. The lookouts ask you what your "
            "business is here. You say that you are just passing by. One of them responds with 'If you "
            "cause any trouble here, we will find you. You've been warned'. These guys have such great "
            "manners, don't they? Well, either way, congratulations! You've managed to reach the City "
            "Square of the Farlands.";
            */
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
            return "The guard tells you, 'State your business civilian, or I will have to resort in arresting "
            "you for failing to obey the laws of King Akhem'. He examines you while saying this, "
            "and spits at your feet.";
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
            player_char.set_player_state(false);
            return "You try to talk to Spyro to distract him. You say, 'What's that over there?' and point to "
            "a wall. He does not fall for that trick, and flies toward you to bite your head off.";
        }
        else
        {
            return "You are not in Spyro's Lair yet. I understand you are trying to skip apart of the game to"
            "get to some of the good stuff, but I will not allow it.";
        }
    }
    else if (obj_name == "king akhem")
    {
        if (player_char.get_player_loc() == "king's throne")
        {
            player_char.set_player_state(false);
            return "You try and talk to King Akhem to distract him. Unfortunately, he does "
            "not pay attention to your silly games, and strikes you in the face with " 
            "his huge Hammer. You die instantly.";
        }
        else
        {
            return "You are not at the King's Throne yet. Look at you, trying to sneak in without "
            "doing the other side missions first. For shame, for shame.";
        }
    }

    return "Invalid action & object combination; try again.";
}

// Add proper function description here
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
    else if (player_char.get_player_loc() == obj.get_object_loc() || player_char.get_player_loc() == obj_name)
    {
        return obj.get_object_desc();
    }
    else
    {
        return "You can't see any " + obj_name + ".";
    }
}

// Add proper function description here
std::string attack(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj.get_object_type() == "character")
    {
        if (player_char.get_player_loc() == "abandoned town")
        {
            if (obj_name == "old lady")
            {
                return "Attacking an old lady? You can't be serious!";
            }
            else if(obj_name == "old lady" && obj.get_object_flag("known_evil")) 
            {
                obj.remove_object_flag("is_alive");
                return "This old lady's disguise isn't going to fool you. You murder the "
                "old lady in cold blood in broad daylight. You stand over her and unveil her "
                "disguise, to find that it was a bandit this whole time trying to steal money from "
                "unsuspecting victims.";
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
            }
            else if (obj_name == "barkeep")
            {
                return "Hey, you've only just met the guy, have some self discipline!";
            }
        }
        else if (player_char.get_player_loc() == "farlands" || player_char.get_player_loc() == "gate")
        {
            if (obj_name == "guards")
            {
               player_char.set_player_state(false);
                return "Attacking two guards at one time? Bold move... \n"
                "The guards are much stronger than someone with one sword and mediocre skills. "
                "They beat you to death as soon as you try and unsheathe your sword.";
            }
            else 
            {
                return "Whatever you are trying to attack, it's not here. Go look somewhere else.";
            }
        }
        else if (player_char.get_player_loc() == "palace" || player_char.get_player_loc() == "side gate")
        {
            if (obj_name == "guards")
            {
                player_char.set_player_state(false);
                return "You attempt to attack the guards head on. However, they stab you multiple "
                "times, killing you. Did you really think that you were strong enough to take on "
                "multiple Palace Soldiers? Feeble minded...";
            }
            if(obj_name == "guard" && obj.get_object_flag("is_unconscious"))
            {
                return "I don't think it's a good idea to kill this guard. His guard friends might"
                "come look for him later. It'd be best to try something else.";
            }
            if (obj_name == "guard") 
            {
                obj.set_object_desc("this is the guard you just knocked out to get inside the palace.");
                obj.set_object_flag("is_unconscious", true);
                player_char.set_player_flag("knocked_guard_out", true);

                return "The guard sees that his toga is becoming loose and drops his sword to "
                "tighten it. You use this opportunity to hit the guard upside the head with "
                "the end of your sword, rendering him unconscious. As he hits the ground, "
                "you notice a paper falls out of his toga.";
            }
            else return "whatever you are trying to attack, its not here. Go look somewhere else.";
        }
        else if (obj_name == "shopkeeper")
        {
            if (player_char.get_player_loc() == "general store")
            {
                player_char.set_player_state(false);
                return "Your sword is strong. However, the shopkeeper takes one of the wooden toys and "
                "hits you in the temple of your head, causing you to hit your head on a table and die.";
            }
            else 
            {
                return "There's no shopkeeper at your location. Maybe try looking in a store, eh?";
            }
        }
        else if(obj_name == "locals")
        {
            if(player_char.get_player_loc() == "coffee shop")
            {
                return "Why are you trying to attack someone who hasn't done anything to you? \n"
                "I'm going to let you try again...";
            }
            else if(player_char.get_player_loc() == "Sarabi's Kitchen Cuisine")
            {
                return "The local was unarmed and not a threat. Thus, you take your sword"
                "out and stab at her chest. She dies in front of you slowly and says, 'Why…?' while"
                "slowly closing her eyes. Do you feel happy about killing the innocent? Shameful…";
            }
        }
        else if(obj_name == "spyro")
        {
            if(player_char.get_player_loc() == "spyro's lair" && 
            player_char.get_player_flag("is_strong") && obj.get_object_flag("is_injured") == false)
            {
                obj.set_object_flag("is_injured", true);
                player_char.set_player_flag("throne_available", true);

                return "With the stregnth you gain from the strength potion, you gain strength throughout"
                "your body, and you use this strength to jump up 10 feet into the air and slash"
                "Spyro's neck. He is badly wounded, but he pleads for his life.\n Do you wwant to"
                "spare his life and advance to the King's Throne?";
            }
            else if(player_char.get_player_loc() == "spyro's lair" && 
            player_char.get_player_flag("is_strong") && obj.get_object_flag("is_injured"))
            {// if the player decides to kill Spyro
                obj.remove_object_flag("is_alive");
                return "You decide to stab Spyro in the heart. While his blood oozing from his chest,"
                "he lets out a loud roar in pain. His body slowly stops moving, and his eyes close. You"
                "have slain the mighty beast, and remove your sword out of his body. The path to King "
                "Akhem's Throne is now clear. Continue your journey.";
            }
            else if(obj.get_object_flag("is_alive") == false && player_char.get_player_loc() == "spyro's lair")
            {
                return "You shouldn't mutilate the beasts body anymore. You should let him rest now.";
            }
            else if(player_char.get_player_loc() == "spyro's lair" && player_char.get_player_flag("the_confuser"))//confusion potion
            {
                obj.remove_object_flag("is_alive");
                return "While Spyro is confused, you see this as a great opportunity to attack him."
                "Spyro has fallen, and the blood is on your hands.";
            }
            else if(player_char.get_player_loc() == "spyro's lair"
             && (player_char.get_player_flag("is_strong") == false || player_char.get_player_flag("the_confuser") == false))
            { //if they try to attack spyro without using any potion
                player_char.set_player_state(false);
                return "Since you did not use any potions and attacked Spyro head on, you were abruptly"
                "eaten alive by him.";
            }
            else
            {
                return "I don't see Spyro here. What are you trying to attack? You must be losing it.";
            }
        }
        else if(obj_name == "king akhem")
        {
            if(player_char.get_player_loc() == "king's throne")
            {
                obj.set_object_flag("attacked_one", true);

                return "You pull out your sword and charge at King Akhem. He dodges the first attack."
                "However, he charges at you and attempts to strike you in the chest with his colossal hammer."
                "You then dodge out of the way at the last second, and he puts a dent in the floor"
                "instead of in you";
            }
            else if(player_char.get_player_loc() == "king's throne" && 
            obj.get_object_flag("attacked_one"))
            {
                obj.remove_object_flag("attacked_one");
                obj.set_object_flag("final_attack", true);

                return "Instead of taking him head on, you circle behind him for an attack from the rear."
                "He takes a while to spin around to defend himself, and you take this opportunity to slash him"
                "in the nape. This causes him to gush out blood.";
            }
            else if(player_char.get_player_loc() == "king's throne" && obj.get_object_flag("final_attack"))
            {
                obj.remove_object_flag("final_attack");
                obj.remove_object_flag("is_alive");
                return "King Akhem has fallen on one knee. His body has gone cold, and he is panting trying"
                "to get the blood from his nape to stop leaking out of his body. Quickly, you slice at his legs"
                "and arms, and stab him in the heart. King Akhem has fallen.\n\n The End. \n Thank you for playing"
                "the game!\n The citizens of the Farlands will rejoice now that King Akhem's rule is finished. You are declared"
                "as a hero, and live the rest of your life happy in the Farlands. \n\n Credits: \n UI Team: \nLane Durst"
                "\nConnor Morris \nObject and Development Team: \nMaureen Sanchez \nJack(Yu Joo)"
                "\nStory Development and General Coding Team: \nShawn Russell \nLogan Remondet";
            }
        }
        // add more cases here
    }
    else if (obj.get_object_type() == "item")
    {
        // add text related to attacking items here
        return "Hey, you never know if you might need that item later on. Try something else first.";
    }

    return "Invalid action & object combination; try again.";
}

// Add proper function description here
std::string read(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj_name == "paper" && (player_char.get_player_loc() == "side gate" || player_char.get_player_loc() == "palace"))
    {
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

// Add proper function description here
std::string main_action(std::string act, game_object &obj, player_info &player_char) 
{
    std::string result = "";
    std::string obj_name = obj.get_object_name();
    
    if (act == "use" || act == "unlock" || act == "drink")
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