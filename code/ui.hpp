#ifndef UI_HPP
#define UI_HPP

#include "classesmisc.hpp"

/// \brief Generates a border made of '=' of a specified size,
/// meant to be placed before or after a string
/// \param border_size The size of the border to be generated;
/// by default, is set to match the length of the titlecard
/// @return The border generated by this function as a string
std::string generate_border(int border_size = 88)
{
    std::string border;
    for (int i = 0; i < border_size; ++i)
    {
        border += "=";
    }
    return border;
}

/// \brief Calculates the number of spaces needed on either side of `text` for it to be 
/// centered based on a specific line length, then appends them to each side of the string.
/// @param text The string of text to be centered
/// \param line_length The length of the line for the text to be centered in;
/// by default, is set to match the length of the titlecard
/// @return Returns centered text or the original string if it's too large to be centered
std::string center_text(std::string text, int line_length = 88)
{
    int center_displacement = floor((line_length - text.size()) / 2);
    for (int i = 0; i < center_displacement; ++i)
    {
        text = " " + text + " ";
    }
    return text;
}

/// @brief Breaks a string into individual words so that it can be processed by another function
/// @param raw The raw text string to be broken apart
/// @return The vector of words generated by splitting the raw text
std::vector<std::string> word_breaker(std::string raw)
{
    std::vector<std::string> words;
    std::string temp;
    for (auto x : raw) // Iterate through each character in `raw`
    {
        if (x == ' ') // If a whitespace is encountered, the current word is finished
        {   
            if (temp != "")
            {
                words.insert(words.end(), temp); // Add stored current word to the end of `words`
            }
            temp = "";
        }
        else 
        {
            temp = temp + x; // If the char isn't a whitespace, add it to the end of `temp`
        }
    }
    words.insert(words.end(), temp); // Add anything left from `temp` to `words`
    return words;
}

/// \brief Converts a vector of strings (assumed to be words from `word_breaker`) into 
/// lines of a size LEQ `wrap_size`; the final output is then sent to the terminal
/// @param words The vector containing all the words to be wrapped
/// \param wrap_size The max length of the line for the text to be wrapped 
/// in; by default, is set to match the length of the titlecard
void word_wrapper(std::vector<std::string> words, int wrap_size = 88)
{
    std::string current_line;
    for (auto x: words) // Iterate through each string in `words`
    {
        if (x.length() + current_line.length() > wrap_size)
        { // If the current string + `current_line` exceeds `wrap_size`, output and reset the string
            std::cout << current_line << std::endl;
            current_line = x + " "; // Reset `current_line` to be equal to the next word, then add a space
        }
        else // Add string to `current_line` if it doesn't exceed `wrap_size`, then add a space
        {
            current_line = current_line + x + " ";
        }
    }

    if (!current_line.empty() && current_line != " ")
    {
        std::cout << current_line << std::endl; // Ensures the last line is always sent (if it exists)
    }

    std::cout << generate_border() << std::endl; // Printing the lower border
}

/// @brief Prompts the player for input and then stores the cin stream
/// @return A string of input text converted into all lowercase for easier matching
std::string get_input()
{
    std::string input;
    std::cout << "> ";
    getline(std::cin, input); // Reads user input into `input` until a newline character is reached

    std::cout << generate_border() << std::endl;

    std::transform(input.begin(), input.end(), input.begin(), ::tolower); // Converts `input` into lowercase
    return input;
}

/// \brief Outputs text as NPC dialogue via formatting the "spoken" text
/// with the name of the speaker and optional style parameter
/// @param dialogue The string of text to be spoken by the NPC
/// @param npc_name The name of the NPC who will be speaking
/// @param format Optional style paramter for changing how the text is shown
void npc_text(std::string dialogue, std::string npc_name, std::string format = ": ")
{
    std::string npc_name_upper = "";
    std::vector<std::string> npc_vec = word_breaker(npc_name);
    for (std::string x : npc_vec) // Making the first letter of each word uppercase
    {
        if (x != npc_vec.back())
        {
            x.at(0) = toupper(x.at(0));
            npc_name_upper += (x + " ");
        }
        else
        {
            x.at(0) = toupper(x.at(0));
            npc_name_upper += x;
        }
    }

    std::string output = npc_name_upper + format + dialogue; // Places the name of the NPC and the style parameter before the dialogue

    std::vector<std::string> vec_output = word_breaker(output); // Breaks `output` into individual words

    word_wrapper(vec_output); // `word_wrapper` sends the output text to the terminal after formatting
}

