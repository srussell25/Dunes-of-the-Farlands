#ifndef OBJECTACTIONS_HPP
#define OBJECTACTIONS_HPP

#include "classesmisc.hpp"

// Add proper function description here
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

    return "Invalid action & object combination; try again.";
}

// Add proper function description here
std::string take(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj.get_object_loc() == "playerinventory")
    {
        return "Are you seriously trying to take an item from your own inventory?";
    }
    
    if (obj_name == "chest key")
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
    else if (obj_name == "book")
    {
        if (player_char.get_player_loc() == "potion room")
        {
            return "Can't you read the sign? It says don't read the book, ya bozo.";
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
        if (player_char.get_player_loc() == "the king's throne")
        {
            player_char.set_player_state(false);
            return "You attempt to grab King Akhem by the arm. He flings you off like a piece of "
            "spaghetti, and you're immediately swarmed by all the guards. Did you really think "
            "that was going to work?";
        }
    }
    else if (obj_name == "paper")
    {
        if (player_char.get_player_loc() == "outside palace")
        {
            player_char.add_inv_item(obj);
            return "The paper was added to your inventory. It seems to have some important script, "
            "maybe you should try reading it?";
        }
    }

    return "This action cannot be performed here. Try something else.";
}

// Add proper function description here
std::string go_to(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj_name == "oasis")
    {   
        if (player_char.get_player_loc() == "game start")
        {
            player_char.set_player_loc(obj);
            player_char.set_player_state(false);
            return "You make your way over to the oasis, but when you get there, "
            "a frog suddenly jumps onto your leg. It's a poisonous frog. You die in seconds.";
        }
        else
        {
            return "That desert oasis is no longer near you.";
        }
    }
    else if (obj_name == "abandoned town")
    {
        if (player_char.get_player_loc() == "game start" )
        { 
            obj.set_object_flag("been_to", true); // Used to check if the player has already accessed this area
            player_char.set_player_loc(obj);
            return "You arrive at the town named Nekhem. The town isn't necessarily abandoned, "
            "but it's overrun by thugs and bandits. The walls are broken, and people have "
            "malicious looks on their faces. You see a tavern called the Sand Dune Saloon nearby, "
            "but your gaze also happens upon an old lady who seems to be struggling.";
        }
        else if (player_char.get_player_loc() == "tavern" && obj.get_object_flag("been_to") == true)
        {
            return "You have returned to the streets of the abandoned town.";
        }
        else
        {
            return "This action cannot be performed here. You cannot go back to the abandoned town"; 
        }
    }
    else if (obj_name == "tavern")
    {
        if (player_char.get_player_loc() == "abandoned town")
        {
            player_char.set_player_loc(obj);
            return "You enter into the tavern. You try to go up to the bar to ask for directions, "
            "but the bar is heavily crowded, and you end up accidentally stepping on a stranger's foot. "
            "He stands up, along with his pals, and draws his sword; you've come across a bandit and his crew!";
        }
        else
        {
			return "You try to go to a tavern for a nice drink; unfortunately, there are none around.";
        }
    }
    else if ( obj_name == "farlands")
    {
        if (player_char.get_player_loc() == "tavern")
        {
           player_char.set_player_loc(obj);
           return "When arriving at the outer gates of the Farlands, you see that this place is surrounded by a "
           "huge sandstone wall that seems to surround the entire city. Spews of fire are emitted from a large stone "
           "statue of what appears to be the city's god, Atum the Almighty. Your only way into the city is through the "
           "doors that are guarded by 2 large guards who do not look so friendly.";
        }
        else 
        {
            return "you cannot get to this location you do not know where it is.";
        }
    }
    else if (obj_name == "gate")
    {
        if (player_char.get_player_loc() == "farlands")
        {
            return "You go to the gate and make eye contact with the guards.";
        }
        else 
		{
			return "you cannot go to said gate from where you are";
		}
    }
    else if (obj_name == "guards")
    {
        if (player_char.get_player_loc() == "farlands" || player_char.get_player_loc() == "gate")
        {
            return "You are already at the guards, try something else";
        }
        else 
		{
			return "what guards are you talking";
		}
    }
    else if (obj_name == "coffee shop")
    {
        if (player_char.get_player_loc() == "city square")
		{
			player_char.set_player_loc(obj);
			return "You enter the coffee shop by walking through the front door.";
		}
		else
		{
			return "This action cannot be performed in the coffee shop. Try talking to some of the locals.";
		}
	}
    else if (obj_name == "general store")
    {
        if (player_char.get_player_loc() == "city square")
        {
            player_char.set_player_loc(obj);
            return "You enter the store.";
        }
        else
        {
            return "This action cannot be performed at the general store. Try talking to the shopkeep."; 
        }
    }
    else if (obj_name == "sarabi's egyptian cuisine")
    {
        if (player_char.get_player_loc() == "city square")
        {
            player_char.set_player_loc(obj);
            return "You enter the restaurant. Smells good in here.";
        }
        else
        {
            return "This action cannot be performed at Sarabi's Egyptian Cuisine. Try talking to the locals.";
        }
    }
    else if (obj_name == "palace")
    {
        if (player_char.get_player_loc() == "city square")
        {
            player_char.set_player_loc(obj); // NOTE: Is this right?
            return "You arrive to the walls outside the Kingdom. This place seems heavily "
            "guarded... better be on alert. Should probably examine the area around before trying to go inside the palace.";
        }
        else
        {
            return "unique fail text"; // Add unique fail text
        }
    }
    else if (obj_name == "potion room")
    {
        if ((player_char.get_player_loc() == "palace" || player_char.get_player_loc() == "gate")
            && player_char.get_player_flag("knocked_guard_out"))
        {
           player_char.set_player_loc(obj);
           return "you enter the palace and head to the potion room. As you may expect there are alot of potions in this room."
            "maybe you can look around?";
        }
    }
    else if(obj_name == "spyro's lair")
    {
        if((player_char.get_player_loc() == "palace" || player_char.get_player_loc() == "gate") 
            && player_char.get_player_flag("knocked_guard_out"))
        {
            player_char.set_player_loc(obj);
            player_char.set_player_state(false);
            return "you enter the palace and enter Spyro's Lair. You see Spyro, the most powerful Sphynx in the land takes his"
            "claws and rips your flesh to shreds. Maybe you should try following the paper's instruction said next time.";
        }
        /* TODO: Finish Part 2 of Spyro's Lair
        else if(player_char.get_player_loc() == "potion room" && (player_char.get_inv_item("fire potion") == ))
        {
            return "";
        }
        */
    }

    return "Invalid action & object combination; try again.";
}

