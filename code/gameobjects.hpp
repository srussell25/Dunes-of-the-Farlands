#ifndef GAMEOBJECTS_HPP
#define GAMEOBJECTS_HPP

// This class contains information about any object within the game
class game_object
{
    private:
        std::string objectType;
        std::string objectName;
        std::string objectDescription;
        std::string objectLocation; 
        std::vector<std::string> objectFlags;
        std::vector<std::string>::iterator flagIter;

    public:
        // Public default constructor
        game_object() {}
        // Public constructor which sets a game_object's type, name & description only.
        game_object(std::string oType, std::string oName, std::string oDesc)
        {
            objectType = oType;
            objectName = oName;
            objectDescription = oDesc;
            objectFlags = {};
        }
        // Public constructor which sets a game_object's type, name, description, as well as its flags.
        game_object(std::string oType, std::string oName, std::string oDesc, std::vector<std::string> oFlags)
        {
            objectType = oType;
            objectName = oName;
            objectDescription = oDesc;
            objectFlags = oFlags;
        }
        // Comparison operators
        friend bool operator==(game_object const& x, game_object const& y)
        {
            return x.objectName == y.objectName;
        }
        friend bool operator!=(game_object const& x, game_object const& y)
        {
            return !(x.objectName == y.objectName);
        }
        // Other methods
        void set_object_name(std::string name)
        {
            objectName = name;
        }
        std::string get_object_type()
        {
            return objectType;
        }
        std::string get_object_name()
        {
            return objectName;
        }
        std::string get_object_description()
        {
            return objectDescription;
        }
        std::string get_object_flag(std::string flag) 
        {
            flagIter = std::find(objectFlags.begin(), objectFlags.end(), flag);
            if (flagIter != objectFlags.end()) 
            {
                return *flagIter;
            }
            else
            {
                return "flag_not_found";
            }
        }
        void add_object_flag(std::string flag)
        {
            objectFlags.insert(objectFlags.begin(), flag);
        }
        void remove_object_flag(std::string flag)
        {
            flagIter = std::find(objectFlags.begin(), objectFlags.end(), flag);
            if (flagIter != objectFlags.end()) 
            {
                objectFlags.erase(flagIter);
            }
        }
};

// The master list of all objects in the game; add objects to this vector after creation.
std::vector<game_object> mainObjects = {};

game_object emptyObject;

// This function takes in a string meant to represent the name of a game_object, and then 
// searches within the vector mainObjects to see if that game_object exists. If it exists, 
// the function returns the game_object; otherwise, it returns an empty game_object.
game_object& find_object(std::string objName)
{
    std::vector<game_object>::iterator iter = std::find_if(mainObjects.begin(), mainObjects.end(), 
    [objName](game_object obj){ return obj.get_object_name() == objName; });

    if (iter != mainObjects.end()) 
    {
        return *iter;
    }
    else
    {
        return emptyObject;
    }
}

// NOTE: When making a game_object you must set its name, its type (either "item", "location", or "character"),
//       and its description at minimum. Optionally, you can also add a vector of strings containing various flags
//       for that object, but keep in mind you can always add (and remove) flags at a later point if needed.

// This function initializes all game objects at the start of the program's runtime.
void initialize_game_objects() {

    // Check if game has already started; if mainObjects is not empty then
    // clear mainObjects & re-add objects in their default state to restart game.
    if (!mainObjects.empty()) {
        mainObjects.clear();
    }

    // Initializing items (objects of type "item")
    mainObjects.insert(mainObjects.end(), game_object("item", "sword", "You look upon an ordinary sword; "
    "it's not pretty, but it gets the job done."));
    mainObjects.insert(mainObjects.end(), game_object("item", "shield", "You look upon an ordinary shield; "
    "it may be made out of wood, but it'll protect you well enough. Maybe."));
    mainObjects.insert(mainObjects.end(), game_object("item", "chestkey", "This is, almost certainly, "
    "the key to the chest. The engraving on the side says 'chest key';"
    " I'd be surprised if it was for anything else."));
    mainObjects.insert(mainObjects.end(), game_object("item", "chest", "You look at the chest and see "
    "that it is... a chest. What, did you expect a mimic or something?"));
    mainObjects.insert(mainObjects.end(), game_object("item", "note", "The note reads: 'January 18th. "
    "Seen some bandits around here recently. Trying to stay out of sight. I know it's part of"
    " my job to keep this chest protected, but I won't make it out here much longer.'")); 
    mainObjects.insert(mainObjects.end(), game_object("item", "drink", "It's the drink the barkeep gave you at the tavern."
    " You get the feeling it'd be nice to take a drink within the tavern.", {"at_location"}));

    // Initializing locations (objects of type "location")
    mainObjects.insert(mainObjects.begin(), game_object("location", "game start", "It's shabby, and a place of calm tension.", {"at_start"}));
    mainObjects.insert(mainObjects.end(), game_object("location", "abandoned town", "The town seems abandoned. All you can see is dilapidated buildings."));
    mainObjects.insert(mainObjects.end(), game_object("location", "oasis", "You look at what seems to be a beautiful oasis."));
    mainObjects.insert(mainObjects.end(), game_object("location", "tavern", "It's a tavern; I wonder if there's anyone inside?"));

    // Initializing characters (objects of type "character")
    // NOTE: The "is_alive" string is an example of a flag being set; in this case, it's used for checking if the bandit is alive 
    //       (if the string exists, the flag is "set"; if the flag doesn't exist, it's not "set".)
    mainObjects.insert(mainObjects.end(), game_object("character", "bandit", "This guy is looking rather shifty hanging out over there.", {"is_alive"}));
    mainObjects.insert(mainObjects.end(), game_object("character", "old lady", "You see an old lady who seems to be having trouble with something,"
    " although you can't quite make out what it is she's having trouble with. Maybe you should try talking to her?"));
    mainObjects.insert(mainObjects.end(), game_object("character", "barkeep", "The barkeep is keeping themselves occupied by wiping down glasses."));
}

#endif