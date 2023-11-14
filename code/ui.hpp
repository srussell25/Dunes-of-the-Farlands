#ifndef UI_HPP
#define UI_HPP

#include "classesmisc.hpp"

//generates a border (meant to be place on top and bottom of a string), made of '=' at the
//specified border size
std::string generate_border(int border_size = 88) //[The default border size is chosen to match the Titlecard]
{
    std::string border;
    for (int i = 0; i < border_size; ++i)
    {
        border += "=";
    }
    return border;
}

//calculates the number of spaces needed on either side of the text for it to be centered based on the
//line length, and appends them to each side of the string. If the text is too large for the given line
//length the method effectively returns the original string. If the line length is not an even value the
//method rounds down during the center_displacement calculation.
std::string center_text(std::string text, int line_length = 88) //[The default line length is chosen to match the Titlecard]
{
    int center_displacement = floor((line_length - text.size()) / 2);
    for (int i = 0; i < center_displacement; ++i)
    {
        text = " " + text + " ";
    }
    return text;
}

//takes a standard string and breaks it into individual words to be later proccessed (primarily by the
//function wordWrapper)
std::vector<std::string> word_breaker(std::string raw)
{
    std::vector<std::string> words;
    std::string temp;
    for (auto x : raw) // iterates through each character in raw
    {
        //if a whitespace is encountered current word is finished
        if (x == ' ')
        {   
            if (temp != "")
            {
                words.insert(words.end(), temp); //add temp (storing current word) to the end of the vector
            }
            temp = "";
        }
        else 
        {
            temp = temp + x; // if the char isn't a whitespace add it to the end of temp
        }
    }
    words.insert(words.end(), temp); // add whatever is left (if anything to the end of temp)
    return words;
}

//takes a vector of strings (words, presumably from wordBreaker), and converts the text into lines that 
//are at most the given wrap size and outputs them to the screen
void word_wrapper(std::vector<std::string> words, int wrap_size = 88)//[The default wrap size is chosen to match the Titlecard]
{
    std::string current_line;
    for (auto x: words) //iterate through each string in the vector
    {
        //if adding the current string to the current_line causes it to exceed the wrap size, output and reset
        //the string
        if (x.length() + current_line.length() > wrap_size)
        {
            std::cout << current_line << std::endl;
            current_line = x + " "; //reset current_line to be equal to the next word and a space
        }
        else //if you can add to the current_line without exceeding wrap size, do so and add a space at the end
        {
            current_line = current_line + x + " ";
        }
    }

    //ensures that the last line is always sent to the screen if there is anything present
    if (!current_line.empty() && current_line != " ")
    {
        std::cout << current_line << std::endl;
    }

    //printing the lower border
    std::cout << generate_border() << std::endl;
}

//prompts user for input, and then takes user input from the cin stream and returns the result as a 
//string in all lowercase for easier matching
std::string get_input()
{
    std::string temp;
    std::cout << "> ";
    getline(std::cin, temp); // Reads user input into temp until a newline character is reached

    std::cout << generate_border() << std::endl;

    std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // Simply converts input into lowercase
    return temp;
}

//Function for returning NPC dialogue to the screen takes the text being spoken, the name of the speaker,
//and optional parameter format (by default ": ") outputs text in the style "Name: dialogue..."
void npc_text(std::string dialogue, std::string npc_name, std::string format = ": ")
{
    std::string output = npc_name + format + dialogue;

    //breaks the output into individual words, this effectively sticks ": " to the end of the npcName as well
    std::vector<std::string> vec_output = word_breaker(output);

    word_wrapper(vec_output);
}

//Function for returning narrator dialogue to the screen. takes the text being 'spoken' and surrounds 
//it with brackets
void narrator(std::string text)
{
    std::string output = "[" + text + "]";

    //breaks the output into individual words, this effectively sticks "[" & "]" to the first and last
    //words respectively
    std::vector<std::string> vec_output = word_breaker(output);

    word_wrapper(vec_output);
}

//Prompts the User whether they want to exit the game with a default message of "Are you sure?"
bool exit_seq(std::string output_text = "default")
{
    std::string query_text = "(Y/N)";

    //the default text is too long for one line, so if the argument
    //is left default (or set equivalent) instead use the two output
    //strings generated below
    std::string output_text1 = "Warning: This game does not save progress.";
    std::string output_text2 = "Are you sure you want to exit?";

    //prints the approptiate output text followed by a Y/N query
    //then a border, and finally a newline containg a user input prompt
    if (output_text == "default")
    {
        std::cout << center_text(output_text1) << std::endl;
        std::cout << center_text(output_text2) << std::endl;
    }
    else
    {
        std::cout << center_text(output_text) << std::endl;
    }

    std::cout << center_text(query_text) << std::endl;
    std::cout << generate_border() << std::endl;

    std::cout << "> ";
    //NOTE: this ^ is used rather than get_input because this specific method needs to read char by char
    //until a y or n is found, unlike get_input which reads a whole line

    //wait until user enters a y or a n
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

//displays the inventory of the given player to the screen in the format
//Your bag contains:
// > A itemName
// > A itemName
// > ...
void display_inventory(player_info player)
{
	std::vector<std::string> inv = player.get_inv_vector();
	
	if (inv.size() == 0)
    {
		std::cout << "Your inventory is empty" << std::endl;
    }

	int i = 0;
	std::cout << "Your bag contains:" << std::endl;

	while (i < inv.size())
	{
		std::cout << (" - A " + inv.at(i)) << std::endl;
		++i;
	}
    
    std::cout << generate_border() << std::endl;
}

//displays the player's current location, followed by a border, to the screen
void display_location(player_info player)
{
	std::cout << ("You are at " + player.get_player_loc()) << std::endl;
    std::cout << generate_border() << std::endl;
}

//displays a thank you message for playing the game followed by a credits section which contains each
//group memeber and their responsibilities
void display_credits()
{
    std::string border = generate_border();
    std::string thank_you_message = "Thank you for playing!";

    thank_you_message = center_text(thank_you_message);
    
	std::cout << thank_you_message << std::endl;
	std::cout << border << std::endl;
	std::cout << "Project Lead & Input Parser Designer: Connor Morris" << std::endl;
	std::cout << "UI Designer: Lane Durst" << std::endl;
	std::cout << "Story Leads & Gameplay Designers: Logan Remondet & Shawn Russel" << std::endl;
	std::cout << "Story Implementers & General Designers: Yu Joo & Maureen Sanchez" << std::endl;
	std::cout << border << std::endl;
}

//text for the titlecard function. Looks strange due to counteracting exit sequence chars, but works fine
const std::string titlecard_text = "  ___                      ___   __   _____ _          ___         _              _    \n"
" |   \\ _  _ _ _  ___ ___  / _ \\ / _| |_   _| |_  ___  | __|_ _ _ _| |__ _ _ _  __| |___\n"
" | |) | || | ' \\/ -_|_-< | (_) |  _|   | | | ' \\/ -_) | _/ _` | '_| / _` | ' \\/ _` (_-<\n"
" |___/ \\_,_|_||_\\___/__/  \\___/|_|     |_| |_||_\\___| |_|\\__,_|_| |_\\__,_|_||_\\__,_/__/\n";

//displays and ascii art titlecard to the screen with appropriate border and a message telling
void display_titlecard()
{
    std::string border = generate_border();
    std::cout << border << std::endl;
    std::cout << titlecard_text << std::endl;
    std::cout << border << std::endl;
}

#endif