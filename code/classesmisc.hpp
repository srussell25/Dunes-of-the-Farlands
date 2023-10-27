#ifndef CLASSESMISC_HPP
#define CLASSESMISC_HPP

// This class contains all info about the player, 
// including their current location, their inventory, 
// and any flags they've set. It is instanced upon
// the program start or game loop restart.
class player_info 
{
    private:
        game_object currentLocation;
        std::vector<game_object> inventory;
        std::vector<std::string> playerFlags;
        bool isAlive;
    
        // Find iterator for object inside inventory vector
        std::vector<game_object>::iterator find_inv_iter(game_object &itemToFind) 
        {
            return std::find(inventory.begin(), inventory.end(), itemToFind);
        }
        // Find iterator for object inside playerFlags vector
        std::vector<std::string>::iterator find_flag_iter(std::string flagToFind) 
        {
            return std::find(playerFlags.begin(), playerFlags.end(), flagToFind);
        }

    public:
        // Public default constructor
        player_info() {}
        // Public constructor called by main
        player_info(std::string str)
        {
            currentLocation = find_object("game start");
            inventory = {};
            playerFlags = {};
            isAlive = true;

            // Add certain items immediately to player inventory
            inventory.insert(inventory.end(), find_object("sword"));
            inventory.insert(inventory.end(), find_object("shield"));
        }
        // Class methods
        std::string get_player_loc()
        {
            return currentLocation.get_object_name();
        }
        void set_player_loc(game_object &newLoc)
        {
            if (newLoc != specificvars::emptyObject)
            {
                currentLocation = newLoc;
            }
        }
        game_object& get_inv_item(std::string itemToGet)
        {
            std::vector<game_object>::iterator invIter = find_inv_iter(find_object(itemToGet));
            if (invIter != inventory.end())
            {
                return *invIter;
            }
            else
            {
                return specificvars::emptyObject;
            }
        }
        void add_inv_item(game_object &itemToAdd)
        {
            if (itemToAdd != specificvars::emptyObject)
            {
                itemToAdd.set_object_loc("playerinventory");
                inventory.insert(inventory.end(), itemToAdd);
            }
        }
        void remove_inv_item(game_object &itemToRemove)
        {
            std::vector<game_object>::iterator invIter = find_inv_iter(itemToRemove);
            if (invIter != inventory.end())
            {
                inventory.erase(invIter);
                remove_object(itemToRemove);
            }
        }
        std::string get_player_flag(std::string flagToGet)
        {
            std::vector<std::string>::iterator flagIter = find_flag_iter(flagToGet);
            if (flagIter != playerFlags.end())
            {
                return *flagIter;
            }
            else
            {
                return "not_found";
            }
        }
        void add_player_flag(std::string flagToAdd)
        {
            if (flagToAdd != "not_found")
            {
                playerFlags.insert(playerFlags.end(), flagToAdd);
            }
        }
        void remove_player_flag(std::string flagToRemove)
        {
            std::vector<std::string>::iterator flagIter = find_flag_iter(flagToRemove);
            if (flagIter != playerFlags.end())
            {
                playerFlags.erase(flagIter);
            }
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