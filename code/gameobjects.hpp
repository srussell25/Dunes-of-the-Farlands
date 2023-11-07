#ifndef GAMEOBJECTS_HPP
#define GAMEOBJECTS_HPP

// Finds the iterator for an object in a vector of the same type.
template <typename A, typename B>
std::vector<A>::iterator find_iter(std::vector<A> &vec_to_check, B &objToFind)
{
    return std::find(vec_to_check.begin(), vec_to_check.end(), objToFind);
}

// Searches for an object in the vector argument, then attempts
// to return the object if it exists in the vector. Returns the
// default constructor of the type within the vector if unsuccessful.
template <typename A, typename B> 
A get_object(std::vector<A> &vec_to_check, B &obj_to_get)
{
    typename std::vector<A>::iterator vec_iter = find_iter(vec_to_check, obj_to_get);
    if (vec_iter != vec_to_check.end())
    {
        return *vec_iter;
    }
    else
    {
        return A();
    }
}

// Attempts to add an object to a vector; fails if the item is equivalent
// to the default constructor of the argument type.
template <typename A>
bool add_object(std::vector<A> &vec_to_check, A &obj_to_add)
{
    if (obj_to_add != A())
    {
        vec_to_check.insert(vec_to_check.end(), obj_to_add);
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
bool remove_object(std::vector<A> &vec_to_check, B &obj_to_rem)
{
    typename std::vector<A>::iterator vec_iter = find_iter(vec_to_check, obj_to_rem);
    if (vec_iter != vec_to_check.end()) 
    {
        vec_to_check.erase(vec_iter);
        return true;
    }
    {
        return false;
    }
}

void assign_map_values(std::unordered_map<std::string, bool> &map, std::vector<std::pair<std::string, bool>> pairs)
{
    for (std::pair<std::string, bool> p : pairs)
    {
        map.insert_or_assign(p.first, p.second);
    }
}

// This class contains information about one of the game's objects,
// including its type, name, description, location, and set flags.
class game_object
{
    private:
        std::string object_type;
        std::string object_name;
        std::string object_desc;
        std::string object_location;
        std::unordered_map<std::string, bool> object_flags;

    public:
        // Public default constructor
        game_object() {}
        // Public constructor which sets a game_object's type, name, and description.
        game_object(std::string obj_type, std::string obj_name, std::string obj_desc)
        {
            object_type = obj_type;
            object_name = obj_name;
            object_desc = obj_desc;
        }
        // Public constructor which sets a game_object's type, name, description, and location.
        game_object(std::string obj_type, std::string obj_name, std::string obj_desc, 
            std::string obj_loc)
        {
            object_type = obj_type;
            object_name = obj_name;
            object_desc = obj_desc;
            object_location = obj_loc;
        }
        // Public constructor which sets a game_object's type, name, description, and flags
        game_object(std::string obj_type, std::string obj_name, std::string obj_desc, 
            std::vector<std::pair<std::string, bool>> obj_flags)
        {
            object_type = obj_type;
            object_name = obj_name;
            object_desc = obj_desc;
            assign_map_values(object_flags, obj_flags);
        }
        // Public constructor which sets a game_object's type, name, description, flags and location.
        game_object(std::string obj_type, std::string obj_name, std::string obj_desc, 
            std::string obj_loc, std::vector<std::pair<std::string, bool>> obj_flags)
        {
            object_type = obj_type;
            object_name = obj_name;
            object_desc = obj_desc;
            object_location = obj_loc;
            assign_map_values(object_flags, obj_flags);
        }
        // Comparison operators
        friend bool operator==(game_object const& x, game_object const& y)
        {
            return x.object_name == y.object_name;
        }
        friend bool operator!=(game_object const& x, game_object const& y)
        {
            return !(x.object_name == y.object_name);
        }
        // Class methods
        std::string get_object_type()
        {
            return object_type;
        }
        std::string get_object_name()
        {
            return object_name;
        }
        void set_object_name(std::string name)
        {
            object_name = name;
        }
        std::string get_object_desc()
        {
            return object_desc;
        }
        void set_object_desc(std::string desc)
        {
            object_desc = desc;
        }
        // If flag exists, returns true; otherwise, returns false.
        bool get_object_flag(std::string flag)
        {
            if (object_flags.count(flag) != 0)
            {
                return object_flags.at(flag);
            }
            else
            {
                return false;
            }
        }
        // Either adds a new flag with the key `name` and value `val`,
        // or sets the value of the existing key `name` to `val`.
        void set_object_flag(std::string name, bool val)
        {
            object_flags.insert_or_assign(name, val);
        }
        void remove_object_flag(std::string flag)
        {
            object_flags.erase(flag);
        }
        std::string get_object_loc() 
        {
            return object_location;
        }
        void set_object_loc(std::string loc)
        {
            object_location = loc;
        }
};

// Specifying main_objects and empty_object inside of a namespace to keep them out of the global scope
namespace specificvars
{
    // The master list of all objects in the game; add objects to this vector after creation.
    std::vector<game_object> main_objects = {};

    // Example of an empty game_object used for comparison.
    game_object empty_object = game_object();
};

// This function takes in a string meant to represent the name of a game_object, and then 
// searches within the vector main_objects to see if that game_object exists. If it exists, 
// the function returns the game_object by reference; otherwise, it returns empty_object by reference.
game_object& find_object(std::string name)
{
    using namespace specificvars;

    std::vector<game_object>::iterator iter = std::find_if(main_objects.begin(), main_objects.end(), 
    [name](game_object obj){ return obj.get_object_name() == name; });

    if (iter != main_objects.end()) 
    {
        return *iter;
    }
    else
    {
        return empty_object;
    }
}

// This function is intended to initialize all game objects at the start of the program's runtime.
void initialize_game_objects() 
{
    using namespace specificvars;

    // Check if game has already started; if main_objects is not empty then
    // clear main_objects & re-add objects in their default state to restart game.
    if (!main_objects.empty()) {
        main_objects.clear();
    }

    // Initializing locations (objects of type "location")
    main_objects.insert(main_objects.begin(), game_object("location", "game start", "It's shabby, and a place "
    "of calm tension."));
    main_objects.insert(main_objects.end(), game_object("location", "abandoned town", "The town seems "
    "abandoned. All you can see is dilapidated buildings."));
    main_objects.insert(main_objects.end(), game_object("location", "oasis", "You look at what seems "
    "to be a beautiful oasis."));
    main_objects.insert(main_objects.end(), game_object("location", "tavern", "It's a tavern; "
    "I wonder if there's anyone inside?"));
    main_objects.insert(main_objects.end(), game_object("location", "palace", "")); // description undecided
    main_objects.insert(main_objects.end(), game_object("location", "inside palace", "")); // description undecided
    main_objects.insert(main_objects.end(), game_object("location", "farlands", "you are currently outside the walls of the farland."));
    main_objects.insert(main_objects.end(), game_object("location", "city square", "Entering the heart "
    "of the city, shops are spread out before you, and you can see King Akhem's palace in the distance."));
    main_objects.insert(main_objects.end(), game_object("location", "general store", "Right ahead of you "
    "appears to be a huge tent - you see a variety of clothes, hats, shoes, and toys within."));
    main_objects.insert(main_objects.end(), game_object("location", "coffee shop", "The shop itself seems "
    "very old at first glance, with cracked walls and faded windows. Doesn't seem to bother the locals, though "
    "- you see many happy faces inside."));
    main_objects.insert(main_objects.end(), game_object("location", "Sarabi's Egyptian Cuisine", "The "
    "outside of the building seems pretty plain, but another glance reveals quite the beautiful entryway."));
    main_objects.insert(main_objects.end(), game_object("location", "gate", "The gate is a light brown, probably from the hot sun beaming on it all day. "
    "It’s a ginormous set of doors, about 15 feet. Its handles are made of sharp gold, imported. The symbols on the door resemble "
    "Egyptian writing, indicating that this is an Egyptian town."));



    // Initializing items (objects of type "item")
    // Initial player inventory items
    main_objects.insert(main_objects.end(), game_object("item", "sword", "You look upon an ordinary sword; "
    "it's not pretty, but it gets the job done.", "playerinventory"));
    main_objects.insert(main_objects.end(), game_object("item", "shield", "You look upon an ordinary shield; "
    "it may be made out of wood, but it'll protect you well enough. Maybe.", "playerinventory"));
    // Other game items
    main_objects.insert(main_objects.end(), game_object("item", "chestkey", "This is, almost certainly, "
    "the key to a chest. It's quite hard to miss the engraving on the key that says \"Chest Key\".", "")); // location undecided
    main_objects.insert(main_objects.end(), game_object("item", "chest", "You look at the chest and see "
    "that it is... a chest. What, did you expect a mimic or something?", "")); // location undecided
    main_objects.insert(main_objects.end(), game_object("item", "note", "The note reads: 'January 18th. "
    "Seen some bandits around here recently. Trying to stay out of sight. I know it's part of "
    "my job to keep this chest protected, but I won't make it out here much longer.'", "outside palace")); 
    main_objects.insert(main_objects.end(), game_object("item", "drink", "Well, it wouldn't be a tavern without any "
    "drinks. It looks like a shot of whisky - why not take a drink?", "tavern"));


    // Initializing characters (objects of type "character")
    main_objects.insert(main_objects.end(), game_object("character", "bandit", "He looks ragged, with "
    "torn clothes and a dented sword.", "tavern", {{"is_alive", true}, {"known_evil", true}}));
    main_objects.insert(main_objects.end(), game_object("character", "old lady", "You see an old lady "
    "who seems to be having trouble with something, although you can't quite make out what it is "
    "she's having trouble with. Maybe you should try talking to her?", "abandoned town", 
    {{"is_alive", true}, {"known_evil", false}}));
    main_objects.insert(main_objects.end(), game_object("character", "barkeep", "The barkeep is keeping "
    "themselves occupied by wiping down glasses.", "tavern", {{"is_alive", true}}));
    main_objects.insert(main_objects.end(), game_object("character", "guards", "these are some strong looking"
    "guards best not to fight them", "gate", {{"is_alive", true}}));
    main_objects.insert(main_objects.end(), game_object("character", "guard", "this soldier is currently by himself."
    "he is guarding a side entrance to the palace. maybe this can be our way in?", "palace", {{"is_alive", true}}));
}

#endif