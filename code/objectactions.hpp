// Add necessary includes & imports here
#include <iostream>
#include "catch.hpp"

//  Including files from other parts of the project
#include "main.cpp"
#include "gameobjects.hpp"

/* 
  These functions should check if you have the right criteria to perform an action; for example, if you try to 
  take a item, you need to make sure that you can reach it (if there is a thing in the way) or even if you're 
  in the same location as the item or in some cases if you even have the item to use in the first place.
*/

// functions for items
void items::take(T parsedObject){
    // if in_location = true {take item} or if blocked by something, check for that, block the user, and then say something like "can't take that right now".
    if(T getLocation(T loc) == "" && T parsedObject == "")
    {
        addItem(T item);
        std::cout << parsedObject << " has been added to your inventory.";
    }
    else if(T getLocation(T loc) == "" && T parsedObject == "" && T findItem(T item) == true) // for if you try to grab an item more than once.
    {
        std::cout << "The item that you're trying to grab again is already in your inventory."
    }
    else if(T getLocation(T loc) == "" && T parsedObject == "")
    {
        addItem(T item);
        std::cout << parsedObject << " has been added to your inventory.";
    }
    else // for if you try to grab something that doesn't exist within the game. 
    {  
        std::cout << "The action that you just attempted to perform is not valid. Please try again.";
    }
}
void items::use(T parsedObject)
{
    // check if they have_item and if the are in_location; this is similar to the attack command.
    if(T getLocation(T loc) == "" && T parsedObject == "" && T findItem(T item) == true)
    {
        removeItem(T item);
        std::cout << parsedObject << " was used.";
    }
    else if(T parsedObject == "")
    {
        std::cout << "You have taken out " << parsedObject << " from your inventory.";
    }
}
void items::look(T parsedObject)
{
    if(T parsedObject == "")
    {
        std::cout << "This key seems to unlock something."; // just example for key
    }
}
void items::examine(T parsedObject)
{
    // unimplemented
}
void items::open(T parsedObject)
{
    if(T parsedObject == "")
    {
        removeItem(T item); // for example, if the user opens a container from within their inventory, then remove the container from their inventory 
        item::take(T item); // and then add the items from within the container to the user's inventory instead
        std::cout << "You obain" << item << " heal potion! It may be useful"; // example text for a heal potion
    }
    else 
    {
        std::cout << "It cannot open.";
    }
}
void items::read(T parsedObject)
{
    if(T getLocation(T loc) == "" && T parsedObject == "") // if user reads something in a specific place, creates an event
    {
        std::cout << "Lord... I can see you..."; // example text of a magical event upon reading a magic book
    }
    else if(T parsedObject == "")
    {
        std::cout << "Can't read this book since it is damaged."; // need to change text to more generic fail state
    }
    else 
    {
        std::cout << "It's unreadable.";
    }
}
void items::throw(T parsedObject){
    if(T getLocation(T loc) == "" && T parsedObject == "")
    {
        removeItem(T item); // if a weapon is thrown, remove the item from the player's inventory
    }
    else 
    {
        std::cout << "This is not a throwing thing.";
    }
}
void items::unlock(T parsedObject){
    if(T getLocation(T loc) == "" && T parsedObject == "")
    {
        removeItem(T item); // user goes next chapter by unlocking some sort of door, then key should disappear from inventory
        std::cout << "You open the door!";
    }
    else
    {
        std::cout << "You don't have anything to unlock " << parsedObject << ".";
    }
}
void items::put(T parsedObject)
{
    // unimplemented
}

// functions for locations
// note: implement descLocation function to give a description of each location. 
void locations::go_to(T parsedObject){
    if(T getLocation(T loc) == "" && T parsedObject == "")
    {
       setLocation(T loc);
       std::cout << "You are now going to: " << parsedObject;
    }
    else if(T findItem(T item) == false && T getLocation(T loc) == "" && T findItem(T loc) == false) // for when the player doesn't have the right items
    {
        std::cout << "You are missing multiple items. Look around the area before moving on to the next location."
    }
}
void locations::look(T parsedObject){
    if(T getLocation(T loc) == "" && T parsedObject == "")
    {
       std::cout << "It has a shady atmosphere"; // example text
    }
    else
    {
        std::cout << "You cannot see. It's too dark"; // example text
    }
}
void locations::leave(T parsedObject){
    if((T getLocation(T loc) == "" && T parsedObject == "") != setLocation(T loc))
    {
       std::cout << "You are leaving from: " << setLocation(T loc);
       setLocation(T loc);
    }
    else
    {
        std::cout << "This place is " << parsedObject << " that you want to go"; // example text
    }
}
void locations::examine(T parsedObject)
{
    if(T getLocation(T loc) == "" && T parsedObject == "")
    {
       std::cout << "There are letters on the wall... It says... God is dead..."; // example text
    }
    else
    {
        std::cout << "Try again!";
    }
}

// functions for characters
void characters::look(T parsedObject)
{
    // unimplemented
}
void characters::examine(T parsedObject)
{
    // unimplemented
}
void characters::attack(T parsedObject)
{
    // unimplemented
}
void charcters::talk_to(T parsedObject)
{
    // unimplemented
}

T examineInput(T parsedAction, T parsedObject
{
    std::string(tolower(parsedAction));
    if(parsedObject == item)
    {
      if(parsedAction == "use")
      {
          void items::use(T parsedObject);
      }
      else if(parsedAction == "take")
      {
          void items::take(T parsedObject);
      }
      else if(parsedAction == "look")
      {
          void items::look(T parsedObject);
      }
      else if(parsedAction == "examine")
      {
          void items::examine(T parsedObject);
      }
      else if(parsedAction == "open")
      {
          void items::open(T parsedObject);
      }
      else if(parsedAction == "read")
      {
          void items::read(T parsedObject);
      }
      else if(parsedAction == "throw")
      {
          void items::throw(T parsedObject);
      }
      else if(parsedAction == "unlock") // probably only going to be used for chests, doors, etc.
      {
          void items::unlock(T parsedObject);
      }
      else if(parsedAction == "put")
      {
          void items::put(T parsedObject);
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
            void locations::go_to(T parsedObject);
        }
        else if(parsedAction == "look")
        {
            void locations::look(T parsedObject);
        }
        else if(parsedAction == "leave")
        {
            void locations::leave(T parsedObject);
        }
        else if(parsedAction == "examine")
        {
            void locations::examine(T parsedObject);
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
            void characters::look(T parsedObject);
        }
        else if(parsedAction == "examine")
        {
            void characters::examine(T parsedObject);
        }
        else if(parsedAction == "attack")
        {
            void characters::attack(T parsedObject);
        }
        else if(parsedAction == "talk to")
        {
            void characters::talk_to(T parsedObject);
        }
        else
        {
            std::cout << parsedAction << " is not a valid input."
        }
    }
    else
    {
        std::cout << parsedObject << " was not recognized. Please try again.";
    }
    return x;
}
