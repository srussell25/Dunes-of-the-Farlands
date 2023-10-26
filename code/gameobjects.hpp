#ifndef GAMEOBJECTS_HPP
#define GAMEOBJECTS_HPP

// This class contains information about all of the game's objects
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
        // Public constructor which sets a game_object's type, name, description, and flags
        game_object(std::string oType, std::string oName, std::string oDesc, std::vector<std::string> oFlags)
        {
            objectType = oType;
            objectName = oName;
            objectDescription = oDesc;
            objectFlags = oFlags;
            objectLocation = "";
        }
        // Public constructor which sets a game_object's type, name, description, flags and location
        game_object(std::string oType, std::string oName, std::string oDesc, std::vector<std::string> oFlags, std::string oLoc)
        {
            objectType = oType;
            objectName = oName;
            objectDescription = oDesc;
            objectFlags = oFlags;
            objectLocation = oLoc;
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
        std::string get_object_type()
        {
            return objectType;
        }
        std::string get_object_name()
        {
            return objectName;
        }
        void set_object_name(std::string name)
        {
            objectName = name;
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
                return "not found";
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
        std::string get_location() 
        {
            return objectLocation;
        }
        void set_location(std::string newLoc)
        {
            objectLocation = newLoc;
        }
};

// The master list of all objects in the game; add objects to this vector after creation.
std::vector<game_object> mainObjects = {};

// Example of an empty game_object used for comparison
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

// This function takes in a reference to a game_object 
// and attempts to erase it from the mainObjects vector.
void remove_object(game_object &objToRemove)
{
    std::vector<game_object>::iterator iter = std::find_if(mainObjects.begin(), mainObjects.end(), objToRemove);

    if (iter != mainObjects.end()) 
    {
        mainObjects.erase(iter);
    }
}

// This function initializes all game objects at the start of the program's runtime.
void initialize_game_objects() 
{
    // Check if game has already started; if mainObjects is not empty then
    // clear mainObjects & re-add objects in their default state to restart game.
    if (!mainObjects.empty()) {
        mainObjects.clear();
    }

    // Initializing locations (objects of type "location")
    mainObjects.insert(mainObjects.begin(), game_object("location", "game start", "It's shabby, and a place "
    "of calm tension.", {}));
    mainObjects.insert(mainObjects.end(), game_object("location", "abandoned town", "The town seems "
    "abandoned. All you can see is dilapidated buildings.", {}));
    mainObjects.insert(mainObjects.end(), game_object("location", "oasis", "You look at what seems "
    "to be a beautiful oasis.", {}));
    mainObjects.insert(mainObjects.end(), game_object("location", "outside palace", "", {})); // description undecided
    mainObjects.insert(mainObjects.end(), game_object("location", "inside palace", "", {})); // description undecided
    mainObjects.insert(mainObjects.end(), game_object("location", "gate", "The gate is wooden, "
    "Egyptian-styled, and at least 15 feet tall.", {}));
    mainObjects.insert(mainObjects.end(), game_object("location", "city square", "Entering the heart "
    "of the city, shops are spread out before you, and you can see King Akhem's palace in the distance.", {}));
    mainObjects.insert(mainObjects.end(), game_object("location", "general store", "Right ahead of you "
    "appears to be a huge tent - you see a variety of clothes, hats, shoes, and toys within.", {}));
    mainObjects.insert(mainObjects.end(), game_object("location", "coffee shop", "The shop itself seems "
    "very old at first glance, with cracked walls and faded windows. Doesn't seem to bother the locals, though "
    "- you see many happy faces inside.", {}));
    mainObjects.insert(mainObjects.end(), game_object("location", "Sarabi's Egyptian Cuisine", "The "
    "outside of the building seems pretty plain, but another glance reveals quite the beautiful entryway.", {}));

    // Initializing items (objects of type "item")
    mainObjects.insert(mainObjects.end(), game_object("item", "sword", "You look upon an ordinary sword; "
    "it's not pretty, but it gets the job done.", {}, "game start"));
    mainObjects.insert(mainObjects.end(), game_object("item", "shield", "You look upon an ordinary shield; "
    "it may be made out of wood, but it'll protect you well enough. Maybe.", {}, "game start"));
    mainObjects.insert(mainObjects.end(), game_object("item", "chestkey", "This is, almost certainly, "
    "the key to a chest. It's quite hard to miss the engraving on the key that says \"Chest Key\".", {}, "")); // location undecided
    mainObjects.insert(mainObjects.end(), game_object("item", "chest", "You look at the chest and see "
    "that it is... a chest. What, did you expect a mimic or something?", {}, "")); // location undecided
    mainObjects.insert(mainObjects.end(), game_object("item", "note", "The note reads: 'January 18th. "
    "Seen some bandits around here recently. Trying to stay out of sight. I know it's part of "
    "my job to keep this chest protected, but I won't make it out here much longer.'", {}, "outside palace")); 
    mainObjects.insert(mainObjects.end(), game_object("item", "drink", "Well, it wouldn't be a tavern without any "
    "drinks. It looks like a shot of whisky - why not take a drink?", {}, "tavern"));

    // Initializing characters (objects of type "character")
    mainObjects.insert(mainObjects.end(), game_object("character", "bandit", "He looks ragged, with "
    "torn clothes and a dented sword.", {"is_alive"}, "tavern"));
    mainObjects.insert(mainObjects.end(), game_object("character", "old lady", "You see an old lady "
    "who seems to be having trouble with something, although you can't quite make out what it is "
    "she's having trouble with. Maybe you should try talking to her?", {"is_alive"}, "abandoned town"));
    mainObjects.insert(mainObjects.end(), game_object("character", "barkeep", "The barkeep is keeping "
    "themselves occupied by wiping down glasses.", {"is_alive"}, "tavern"));
}

#endif