std::string go_to(game_object &obj, std::string direction, player_info &player_char) 
{
    int i, j;
    i, j = obj.get_entire_location_small_pos(player_char.get_player_loc());
    if (direction == "south") 
    {
        
    }
    else if (direction == "north") 
    {

    }
    else if (direction == "west") 
    {
        
    }
    else if (direction == "east") 
    {
        
    }
    return;
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
        else if (player_char.get_player_loc() != "general store")
        {
            return "You're not at a store; where do you expect to see a shopkeeper?";
        }
    }
    else if (obj_name == "guards")
    {
        if (player_char.get_player_loc() == "farlands" || player_char.get_player_loc() == "gate") 
        {
            // Set guards description and location for the palace later on
            obj.set_object_desc("The guards have large swords that could kill an unprepared civilian "
            "with only one swing. There are a lot of guards, but you do see one guard alone next "
            "to a side gate. A perfect time to strike...");
            obj.set_object_loc("palace");

            // Continue with player actions
            player_char.set_player_loc(find_object("city square"));
            return "You politely ask if you can get into the city. The guards ask you what your "
            "business is here. You say that you are just passing by. One of them responds with 'If you "
            "cause any trouble here, we will find you. You've been warned'. These guys have such great "
            "manners, don't they? Well, either way, congratulations! You've managed to reach the City "
            "Square of the Farlands.";
        }
        else if (player_char.get_player_loc() == "palace")
        {
            player_char.set_player_state(false);
            return "You attempt to talk to the big group of guards who are guarding the palace and, without warning, "
            "you find yourself surrounded. These guards are really effective at keeping intruders out, huh?";
        }
        else 
        {
            return "There aren't any guards at your current location. Maybe you'll see some later?";
        }
    }
    else if (obj_name == "guard")
    {
        if (player_char.get_player_loc() == "palace" || player_char.get_player_loc() == "side gate")
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
        if (player_char.get_player_loc() == "the king's throne")
        {
            player_char.set_player_state(false);
            return "You try and talk to King Akhem to distract him. Unfortunately, he does "
            "not pay attention to your silly games, and strikes you in the face with " 
            "Smough's Hammer. You die instantly.";
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
    if (player_char.get_player_loc() == obj.get_object_loc() || player_char.get_player_loc() == obj_name)
    {
        return obj.get_object_desc();
    }
    else if (player_char.get_player_loc() == "coffee shop" && obj_name == "locals")
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
        obj.set_object_flag("is_evil", true);
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
            else if(obj_name == "old lady" && obj.get_object_flag("is_evil")) 
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
    
    if (act == "use" || act == "unlock")
    { 
        result = use(obj, obj_name, player_char);
    }
    else if (act == "take" || act == "get" || act == "grab")
    {
        result = take(obj, obj_name, player_char);
    }
    else if (act == "go")
    {
        result = go_to(obj, obj_name, player_char);
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