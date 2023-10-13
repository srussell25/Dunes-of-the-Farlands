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
        std::vector<game_object>::iterator invIter;
        std::vector<std::string>::iterator flagIter;
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
        void set_location(game_object &location)
        {
            currentLocation = location;
        }
        game_object get_location()
        {
            return currentLocation;
        }
        game_object find_item(game_object &item) 
        {
            invIter = std::find(inventory.begin(), inventory.end(), item);
            if (invIter != inventory.end()) 
            {
                return *invIter;
            }
            else
            {
                return game_object();
            }
        }
        void add_item(game_object &item)
        {
            inventory.insert(inventory.end(), item);
        }
        void remove_item(game_object &item)
        {
            invIter = std::find(inventory.begin(), inventory.end(), item);
            if (invIter != inventory.end()) 
            {
                inventory.erase(invIter);
            }
        }
        std::string find_flag(std::string flag) 
        {
            flagIter = std::find(flags.begin(), flags.end(), flag);
            if (flagIter != flags.end()) 
            {
                return *flagIter;
            }
            else
            {
                return "flag_not_found";
            }
        }
        void add_flag(std::string flag) 
        {
            flags.insert(flags.end(), flag);
        }
        void remove_flag(std::string flag) 
        {
            flagIter = std::find(flags.begin(), flags.end(), flag);
            if (flagIter != flags.end()) 
            {
                flags.erase(flagIter);
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