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
        std::string cur_loc;
        std::string prev_loc;
        std::set<std::string> set_loc;
        std::vector<std::string> player_inv;
        std::unordered_map<std::string, bool> player_flags;

    public:
        // Public default constructor
        player_info() {}
        // Public constructor called by main
        player_info(std::string str)
        {
            cur_loc = "game start";
            prev_loc = cur_loc;
            set_loc = specificvars::location_set_one;
            player_inv = {};
            player_flags.insert_or_assign("is_alive", true);

            // Add items immediately to inventory upon construction
            player_inv.insert(player_inv.end(), "sword");
            player_inv.insert(player_inv.end(), "shield");
        }
        // Class methods
        std::string get_player_loc()
        {
            return cur_loc;
        }
        std::string get_player_loc_prev()
        {
            return prev_loc;
        }
        std::set<std::string> get_player_loc_set()
        {
            return set_loc;
        }
        void set_player_loc(std::string loc)
        {
            prev_loc = cur_loc;
            cur_loc = loc;
        }
        void set_player_loc_set(std::set<std::string> loc)
        {
            set_loc = loc;
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
        // Removes an item from the player's inventory and 
        // (optionally) removes it permanently from the main_objects vector
        void remove_inv_item(std::string item_to_rem, bool remove_perm)
        {
            if (remove_object(player_inv, item_to_rem) && remove_perm)
            {
                remove_object(specificvars::main_objects, find_object(item_to_rem));
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