/// @brief Outputs text as narrator dialogue by taking the text being "spoken" and surrounding it with brackets
/// @param text The text that will be formatted & then sent to the terminal
void narrator(std::string text)
{
    std::string output = "[" + text + "]"; // Places "[" & "]" between the start and end of the output text

    std::vector<std::string> vec_output = word_breaker(output); // Breaks `output` into individual words

    word_wrapper(vec_output); // `word_wrapper` sends the output text to the terminal after formatting
}

/// @brief Prompts the player with a Y/N selection loop; it's set up by default for the game's exit sequence
/// @param output_text The text that will be sent to the console before querying for a Y/N response
/// @return A boolean value representing if the player chose yes (`true`) or no (`false`)
bool exit_seq(std::string output_text = "default")
{
    std::string query_text = "(Y/N)";
    std::string output_text1 = "Warning: This game does not save progress.";
    std::string output_text2 = "Are you sure you want to exit?";

    if (output_text == "default") // Output the strings stored above if the default argument is used
    {
        std::cout << center_text(output_text1) << std::endl;
        std::cout << center_text(output_text2) << std::endl;
    }
    else
    {
        std::cout << center_text(output_text) << std::endl;
    }

    std::cout << center_text(query_text) << std::endl; // Print the Y/N query
    std::cout << generate_border() << std::endl; // Print a border to separate the input prompt

    std::cout << "> "; // Not using get_input() because this method reads char-by-char

    while (true) // Wait until the player enters Y or N (or their lowercase equivalents)
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

/// @brief Outputs a formatted list of the player's current inventory to the terminal
/// @param player An instance of `player_info` representing the player's current state
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

/// @brief Outputs the player's current location, followed by a border, to the terminal
/// @param player An instance of `player_info` representing the player's current state
void display_location(player_info player)
{
    std::string current_location = "";
    std::vector<std::string> location_vec = word_breaker(player.get_player_loc());
    for (std::string x : location_vec) // Making the first letter of each word uppercase
    {
        if (x != location_vec.back())
        {
            x.at(0) = toupper(x.at(0));
            current_location += (x + " ");
        }
        else
        {
            x.at(0) = toupper(x.at(0));
            current_location += x;
        }
    }
    current_location = "You are currently at the " + current_location + ".";

	std::cout << current_location << std::endl;
    std::cout << generate_border() << std::endl;
}

/// \brief Outputs a thank-you message to the console, followed 
/// by a list of group members and their contributions
void display_credits()
{
    const std::string border = generate_border();
    
	std::cout << center_text("Thank you for playing!") << std::endl;
	std::cout << border << std::endl;
	std::cout << "Project Lead & Input Parser Designer: Connor Morris" << std::endl;
	std::cout << "Main Loop & UI Designer: Lane Durst" << std::endl;
	std::cout << "Story Leads & Gameplay Designers: Logan Remondet & Shawn Russell" << std::endl;
	std::cout << "Story Implementers & Program Designers: Yu Joo & Maureen Sanchez" << std::endl;
	std::cout << border << std::endl;
}

/// @brief Outputs an ASCII art titlecard to the terminal surrounded by borders
void display_titlecard()
{
    const std::string titlecard_text = "  ___                      ___   __   _____ _          ___         _              _    \n"
    " |   \\ _  _ _ _  ___ ___  / _ \\ / _| |_   _| |_  ___  | __|_ _ _ _| |__ _ _ _  __| |___\n"
    " | |) | || | ' \\/ -_|_-< | (_) |  _|   | | | ' \\/ -_) | _/ _` | '_| / _` | ' \\/ _` (_-<\n"
    " |___/ \\_,_|_||_\\___/__/  \\___/|_|     |_| |_||_\\___| |_|\\__,_|_| |_\\__,_|_||_\\__,_/__/\n";
    const std::string border = generate_border();
    
    std::cout << border << std::endl;
    std::cout << titlecard_text << std::endl;
    std::cout << border << std::endl;
}

#endif