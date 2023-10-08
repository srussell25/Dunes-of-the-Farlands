// Add necessary includes & imports here
#include "catch.hpp"
#include <iostream>
#include <string>
#include <stdio.h>

// method for prompting and reading user input
std::string getInput()
{
    std::string temp;
    // prompts for user input without skipping a line
    std::cout<<"> ";
    // reads user input into temp until a newline character is reached
    getline(std::cin,temp);
    // returns the player input
    return temp;
}

// function for returning npc dialogue to the screen
void npcText(std::string dialogue, std::string npcName, std::string format = ": ")
{
    int wrap = 100;
    // default formatting takes the style [Name: dialogue], however the format field was included
    // as an optional argument in case specific NPC entities should have different dialogue style
    if (dialogue.length() > wrap)
    {

    }
    std::string output = npcName+format+dialogue;
    std::cout<<output<<std::endl;
}

// method for returning all non dialogue information to the screen
void narrator(std::string Text)
{
    std::cout<<"["+Text+"]"<<std::endl;
}

// TODO: make sure this actually functions lol
bool exitSeq()
{
    std::cout<<"Are you sure? (Y/N)"<<std::endl;
    // creates a loop that continuously gets the next character until it finds either a Y or N reply
    while (true)
    {
    char reply = getchar();
    if (reply == 'y' || reply == 'Y')
        return true;
    else if (reply == 'n' || reply == 'N')
        return false;
    }
}

// TODO: decide if this function is needed
void pauseGame()
{
    std::cout<<"1] Resume"<<std::endl<<"2] Save Game"<<std::endl<<"3] Save and Exit"<<std::endl;
    char input = getchar();
    switch (input)
    {
        case '1':
            break;
        case '2':
            // save function here
            break;
        case '3':
            // save function here
            if (exitSeq() == true)
                exit(0);
            break; // should be unneccesary, but better safe than sorry
    }
}