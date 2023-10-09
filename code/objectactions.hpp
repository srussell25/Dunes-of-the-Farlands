#ifndef OBJECTACTIONS_HPP
#define OBJECTACTIONS_HPP
#endif

// This function will take in an action as a string and the current 
// game object being called upon; it will then check the name of the 
// action via a set of if statements doing string comparisons, and once 
// it finds a match, it will send the game object through to a 
// dedicated function for the action being called upon.
std::string main_action(std::string act, game_object obj) 
{
    std::string result;
    if (act == "use")
    { 
            result= use(obj);
    }
    else (act == "take")
    {
        result = take(obj);
    }
    // code goes here

    return result;
}



std::string use(game_object obj)
{
    if (obj.get_object_name() == "key")
    {
        return "you used the key";
    }
    
    
}
std::string take(game_object obj)
{
    if (obj.get_object_name() == "key")
    {
        player.add_item(obj);
        return "you added the key to your inventory";
    }
}