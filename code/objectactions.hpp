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
    else if(currObjName == "book"){
        if(playerChar.get_player_loc() == "Potion Room")
        {
            return "You cant read? It says not to take the book silly. Try something else";
        }
        else
        {
            return "You cannot perform this action here. Try something else"; //unique fail test
        }
    }
    else if(currObjName == "Spyro"){
        if(playerChar.get_player_loc() == "Spyro's Lair")
    {
        playerChar.set_player_state(false);
        return "You try and grab Spyro by the leg, to which he takes his leg and repeatedly stomps you until you "
        "are one with the stone under his feet";
    }
    else
    {
        return "This action cannot be performed here. Try something else."; //unique fail test
    }
}
    else if(currObjName == "King Akhem"){
        if(playerChar.get_player_loc() == "The King's Throne")
        {
            playerChar.set_player_state(false);
            return "You lunge at King Akhem to grab him by the arm. He flings you off like a piece of "
            "spaghetti. This knocks you out cold, and he throws you out of the palace.";
        }
        else
        {
            return "This action cannot be performed here. Try something else."; //unique fail test
        }
    }
    else if(currObjName == "Paper"){
        if(playerChar.get_player_loc() == "outside palace")
        {
            return "You grab the paper. Seems to have some important script on it.";
        }
        else
        {
            return "This action cannot be performed here. Try something else."; //unique fail test
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
            return "That desert oasis is no longer near you."; // add unique fail text
        }
    }
    else if (obj_name == "abandoned town")
    {
        if (player_char.get_player_loc() == "game start" )
        { // we add a flag to the location "abandoned town" and we have a seperate else to check for if we have been here already
            obj.set_object_flag("been_to", true);
            player_char.set_player_loc(obj);
            return "You arrive at the town named Nekhem. The town isn't necessarily abandoned,"
            " but it's overrun by thugs and bandits. The walls are broken, and people have"
            " malicious looks on their faces. You see a tavern called the Sand Dune Saloon nearby,"
            " but your gaze also happens upon an old lady who seems to be struggling.";
        }
        else if (player_char.get_player_loc() == "tavern" && obj.get_object_flag("been_to") == true )
        {
            return "you are now in the abandoned town";
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
            return "You enter into the tavern. You try to go up to the bar to ask for directions,"
            " but the bar is heavily crowded, and you end up accidentally stepping on a stranger's foot."
            " He stands up, along with his pals, and draws his sword; you've come across a bandit and his crew!";
        }
        else
        {
			return "you try to go to a tavern for a nice drink, but there is no taverns that are near you."; // add unique fail text
        }
    }
    else if ( obj_name == "farlands")
    {
        if (player_char.get_player_loc() == "tavern"  )
        {
           player_char.set_player_loc(obj);
           return "When arriving at the outer gates of the Farlands, you see that this place is surrounded by a "
           "huge sandstone wall that seems to surround the entire city. Spews of fire are emitted from a large stone "
           "statue of what appears to be the city’s god, Atum the Almighty. Your only way into the city is through the "
           "doors that are guarded by 2 large guards who do not look so friendly. ";
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
    else if(currObjName == "coffee shop")
    {
        if(playerChar.get_player_loc() == "city square")
		{
			playerChar.set_player_loc(obj);
			return "You enter the coffee shop by walking through the front door.";
		}
		else
		{
			return "This action cannot be performed in the coffee shop. Try talking to some of the locals.";
		}
	}
    else if(currObjName == "general store")
    {
        if(playerChar.get_player_loc() == "city square")
        {
            playerChar.set_player_loc(obj);
            return "You enter the store.";
        }
        else
        {
            return "This action cannot be performed at the general store. Try talking to the shopkeep."; 
        }
    }
    else if(currObjName == "Sarabi's Egyptian Cuisine")
    {
        if(playerChar.get_player_loc() == "city square")
        {
            playerChar.set_player_loc(obj);
            return "You enter the restaurant. Smells good in here.";
        }
        else
        {
            return "This action cannot be performed at Sarabi's Egyptian Cuisine. Try talking to the locals.";
        }
    }
    // else if(currObjName == "Palace" && playerChar.get_player_loc() == "city square") //going to need to update this version to get this one done.
    // {
        
    //     {
    //         return "You arrive to the walls outside the Kingdom. This place seems heavily"
    //         "guarded… better be on alert. Should probably examine the area before going in.";
    //     }
    //     else
    //     {

    //     }
    // }
}

// Add function description here
std::string talk_to(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj_name == "barkeep")
    {
        if (player_char.get_player_loc() == "tavern")
        {
            obj.set_object_flag("talked_to", true);
            return "Welcome to the Sand Dune Saloon. I'm the barkeep. Here's a drink, it's on the house; I can tell you're good people."
            " I must warn you though: there is nothing worth staying for at this town, that is, unless you want to get yourself killed by"
            " one of the locals. If I were you, I'd recommend heading east of here, to the Farlands. It's quite the dangerous area in its"
            " own right, but you'll find more to do over in that region.";
        }
        else if (playerChar.get_player_loc() != "tavern")
        {
            return "The barkeep is in the tavern, not in this area"; // add unique fail text
        }
    }
    else if (obj_name == "old lady")
    {
        if (player_char.get_player_loc() == "abandoned town")
        {
            player_char.set_player_state(false);
            return "You try to talk to the old lady, but as you walk over, she suddenly turns around and stabs you."
            " She takes all of your items, and then runs off. Looks like she didn't need any help after all... \n "
            "Game Over, Try Again.";
        }
        else
        {
            return "The old lady is not in this area."; 
        }
    }
    else if(currObjName == "locals")
    {
		if(playerChar.get_player_loc() == "Sarabi's Egyptian Cuisine" )
        {
            return "You pass a woman eating. She mentions that she cannot stand King Akhem. "
            "She says she does not care if she gets arrested for saying so. ‘People like him are less "
            "than the dirt under my feet when I step foot outside’ she says.";
        }
        else if(playerChar.get_player_loc() == "coffee shop")
		{
            return "You come across a man who is having a coffee. You ask if you can sit down,"
            "and he accepts. He orders you a coffee as well. You guys make small talk about where you" 
            "are both from and what to do in the Farlands. He lets you know that you should not go near the "
            "Palace unless you want to get in trouble. He says that King Akhem will kill anyone who gets in "
            "his way and will obtain power by any means possible. You thank him for his time and get up from "
            "the table with your coffee.";
        }
        else
        {
            return "There are no locals in the area that you are in. Try something else. "; 
            //this is if they try talking to anyone else other than the locals
        }
    }
    else if(currObjName == "shopkeeper"){
        if(playerChar.get_player_loc() == "general store")
        {
            return "You approach the shopkeeper and say hello. She gives a shy hello back and asks what she "
            "could do for her. You begin to ask about the town and what it has to offer. She replies saying "
            "that she doesn't like this town because of King Akhem, and that she wishes that someone would put "
            "a stop to him. She takes notice that you are somewhat of a warrior and sees that you lack any type of "
            "armor. She pulls out the Armor of Torren, and says, ‘You must take this and find a way to defeat King "
            "Akhem, you are the chosen one. Please… you are our only hope. Here, please take this gift' You "
            "are offered to take the armor.";
            
        }
        else if(playerChar.get_player_loc() != "general store")
        {
            return "Shopkeep is at the general store, not here silly.";
        }
    }
    else if (obj_name == "guards")
    {
        if (player_char.get_player_loc() == "farlands" ||player_char.get_player_loc() == "gate") 
        {
            obj.set_object_desc("The guards have large swords that could kill an unprepared civilian with only one swing. "
            "There are a lot of guards, but one is by himself at side gate.");
            obj.set_object_loc("palace");

            player_char.set_player_loc(obj);//need this to be change or talk to connor about this
            return "You politely ask if you can get into the city. The guards ask you what your "
            "business is here. You say that you are just passing by. A guard says, ‘if you cause "
            "trouble here, we will find you’. These guys have such manners, don’t they? \n \n "
            "Congratulations, you have entered the City Square of the Farlands. Maybe you should look around.";
        }
        else if (player_char.get_player_loc() == "palace")
        {
            player_char.set_player_state(false);
            return "you attempt to talk to the big group of guards who are guarding the palace and with out warning "
            "they surround you and and kill you. seems like these guards are really effective at keeping intruders out \n Game Over";
        }
        else 
        {
            "there are no guards at your current location, maybe you will find some later.";
        }
    }
    else if (obj_name == "guard")
    {
        if (player_char.get_player_loc() == "palace")
        {
            return "The guard tells you, ‘State your business civilian, or I will have to resort in arresting "
            "you for failing to obey the laws of King Akhem’. He examines you while saying this, "
            "and spits at your feet.";
        }
        else 
        {
            return "there is not a guard at your current location, maybe you will find some at a later point";
        }
    }
    else if(currObjName == "Spyro")
    {
        if(playerChar.get_player_loc() == "Spyro's Lair")
        {
            playerChar.set_player_state(false);
            return "You try to talk to Spyro to distract him. You say, ‘What’s that over there?’ and point to"
            "a wall. He does not fall for that trick, and flies toward you to bite your head off.\n Game Over,"
            "Try Again.";
        }
        else
        {
            return "You are not in Spyro's Lair yet. I understand you are trying to skip apart of the game to"
            "get to some of the good stuff, but I will not allow it.";
        }
    }
    else if(currObjName == "King Akhem")
    {
        if(playerChar.get_player_loc() == "The King's Throne")
        {
            playerChar.set_player_state(false);
            return "You try and talk to King Akhem to distract him. Unfortunately, he does not pay "
            "attention to your silly games, and strikes you in the face with Smough’s Hammer. This kills"
            "you instantly. \n Game Over, Try Again.";
        }
        else
        {
            return "You are not in the King's Throne room yet. Look at you trying to sneak in without "
            "doing the other side missions first. For shame.";
        }
    }
	
    return "Invalid action & object combination; try again."; // Fallback return
}

