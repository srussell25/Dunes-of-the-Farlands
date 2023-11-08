#ifndef PARSER_HPP
#define PARSER_HPP

#include "gameobjects.hpp"

// NOTE: list of all commands: go to, look at, examine, attack, take, 
// throw item, read, open, unlock, put, talk to, inventory, help, exit

// Temp. namespace & initialize function until I can think of a better solution
namespace tempspace
{
    std::vector<std::string> unique_commands = {"inventory", "help", "exit"};
    std::unordered_map<std::string, int> command_map;
};

void initialize_parser()
{
    // TODO: test, then add more commands
    assign_map_values(tempspace::command_map, {{"attack", 6}, {"take", 4}});
}

// Takes in a string and returns a vector of substrings split by whitespace.
std::vector<std::string> string_splitter(std::string str)
{
    std::vector<std::string> return_vec;
    std::string temp_str; // separate var right now for debug purposes
    std::size_t prev_index = 0;
    std::size_t cur_index = 1;

    if (str.size() <= 1)
    {
        return return_vec;
    }
 
    while (cur_index <= str.size())
    {
        cur_index = str.find(" ", prev_index);
        if (cur_index != std::string::npos)
        {        
            temp_str = str.substr(prev_index, cur_index - prev_index);
            return_vec.insert(return_vec.end(), temp_str);
            prev_index = cur_index + 1;
        }
        else if (cur_index == std::string::npos && !return_vec.empty())
        {
            temp_str = str.substr(prev_index, str.size());
            return_vec.insert(return_vec.end(), temp_str);
            break;
        }
        else
        {
            return_vec.insert(return_vec.end(), str);
            break;
        }
    }

    return return_vec;
}

// WIP new parser, put details here later
std::pair<std::string, std::reference_wrapper<game_object>> game_input_parser(std::string input)
{
    std::string return_str;
    std::reference_wrapper<game_object> return_obj = specificvars::empty_object;

    if (input.empty())
    {
       return {return_str, return_obj};
    }

    std::vector<std::string>::iterator input_iter;
    std::vector<std::string> input_as_vec = string_splitter(input);

    if (input_as_vec.empty())
    {
        return {return_str, return_obj};
    }
    else if (input_as_vec.size() == 1)
    {
        return_str = get_object(tempspace::unique_commands, input_as_vec.at(0));
    }
    else
    {
        
    }

    return {return_str, return_obj};
}

#endif