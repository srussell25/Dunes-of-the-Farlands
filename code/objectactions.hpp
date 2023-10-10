#ifndef OBJECTACTIONS_HPP
#define OBJECTACTIONS_HPP

#include "playercharacter.hpp"

std::string use(game_object obj, player_info &playerChar)
{
    if (obj.get_object_name() == "chestKey")
    {
        return "You used the chestKey.";
    }
    else if (obj.get_object_name() == "drink"){
        if (obj.get_object_flag("at_object") == "at_object")
        {
            playerChar.remove_item(obj);
            return "man that drink was pretty good.";
        }
        else
        {
            return "man that drink sucked you really should of drank it in the tavern";
        }
    }
    
    return "";
}

std::string take(game_object obj, player_info &playerChar)
{
    if (obj.get_object_name() == "chestKey")
    {
        playerChar.add_item(obj);
        return "chestKey added to inventory.";
    }
    else if(obj.get_object_name() == "drink")  {
        if (obj.get_object_flag("at_object") == "at_object")
        {
            playerChar.add_item(obj);
            return "drink was added to inventory.";
        }
        else 
        {
            return "what drink?";
        }

    }
    return "";
}
std::string go_to(game_object obj, player_info &playerChar)
{
    if (obj.get_object_name() == "oasis")
    {
       if (playerChar.get_location().get_object_name() == "gameStart")
       {
        playerChar.set_location(obj) = oasis; 
        return "you got to the oasis. when you make it there a frog jumps onto your legs and poisons you,"
         "you die in seconds.";
         playerChar.set_player_state(false);
       }
    }
    else if (obj.get_object_name() == "abandonedTown"){
        if (playerChar.get_location().get_object_name() == "gameStart")
       {
        playerChar.set_location(obj) = abandonedTown; 
        oldLady.add_object_flag("nearCharacter");
        abandonedTown.add_object_flag("at_town");
        gameStart.remove_object_flag("at_start");
        return "You arrive at the town named Nekhem. The town isnt necessarily abandoned, but its overrun by thugs and bandits."
         "The walls are broken, and people have malicious looks on their faces. there is a tavern called the Sand Dune Saloon. there is also a old lady who seems to be struggling. what do you do?";
         
       }
    }

    else if (obj.get_object_name() == "tavern")
    {
        if (playerChar.get_location().get_object_name() == "abandonedTown"){

        
        barKeep.add_object_flag("nearCharacter");
        bandit.add_object_flag("nearCharacter");
        tavern.add_object_flag("at_tavern");
        drink.add_object_flag("at_object");
        abandonedTown.remove_object_flag("at_town");
        oldLady.remove_object_flag("nearCharacter");
        
    return "you entered into the tavern. it is full with towns people. you go up to the bar to ask for directions."
    "unfortunalty as your walking up to the counter you step on you you accidentally step on someones foot "
    "they stand up and draw there swords. what do you do?";
        }
    return "";
}
}

std::string talk_to(game_object obj, player_info &playerChar){
        if(obj.get_object_flag("bartender") == "bartender" ||obj.get_object_flag("barkeep") == "barkeep" ){
            if (obj.get_object_flag("nearCharacter") == "nearCharacter"){
            return "hey im the bartender of the Sand Dune Saloon."
         }
        }
}


//if there is an object to look at, call this function for the description
std::string look(game_object obj, player_info &playerChar){
        if(obj.get_object_flag("at object") == "at object"){
        return obj.get_object_description();
        }
}

//should give a more in depth description of an object. 
std::string examine(game_object obj, player_info &playerChar){
         if(obj.get_object_flag("at object") == "at object"){
        return obj.get_object_description();
    }
}

//attack the character, then check for the specified character
std::string attack(game_object obj, player_info &playerChar){
    if(obj.get_object_type() == "character" && obj.get_object_flag("nearCharacter") == "nearCharacter"){
        if(obj.get_object_name() == "bandit"){
            bandit.remove_object_flag("is_alive");
            return "You have slay the bandit with your sword. no one in that Sand Dune Saloon bats a eye. the bartender bekends you over to talk.";
        }
        else if(obj.get_object_name() == "oldLady"){
            return "Interesting... ";
        }
        else if(obj.get_object_name() == "barKeep"){
            return "He's a bar keep, have some self discipline";
        }
    }
    return "";
}

//read things like books, notes, etc.
std::string read(game_object obj, player_info &playerChar){
    if(obj.get_object_type() == "item"){
        if(obj.get_object_name() == "note" && obj.get_object_flag("at tavern") == "at tavern"){
                return obj.get_object_description();
        }
    }
}

//basically same thing as take, just works just in case the player puts get instead of take
std::string get(game_object obj, player_info &playerChar){
     if (obj.get_object_name() == "chestKey")
    {
        playerChar.add_item(obj);
        return "chestKey added to inventory.";
    }
    else if(obj.get_object_name() == "drink")  {
        if (obj.get_object_flag("at tavern") == "at tavern")
        {
            playerChar.add_item(obj);
            return "drink was added to inventory.";
        }
        else 
        {
            return "what drink?";
        }

    }
    return "";
}

//same concept as functions take and get.
std::string grab(game_object obj, player_info &playerChar){
     if (obj.get_object_name() == "chestKey")
    {
        playerChar.add_item(obj);
        return "chestKey added to inventory.";
    }
    else if(obj.get_object_name() == "drink")  {
        if (obj.get_object_flag("at tavern") == "at tavern")
        {
            playerChar.add_item(obj);
            return "drink was added to inventory.";
        }
        else 
        {
            return "what drink?";
        }

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
    else if (act == "get")
    {
        result = get(obj, playerChar);
    }
    else if (act == "talk to")
    {
        result = talk_to(obj, playerChar);
    }
    else if (act == "grab")
    {
        result = grab(obj, playerChar);
    }
    return result;
}

#endif