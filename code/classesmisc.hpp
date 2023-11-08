#ifndef CLASSESMISC_HPP
#define CLASSESMISC_HPP

#include "gameobjects.hpp"

// This class contains all info about the player, 
// including their current location, their inventory, 
// and any flags they've set. It is instanced upon
// the program start or game loop restart.
class player_info 
{
    private:
        std::vector<game_object>::iterator player_location;
        std::vector<std::string> player_inv;
        std::unordered_map<std::string, bool> player_flags;

    public:
        // Public default constructor
        player_info() {}
        // Public constructor called by main
        player_info(std::string str)
        {
            player_location = specificvars::main_objects.begin();
            player_inv = {};
            player_flags.insert_or_assign("is_alive", true);

            // Add items immediately to inventory upon construction
            player_inv.insert(player_inv.end(), "sword");
            player_inv.insert(player_inv.end(), "shield");
        }
        // Class methods
        std::string get_player_loc()
        {
            return (*player_location).get_object_name();
        }
        void set_player_loc(game_object &loc)
        {
            if (loc != specificvars::empty_object)
            {
                player_location = find_iter(specificvars::main_objects, loc);
            }
        }
        bool get_inv_item(std::string item_to_get)
        {
            return !(get_object(player_inv, item_to_get).empty());
        }
        void add_inv_item(game_object &item_to_add)
        {
            if (item_to_add != specificvars::empty_object)
            {
                item_to_add.set_object_loc("playerinventory");
                player_inv.insert(player_inv.end(), item_to_add.get_object_name());
            }
        }
        // Removes an item from the players inventory and 
        // (optionally) removes it permanently from the main_objects vector
        void remove_inv_item(std::string item_to_rem, bool remove_perm)
        {
            if (remove_object(player_inv, item_to_rem) && remove_perm)
            {
                remove_object(specificvars::main_objects, find_object(item_to_rem));
            }
        }
        // Returns a string containing the names of all items in the player's inventory
        std::string get_inv_string()
        {
            std::string str;
            for (std::string s : player_inv)
            {
                if (s == *player_inv.begin())
                {
                    str.append("Current inventory: " + s);
                }
                else
                {
                    str.append(", " + s);
                }
            }
            if (str.empty())
            {
                return "Inventory is currently empty!";
            }
            else
            {
                return str + ".";
            }
        }
        // NOTE: DOES NOT PASS BY REFERENCE
        std::vector<std::string> get_inv_vector()
        {
            return player_inv;
        }
        // If flag exists, returns true; otherwise, returns false.
        bool get_player_flag(std::string flag)
        {
            if (player_flags.count(flag) != 0)
            {
                return player_flags.at(flag);
            }
            else
            {
                return false;
            }
        }
        // Either adds a new flag with the key `name` and value `val`,
        // or sets the value of the existing key `name` to `val`.
        void set_player_flag(std::string name, bool val)
        {
            player_flags.insert_or_assign(name, val);
        }
        void remove_player_flag(std::string flag)
        {
            player_flags.erase(flag);
        }
        bool get_player_state()
        {
            return player_flags.at("is_alive");
        }
        void set_player_state(bool state)
        {
            player_flags.insert_or_assign("is_alive", state);
        }
};

#endif