// If there is an object to look at, call this function for the description.
std::string look_at(game_object &obj, std::string obj_name, player_info &player_char)
{
    //if (player_char.get_player_loc() == obj_name)
    if (player_char.get_player_loc() == obj.get_object_loc() || player_char.get_player_loc() == obj_name)
    {
        return obj.get_object_desc();
    }
    else if(playerChar.get_player_loc() == "coffee shop"  && currObjName == "locals")
    {
        obj.set_object_desc("These locals seem like they have had a long day. People have dirt all on their"
    "clothes and in their hair, many are sleeping at the tables they're sitting at. However, the people seem"
    "to have smiles on their faces.");
        obj.set_object_loc("coffee shop");
        return obj.get_object_desc();
    }
    else if(playerChar.get_player_loc() == "Sarabi's Egyptian Cuisine" && currObjName == "locals")
    {
        obj.set_object_desc("These locals seem to be wealthier than those at the coffee shop. They look at "
        "you and scoff as if you are not worthy enough to be in the restaurant itself. Who do they think they"
        "are?!");
        obj.set_object_loc("Sarabi's Egyptian Cuisine");
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
        else if (player_char.get_player_loc() == "farlands" || player_char.get_player_loc() == "gate")
        {
            if (obj_name == "guards")
            {
               player_char.set_player_state(false);
                return "Attacking two guards at one time? Bold move… \n"
                "The guards are much stronger than someone with one sword and mediocre skills. "
                "The guards beat you to death as soon as you try and unsheathe your sword. \n Game Over";
            }
            else 
            {
                return "whatever you are trying to attack its not here. look somewhere else.";
            }
        }
        else if (player_char.get_player_loc() == "palace" )
        {
             if (obj_name == "guards")
             {
                player_char.set_player_state(false);
                return "You attempt to attack the guards head on. However, they stab you multiple "
                "times, killing you. Did you really think that you were strong enough to take on "
                "multiple Palace Soldiers? Feeble minded…\n Game Over";
             }
             if (obj_name == "guard") 
             {
                obj.set_object_flag("is_uncondcius",true);
                return "The guard sees that his toga is becoming loose and drops his sword to tighten it. "
                "you use this opertunity to hit the guard upside the head with the end of your sword knocking him unconscious "
                "You see that a paper falls out of a part of his toga";
             }
        }
        else if (obj_name == "shopkeeper")
        {
        if (player_char.get_player_loc() == "general store" )
            {
                player_char.set_player_state(false);
                return "Your sword is strong. However, the shopkeeper takes one of the wooden toys and "
                "hits you in the temple of your head, causing you to hit your head on a table and die. \n Game Over";
            }
            else 
            {
                return "there is not a shopkeeper at your current location, maybe you will find one at a store. ";
            }
        }
		
        // add more cases here
    }
    else if (obj.get_object_type() == "item")
    {
        // add text related to attacking items here.
		
        return "you cannot attack this item you may need it later silly. try a different approch.";
    }

    return "Invalid action & object combination; try again."; // Fallback return
}

// Read things like books, notes, etc.
std::string read(game_object &obj, std::string obj_name, player_info &player_char)
{
    if (obj.get_object_type() == "item" && playerChar.get_player_loc() == obj.get_object_loc() && obj.get_object_name() != "book")
    {
        return obj.get_object_desc();
    }
    else if(obj.get_object_type() == "item" && playerChar.get_player_loc() == obj.get_object_loc() && obj.get_object_name() == "book")
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