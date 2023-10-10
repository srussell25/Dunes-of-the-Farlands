#ifndef PLAYERCHARACTER_HPP
#define PLAYERCHARACTER_HPP

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
        player_info()
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
        void add_item(game_object item)
        {
            inventory.insert(inventory.end(), item);
        }
        void remove_item(game_object item)
        {
            invIter = std::find(inventory.begin(), inventory.end(), item);
            inventory.erase(invIter);
        }
        game_object find_item(game_object item) 
        {
            return *std::find(inventory.begin(), inventory.end(), item);
        }
        void add_flag(std::string flag) 
        {
            flags.insert(flags.end(), flag);
        }
        void remove_flag(std::string flag) 
        {
            flagIter = std::find(flags.begin(), flags.end(), flag);
            flags.erase(flagIter);
        }
        std::string find_flag(std::string flag) 
        {
            return *std::find(flags.begin(), flags.end(), flag);
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

#endif