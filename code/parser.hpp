#ifndef PARSER_HPP
#define PARSER_HPP

#include "gameobjects.hpp"

namespace parserspace
{
    std::set<std::string> unique_commands = {"credits", "exit", "help", "inventory", "leave"};
    std::set<std::string> predicate_set = {"a", "an", "at", "to", "the"};
    std::unordered_map<std::string, bool> command_map;
};

// Add proper function description here
void initialize_parser()
{
    assign_map_values(parserspace::command_map, {{"use", true}, {"take", false}, 
    {"go", false}, {"look", false}, {"read", false}, 
    {"talk", false}, {"attack", true}, {"examine", false},
    {"grab", false}, {"get", false}, {"drink", false}});
}

// Takes in a string and returns a vector of substrings split by whitespace.
std::vector<std::string> string_splitter(std::string str)
{
    std::vector<std::string> return_vec;
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
            return_vec.insert(return_vec.end(), str.substr(prev_index, cur_index - prev_index));
            prev_index = cur_index + 1;
        }
        else if (cur_index == std::string::npos && !return_vec.empty())
        {
            return_vec.insert(return_vec.end(), str.substr(prev_index, str.size()));
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

// Add proper function description here
std::pair<std::string, std::reference_wrapper<game_object>> game_input_parser(std::string input)
{
    std::string return_str;
    std::reference_wrapper<game_object> return_obj = specificvars::empty_object;

    if (input.empty())
    {
       return {return_str, return_obj};
    }

    std::vector<std::string> input_vec = string_splitter(input);
    std::size_t input_vec_size = input_vec.size();

    if (input_vec_size == 0)
    {
        return {return_str, return_obj};
    }
    else if (input_vec_size == 1 && parserspace::unique_commands.contains(input_vec.at(0)))
    {
        return_str = input_vec.at(0);
    }
    else if (parserspace::command_map.contains(input_vec.at(0)))
    {
        return_str = input_vec.at(0);
        
        int i = 1;
        while (i < input_vec_size)
        {
            if (!parserspace::predicate_set.contains(input_vec.at(i)))
            {
                break;
            }
            i++;
        }

        std::string combined_str;
        for (i; i < input_vec_size; i++)
        {
            if (i == input_vec_size - 1)
            {
                combined_str += input_vec.at(i);
            }
            else
            {
                combined_str += input_vec.at(i) + " ";
            }
        }

        if (!combined_str.empty()) 
        {
            return_obj = find_object(combined_str);
        }
    }

    return {return_str, return_obj};
}

#endif