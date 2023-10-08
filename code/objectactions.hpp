// Add necessary includes & imports here
#include "catch.hpp"
#include <iostream>

// TODO: Make the comment below more concise
/* 
  These functions should check if you have the right criteria to perform an action; for example, if you try to 
  take a item, you need to make sure that you can reach it (if there is a thing in the way) or even if you're 
  in the same location as the item or in some cases if you even have the item to use in the first place.
*/

// TODO: Define "item" and "loc" variables

/* TODO: 
    None of the methods in this file below will work because they are redefining methods that already exist within gameobjects.hpp.
    This file needs a complete rewrite.
    Everything is commented out so that the rest of the program will compile.

// functions for items
void items::take(auto parsedObject){
    // if in_location = true {take item} or if blocked by something, check for that, block the user, and then say something like "can't take that right now".
    if(getLocation(loc) == "" && parsedObject == "")
    {
        addItem(item);
        std::cout << parsedObject << " has been added to your inventory.";
    }
    else if(getLocation(loc) == "" && parsedObject == "" && findItem(item) == true) // for if you try to grab an item more than once.
    {
        std::cout << "The item that you're trying to grab again is already in your inventory."
    }
    else if(getLocation(loc) == "" && parsedObject == "")
    {
        addItem(item);
        std::cout << parsedObject << " has been added to your inventory.";
    }
    else // for if you try to grab something that doesn't exist within the game. 
    {  
        std::cout << "The action that you just attempted to perform is not valid. Please try again.";
    }
}
void items::use(auto parsedObject)
{
    // check if they have_item and if the are in_location; this is similar to the attack command.
    if(getLocation(loc) == "" && parsedObject == "" && findItem(item) == true)
    {
        removeItem(item);
        std::cout << parsedObject << " was used.";
    }
    else if(parsedObject == "")
    {
        std::cout << "You have taken out " << parsedObject << " from your inventory.";
    }
}
void items::look(auto parsedObject)
{
    if(parsedObject == "")
    {
        std::cout << "This key seems to unlock something."; // just example for key
    }
}
void items::examine(auto parsedObject)
{
    // unimplemented
}
void items::open(auto parsedObject)
{
    if(parsedObject == "")
    {
        removeItem(item); // for example, if the user opens a container from within their inventory, then remove the container from their inventory 
        item::take(item); // and then add the items from within the container to the user's inventory instead
        std::cout << "You obain" << item << " heal potion! It may be useful"; // example text for a heal potion
    }
    else 
    {
        std::cout << "It cannot open.";
    }
}
void items::read(auto parsedObject)
{
    if(getLocation(loc) == "" && parsedObject == "") // if user reads something in a specific place, creates an event
    {
        std::cout << "Lord... I can see you..."; // example text of a magical event upon reading a magic book
    }
    else if(parsedObject == "")
    {
        std::cout << "Can't read this book since it is damaged."; // need to change text to more generic fail state
    }
    else 
    {
        std::cout << "It's unreadable.";
    }
}
void items::throwItem(auto parsedObject){
    if(getLocation(loc) == "" && parsedObject == "")
    {
        removeItem(item); // if a weapon is thrown, remove the item from the player's inventory
    }
    else 
    {
        std::cout << "This is not a throwing thing.";
    }
}
void items::unlock(auto parsedObject){
    if(getLocation(loc) == "" && parsedObject == "")
    {
        removeItem(item); // user goes next chapter by unlocking some sort of door, then key should disappear from inventory
        std::cout << "You open the door!";
    }
    else
    {
        std::cout << "You don't have anything to unlock " << parsedObject << ".";
    }
}
void items::put(auto parsedObject)
{
    // unimplemented
}

// functions for locations
// TODO: replace example description text with a direct call to a gameObject's get_description() function
void locations::go_to(auto parsedObject)
{
    if(getLocation(loc) == "" && parsedObject == "")
    {
       setLocation(loc);
       std::cout << "You are now going to: " << parsedObject;
    }
    else if(findItem(item) == false && getLocation(loc) == "" && findItem(loc) == false) // for when the player doesn't have the right items
    {
        std::cout << "You are missing multiple items. Look around the area before moving on to the next location."
    }
}
void locations::look(auto parsedObject)
{
    if(getLocation(loc) == "" && parsedObject == "")
    {
       std::cout << "It has a shady atmosphere"; // example text
    }
    else
    {
        std::cout << "You cannot see. It's too dark"; // example text
    }
}
void locations::leave(auto parsedObject)
{
    if((getLocation(loc) == "" && parsedObject == "") != setLocation(loc))
    {
       std::cout << "You are leaving from: " << setLocation(loc);
       setLocation(loc);
    }
    else
    {
        std::cout << "This place is " << parsedObject << " that you want to go"; // example text
    }
}
void locations::examine(auto parsedObject)
{
    if(getLocation(loc) == "" && parsedObject == "")
    {
       std::cout << "There are letters on the wall... It says... God is dead..."; // example text
    }
    else
    {
        std::cout << "Try again!";
    }
}

// functions for characters
void characters::look(auto parsedObject)
{
    // unimplemented
}
void characters::examine(auto parsedObject)
{
    // unimplemented
}
void characters::attack(auto parsedObject)
{
    // unimplemented
}
void characters::talk_to(auto parsedObject)
{
    // unimplemented
}

*/

// TODO: Delete the following code once the parser is finished; this just does the job of the parser
/*
void examineInput(auto parsedAction, auto parsedObject)
{
    std::string(tolower(parsedAction));
    if(parsedObject == item)
    {
        if(parsedAction == "use")
        {
            void items::use(parsedObject);
        }
        else if(parsedAction == "take")
        {
            void items::take(parsedObject);
        }
        else if(parsedAction == "look")
        {
            void items::look(parsedObject);
        }
        else if(parsedAction == "examine")
        {
            void items::examine(parsedObject);
        }
        else if(parsedAction == "open")
        {
            void items::open(parsedObject);
        }
        else if(parsedAction == "read")
        {
            void items::read(parsedObject);
        }
        else if(parsedAction == "throwItem")
        {
            void items::throwItem(parsedObject);
        }
        else if(parsedAction == "unlock") // probably only going to be used for chests, doors, etc.
        {
            void items::unlock(parsedObject);
        }
        else if(parsedAction == "put")
        {
            void items::put(parsedObject);
        }
        else
        {
            std::cout << parsedAction << " is not a valid input.";
        }
    }
    else if(parsedObject == locations)
    {
        if(parsedAction == "go to")
        {
            void locations::go_to(parsedObject);
        }
        else if(parsedAction == "look")
        {
            void locations::look(parsedObject);
        }
        else if(parsedAction == "leave")
        {
            void locations::leave(parsedObject);
        }
        else if(parsedAction == "examine")
        {
            void locations::examine(parsedObject);
        }
        else
        {
            std::cout << parsedAction << " is not a valid input.";
        }
    }
    else if(parsedObject == characters)
    {
        if(parsedAction == "look")
        {
            void characters::look(parsedObject);
        }
        else if(parsedAction == "examine")
        {
            void characters::examine(parsedObject);
        }
        else if(parsedAction == "attack")
        {
            void characters::attack(parsedObject);
        }
        else if(parsedAction == "talk to")
        {
            void characters::talk_to(parsedObject);
        }
        else
        {
            std::cout << parsedAction << " is not a valid input.";
        }
    }
    else
    {
        std::cout << parsedObject << " was not recognized. Please try again.";
    }
}
*/
