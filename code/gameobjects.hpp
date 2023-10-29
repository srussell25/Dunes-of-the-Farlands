#ifndef GAMEOBJECTS_HPP
#define GAMEOBJECTS_HPP

// Finds the iterator for an object in a vector of the same type.
template <typename A, typename B>
std::vector<A>::iterator find_iter(std::vector<A> &vecToCheck, B &objToFind)
{
    return std::find(vecToCheck.begin(), vecToCheck.end(), objToFind);
}

// Searches for an object in the vector argument, then attempts
// to return the object if it exists in the vector. Returns the
// default constructor of the type within the vector if unsuccessful.
template <typename A, typename B> 
A get_object(std::vector<A> &vecToCheck, B &objToGet)
{
    typename std::vector<A>::iterator vecIter = find_iter(vecToCheck, objToGet);
    if (vecIter != vecToCheck.end())
    {
        return *vecIter;
    }
    else
    {
        return A();
    }
}

// Attempts to add an object to a vector; fails if the item is equivalent
// to the default constructor of the argument type.
template <typename A>
bool add_object(std::vector<A> &vecToCheck, A &objToAdd)
{
    if (objToAdd != A())
    {
        vecToCheck.insert(vecToCheck.end(), objToAdd);
        return true;
    }
    else
    {
        return false;
    }
}

// Searches for an object in the vector argument, then attempts to remove
// the object if it exists in the vector. Returns true if successful,
// otherwise returns false.
template <typename A, typename B>
bool remove_object(std::vector<A> &vecToCheck, B &objToRemove)
{
    typename std::vector<A>::iterator vecIter = find_iter(vecToCheck, objToRemove);
    if (vecIter != vecToCheck.end()) 
    {
        vecToCheck.erase(vecIter);
        return true;
    }
    {
        return false;
    }
}

// This class contains information about one of the game's objects,
// including its type, name, description, location, and set flags.
class game_object
{
    private:
        std::string objectType;
        std::string objectName;
        std::string objectDescription;
        std::string objectLocation;
        std::vector<std::string> objectFlags;

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
        // Class methods
        std::string get_object_type()
        {
            return objectType;
        }
        std::string get_object_name()
        {
            return objectName;
        }
        void set_object_name(std::string newName)
        {
            objectName = newName;
        }
        std::string get_object_desc()
        {
            return objectDescription;
        }
        void set_object_desc(std::string newDesc)
        {
            objectDescription = newDesc;
        }
        std::string get_object_flag(std::string flagToGet) 
        {
            return get_object(objectFlags, flagToGet);
        }
        void add_object_flag(std::string flagToAdd)
        {
            if (!flagToAdd.empty())
            {
                objectFlags.insert(objectFlags.begin(), flagToAdd);
            }
        }
        void remove_object_flag(std::string flagToRemove)
        {
            remove_object(objectFlags, flagToRemove);
        }
        std::string get_object_loc() 
        {
            return objectLocation;
        }
        void set_object_loc(std::string newLoc)
        {
            objectLocation = newLoc;
        }
};

// Specifying mainObjects and emptyObject inside of a namespace to keep them out of the global scope
namespace specificvars
{
    // The master list of all objects in the game; add objects to this vector after creation.
    std::vector<game_object> mainObjects = {};

    // Example of an empty game_object used for comparison.
    game_object emptyObject = game_object();
};

// This function takes in a string meant to represent the name of a game_object, and then 
// searches within the vector mainObjects to see if that game_object exists. If it exists, 
// the function returns the game_object by reference; otherwise, it returns emptyObject by reference.
game_object& find_object(std::string objName)
{
    using namespace specificvars;

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

// This function is intended to initialize all game objects at the start of the program's runtime.
void initialize_game_objects() 
{
    using namespace specificvars;

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
    mainObjects.insert(mainObjects.end(), game_object("location", "tavern", "It's a tavern; "
    "I wonder if there's anyone inside?", {}));
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
    // Initial player inventory items
    mainObjects.insert(mainObjects.end(), game_object("item", "sword", "You look upon an ordinary sword; "
    "it's not pretty, but it gets the job done.", {}, "playerinventory"));
    mainObjects.insert(mainObjects.end(), game_object("item", "shield", "You look upon an ordinary shield; "
    "it may be made out of wood, but it'll protect you well enough. Maybe.", {}, "playerinventory"));
    // Other game items
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