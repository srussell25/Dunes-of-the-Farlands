#ifndef CLASSESMISC_HPP
#define CLASSESMISC_HPP

// This class contains all info about the player, 
// including their current location, their inventory, 
// and any flags they've set. It is instanced upon
// the program start or game loop restart.
class player_info 
{
    private:
        std::vector<game_object>::iterator currentLocation;
        std::vector<std::string> inventory;
        std::vector<std::string> playerFlags;
        bool isAlive;

    public:
        // Public default constructor
        player_info() {}
        // Public constructor called by main
        player_info(std::string str)
        {
            currentLocation = specificvars::mainObjects.begin();
            inventory = {};
            playerFlags = {};
            isAlive = true;

            // Add certain items immediately to player inventory
            inventory.insert(inventory.end(), "sword");
            inventory.insert(inventory.end(), "shield");
        }
        // Class methods
        std::string get_player_loc()
        {
            return (*currentLocation).get_object_name();
        }
        void set_player_loc(game_object &newLoc)
        {
            if (newLoc != specificvars::emptyObject)
            {
                currentLocation = find_iter(specificvars::mainObjects, newLoc);
            }
        }
        bool get_inv_item(std::string itemToGet)
        {
            if (get_object(inventory, itemToGet) == std::string())
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        void add_inv_item(game_object &itemToAdd)
        {
            if (itemToAdd != specificvars::emptyObject)
            {
                itemToAdd.set_object_loc("playerinventory");
                inventory.insert(inventory.end(), itemToAdd.get_object_name());
            }
        }
        // Removes an item from the players inventory and 
        // (optionally) removes it permanently from the mainObjects vector
        void remove_inv_item(std::string itemToRemove, bool permRemove)
        {
            if (remove_object(inventory, itemToRemove) && permRemove)
            {
                remove_object(specificvars::mainObjects, find_object(itemToRemove));
            }
        }
        // Returns a string containing the names of all items in the player's inventory
        std::string get_inv_string()
        {
            std::string str;
            for (std::string s : inventory)
            {
                if (s == *inventory.begin())
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
        std::string get_player_flag(std::string flagToGet)
        {
            return get_object(playerFlags, flagToGet);
        }
        void add_player_flag(std::string flagToAdd)
        {
            if (!flagToAdd.empty())
            {
                playerFlags.insert(playerFlags.end(), flagToAdd);
            }
        }
        void remove_player_flag(std::string flagToRemove)
        {
            remove_object(playerFlags, flagToRemove);
        }
        bool get_player_state()
        {
            return isAlive;
        }
        void set_player_state(bool state)
        {
            isAlive = state;
        }
};

// TODO: Implement game_flags class with two private variables, 
// flag name (string) and flag status (bool), and then add
// public functions to access & modify those variables
class game_flags 
{
    // unimplemented
};

#endif