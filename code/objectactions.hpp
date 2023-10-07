// Add necessary includes & imports here
#include <iostream>
#include "catch.hpp"
#include "gameobjects.hpp"
#include "main.cpp"




/*the functions should check if you have the right check to see if you can preform the action for example
if you try to take a item you need to make sure that you can reach it (if there is a thing in the way) or even
if your in the same location as the item or in some cases if you even have the item to use in the first place */

//functions for Items
void items::take(T parsedObject){
//if in_location = true {take item} or if blocked by something check for that, block the user and say somthing like "can't take that right now"
}
void items::use(T parsedObject){
// check if they have_item and if the are in_location this is similar to the attack command 
}
void items::look(T parsedObject){

}
void items::examine(T parsedObject){

}
void items::open(T parsedObject){

}
void items::read(T parsedObject){

}
void items::Throw(T parsedObject){

}
void items::unlock(T parsedObject){

}
void items::put(T parsedObject){

}

//functions for locations
void locations::go_to(T parsedObject){
    /*change the users location based on where they are. if they are connected to the next place from where they are 
    move the player though the player_location variale or though bools turning on and off(this method can take a long time to set up
    if we give the player a way to move back and forth between locations). if they can't go to a location because its blocked check for that*/
}
void locations::look(T parsedObject){

}
void locations::leave(T parsedObject){

}
void locations::examine(T parsedObject){

}

//functions for characters

void characters::look(T parsedObject){

}
void characters::examine(T parsedObject){

}
void characters::attack(T parsedObject){

}
void charcters::talk_to(T parsedObject){

}


int function4(int x)

{
    return x;
}