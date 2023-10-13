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
        std::vector<std::string> flags;
        //std::vector<game_object>::iterator invIter;
        //std::vector<std::string>::iterator flagIter;
        bool isAlive;
    
    public:
        // Public default constructor
        player_info() {}
        // Public constructor called by main
        player_info(std::string str)
        {
            currentLocation = *mainObjects.begin();
            inventory = {};
            flags = {};
            isAlive = true;
        }
        // Class methods
        void set_location(game_object location)
        {
            currentLocation = location;
        }
        game_object get_location()
        {
            return currentLocation;
        }
        // TODO: Fix player inventory
        void add_item(game_object item)
        {
            inventory.insert(inventory.end(), item);
        }
        void remove_item(game_object item)
        {
            if (std::find(inventory.begin(), inventory.end(), item) != inventory.end())
            {
                inventory.erase(std::find(inventory.begin(), inventory.end(), item));
            }
        }
        game_object find_item(game_object item) 
        {
            return *std::find(inventory.begin(), inventory.end(), item);
        }
        // TODO: Fix player flags
        void add_flag(std::string flag) 
        {
            flags.insert(flags.end(), flag);
        }
        void remove_flag(std::string flag) 
        {
            if (std::find(flags.begin(), flags.end(), flag) != flags.end()) 
            {
                flags.erase(std::find(flags.begin(), flags.end(), flag));
            }
        }
        std::string find_flag(std::string flag) 
        {
            if (std::find(flags.begin(), flags.end(), flag) != flags.end()) 
            {
                return *std::find(flags.begin(), flags.end(), flag);
            }
            return "flag_not_found";
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