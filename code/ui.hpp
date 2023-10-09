// Add necessary includes & imports here
#include "catch.hpp"
#include <iostream>
#include <string>
#include <stdio.h>

// Method for prompting and reading user input
std::string get_input()
{
    std::string temp;
    // Prompts for user input without skipping a line
    std::cout << "> ";
    // Reads user input into temp until a newline character is reached
    getline(std::cin, temp);
    // Returns the player input
    return temp;
}

// Function for returning npc dialogue to the screen
void npc_text(std::string dialogue, std::string npcName, std::string format = ": ")
{
    int wrap = 100;
    // Default formatting takes the style [Name: dialogue], however the format field was included
    // as an optional argument in case specific NPC entities should have different dialogue style
    if (dialogue.length() > wrap)
    {
        // unimplemented
    }
    std::string output = npcName + format + dialogue;
    std::cout << output << std::endl;
}

// Method for returning all non-dialogue information to the screen
void narrator(std::string text)
{
    std::cout << "[" + text + "]" << std::endl;
}

// TODO: Test this function properly
bool exit_seq()
{
    std::cout << "Are you sure? (Y/N)" << std::endl;
    // Creates a loop that continuously gets the next character until it finds either a Y or N reply
    while (true)
    {
        char reply = getchar();
        if (reply == 'y' || reply == 'Y')
        {
            return true;
        }
        else if (reply == 'n' || reply == 'N')
        {    
            return false;
        }
    }
}