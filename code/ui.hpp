#ifndef UI_HPP
#define UI_HPP


//ftxui includes
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/box.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include <iostream>
#include "classesmisc.hpp"

//takes a standard string and breaks it into individual
//words to be later proccessed (primarily by the function
//wordWrapper)
std::vector<std::string> word_breaker(std::string raw)
{
    std::vector<std::string> words; // vector that will be filled and returned
    std::string temp; // intermediary string
    for (auto x : raw) // iterates through each character in raw
    {
        //if a whitespace is encountered current word is finished
        if (x == ' ')
        {
            words.insert(words.end(), temp); //add temp (storing current word) to the end of the vector
            temp = ""; //reset temp to an empty string
        }
        else temp = temp + x; // if the char isn't a whitespace add it to the end of temp
    }
    words.insert(words.end(),temp);
    return words;
}


//takes a vector of strings (words, presumably
//from wordBreaker), and converts the text into
//lines that are at most the given wrap size
void word_wrapper(std::vector<std::string> words, int wrap_size = 68)//[The default wrap size is arbitrarily chosen]
{
    std::string current_line;
    std::string border;
    
    //generating a border that will be placed before and after the main text
    for(int i = 0; i < wrap_size; ++i)
        border += "=";

    //printing the top border
    std::cout << border << std::endl;

    bool print_last; // keeps track on whether the last operation being preformed was appending or printing the line
    for (auto x: words) //iterate through each string in the vector
    {
        //if adding the current string to the current_line 
        //causes it to exceed the wrap size do operations
        if (x.length() + current_line.length() > wrap_size)
        {
            std::cout << current_line << std::endl; //print current_line
            current_line = x + " "; //reset current_line to be equal to the next word
        }

        //if you can add to the current_line without
        //exceeding wrap size, do so and add a space
        //at the end
        else
        {
            current_line = current_line + x + " ";
        }
    }

    //ensures that the last line is always
    //sent to the screen if there is anything present
    if (!current_line.empty() && current_line != " ")
        std::cout << current_line << std::endl;

    //printing the lower border
    std::cout << border << std::endl;
}

//takes user input from the cin stream and
//returns the result as a string in all lowercase
//for easier matching
std::string get_input()
{
    std::string temp;
    // Prompts for user input without skipping a line
    std::cout << "> ";
    // Reads user input into temp until a newline character is reached
    getline(std::cin, temp);
    // Simply converts input into uppercase for easy matching
    std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    // Returns the player input
    return temp;
}

//Function for returning NPC dialogue to the screen
//takes the text being spoken, the name of the speaker,
//and optional parameter format (by default ": ")
//outputs text in the style "Name: dialogue..."
void npc_text(std::string dialogue, std::string npcName, std::string format = ": ")
{
    std::string output = npcName + format + dialogue; // combines the given strings to format text correctly

    //breaks the output into individual words, this effectively sticks ": " to the end of the npcName as well
    std::vector<std::string> vecOutput = word_breaker(output);

    //due to the way wordWrapper is written, it not only ensures that there is only one space between words
    //but it also outputs the text to the screen without an additional function call
    word_wrapper(vecOutput);
}

//Function for returning narrator dialogue to the screen
//takes the text being 'spoken' and surrounds it with brackets
void narrator(std::string text)
{
    std::string output = "[" + text + "]";

    //breaks the output into individual words, this also effectively sticks "[" & "]"
    //to the first and last words respectively
    std::vector<std::string> vec_output = word_breaker(output);

    //due to the way wordWrapper is written, it not only ensures that there is only one space between words
    //but it also outputs the text to the screen without an additional function call
    word_wrapper(vec_output);
}

//Prompts the User whether they want to exit the game
//with a default message of "Are you sure?"
bool exit_seq(std::string output_text = "Warning: This game does not save progress. Are you sure you want to exit?")
{
    //prints the output text followed by a Y/N choice prompt and a newline to the screen
    std::string temp = output_text + "\n(Y/N)";
    word_wrapper(word_breaker(temp)); // likely same affect as directly doing cout the temp string, but better safe than sorry

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

//displays the inventory of the given player to the screen
//in the format
//Your bag contains:
// > itemName
// > itemName
// > ...
void display_inventory(player_info player)
{
	std::vector<std::string> inv = player.get_inv_vector();
	//if the player inventory is empty output a message
	//telling the player their inventory is empty
	if (inv.size() == 0)
		std::cout << "Your inventory is empty" << std::endl;
		
	int i = 0;
	std::cout << "Your bag contains:" << std::endl;
	//loops over a number of times equal to the inventory size
	//and displays each item at the corresponding place within
	//the inventory
	while (i < inv.size())
	{
		std::cout << " > A " << inv.at(i) << std::endl;
		++i;
	}
}

//displays the player's current location,
//followed by a newline, to the screen
void display_location(player_info player)
{
	std::cout << "You are at " << player.get_player_loc() << std::endl;
}

//displays a thank you message for playing the game
//followed by a credits section which contains each
//group memeber and their responsibilities
void display_credits()
{
	std::cout << "Thanks For Playing!" << std::endl;
	std::cout << "=============================================================" << std::endl;
	std::cout << "Project Lead & Input Parser Designer: Connor Morris" << std::endl;
	std::cout << "UI Designer: Lane Durst" << std::endl;
	std::cout << "Story Leads & Object Designers: Logan Remondet & Shawn Russel" << std::endl;
	std::cout << "Map Lead & Object Action Designers: Yu Joo & Maureen Sanchez" << std::endl;
	std::cout << "=============================================================" << std::endl;
}

#endif