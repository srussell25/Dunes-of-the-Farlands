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

// Attempts to assign multiple key/value pairs from a vector
// of type pair to an unordered map that is passed by reference.
template <typename A, typename B>
void assign_map_values(std::unordered_map<A, B> &map, std::vector<std::pair<A, B>> pairs)
{
    for (std::pair<A, B> p : pairs)
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
        std::set<std::string> object_synonyms;

    public:
        game_object() {} // Public default constructor
        game_object(std::string obj_type, std::string obj_name, std::string obj_desc) // Type, name & desc
        {
            object_type = obj_type;
            object_name = obj_name;
            object_desc = obj_desc;
        }
        game_object(std::string obj_type, std::string obj_name, std::string obj_desc,
            std::string obj_loc) // Above + location
        {
            object_type = obj_type;
            object_name = obj_name;
            object_desc = obj_desc;
            object_location = obj_loc;
        }
        game_object(std::string obj_type, std::string obj_name, std::string obj_desc,
            std::vector<std::pair<std::string, bool>> obj_flags) // Above w/ flags instead of loc
        {
            object_type = obj_type;
            object_name = obj_name;
            object_desc = obj_desc;
            assign_map_values(object_flags, obj_flags);
        }
        game_object(std::string obj_type, std::string obj_name, std::string obj_desc, 
            std::string obj_loc, std::vector<std::pair<std::string, bool>> obj_flags) // Above + loc
        {
            object_type = obj_type;
            object_name = obj_name;
            object_desc = obj_desc;
            object_location = obj_loc;
            assign_map_values(object_flags, obj_flags);
        }

        game_object(std::string obj_type, std::string obj_name, std::string obj_desc, std::set<std::string> synonyms) // Type, name, desc, & synonyms
        {
            object_type = obj_type;
            object_name = obj_name;
            object_desc = obj_desc;
            object_synonyms = synonyms;
        }

        friend bool operator==(game_object const& x, game_object const& y)
        {
            return x.object_name == y.object_name;
        }
        friend bool operator!=(game_object const& x, game_object const& y)
        {
            return !(x.object_name == y.object_name);
        }
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
        // If flag exists & is set, returns true; otherwise, returns false.
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

    // Location sets
    std::set<std::string> location_set_one = {"abandoned town", "farlands", "game start", "oasis"}; // at start
    std::set<std::string> location_set_two = {"tavern"}; // at abandoned town
    std::set<std::string> location_set_three = {"town square"}; // at entrance to farlands (synonym for farlands)
    std::set<std::string> location_set_four = {"coffee shop", "general store", "palace", "sarabi's egyptian cuisine"}; // at town square
    std::set<std::string> location_set_five = {"inside palace", "side gate"}; // at gate (synonym for palace)
    std::set<std::string> location_set_six = {"king's throne room", "potion room", "spyro's lair"}; // at inside palace
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
    if (!main_objects.empty()) // Clear main_objects & re-add upon calling this function more than once
    {
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

    main_objects.insert(main_objects.end(), game_object("location", "palace", "The Kingdom is very "
    "large and heavily guarded. You can see King Akhem's guards walking around the entire fortress. "
    "with swords, javelins, and shields. There is a gate on the side that is surprisingly guarded by only "
    "one person."));

    main_objects.insert(main_objects.end(), game_object("location", "side gate", "You walk "
    "up to the side gate, and are greeted by the sight of a lone guard."));

    main_objects.insert(main_objects.end(), game_object("location", "farlands", "You are currently "
    "outside the walls of the Farlands."));

    main_objects.insert(main_objects.end(), game_object("location", "gate", "The gate is a light brown, "
    "probably from the hot sun beaming on it all day. It's a ginormous set of doors, about 15 feet. "
    "Its handles are made of sharp gold, imported. The symbols on the door resemble "
    "Egyptian writing, indicating that this is an Egyptian town."));
    
    main_objects.insert(main_objects.end(), game_object("location", "city square", "You are in the City Square "
    "of the Farlands. You see a shop called Coco's Coffee filled that has friendly-looking locals, a Nunu's "
    "General Store, Sarabi's Egyptian Cuisine, and farther down you see King Akhem's Palace"));

    main_objects.insert(main_objects.end(), game_object("location", "general store", "Right ahead of you "
    "appears to be a huge tent - you see a variety of clothes, hats, shoes, and toys within."));

    main_objects.insert(main_objects.end(), game_object("location", "coffee shop", "The shop itself seems "
    "very old at first glance, with cracked walls and faded windows. Doesn't seem to bother the locals, though "
    "- you see many happy faces inside."));

    main_objects.insert(main_objects.end(), game_object("location", "sarabi's egyptian cuisine", "The "
    "outside of the building seems pretty plain, but another glance reveals quite the beautiful entryway."));

    main_objects.insert(main_objects.end(), game_object("location", "potion room", "This potion room is rather "
    "windowless and small. The room is lined with shelves that have many colorful potions on them. "
    "You see a countertop that has a dusty old book on it. You notice there is a note on the book "
    "that says, 'Apprentices should not take the book outside of the Potion Room.' Your inventory "
    "can only hold one potion, so choose wisely."));

    main_objects.insert(main_objects.end(), game_object("location", "spyro's lair", "Spyro's lair is a dimly"
    "lit room, with a few windows higher up in the wall toward the ceiling. There is a candle-lit chandlier"
    "in the middle of the room, and the room seems to be made out of stone blocks."));

    main_objects.insert(main_objects.end(), game_object("location", "the king's throne", "The King's Throne room"
    "is exactly like Spyro's liar. However, he has a bed AND a rug. He is a simple man. There have been reports"
    "of the King firing multiple interior designers in the past."));

    // Initializing items (objects of type "item") starting w/ items for the player inventory
    main_objects.insert(main_objects.end(), game_object("item", "sword", "You look upon an ordinary sword; "
    "it's not pretty, but it gets the job done.", "playerinventory"));

    main_objects.insert(main_objects.end(), game_object("item", "shield", "You look upon an ordinary shield; "
    "it may be made out of wood, but it'll protect you well enough. Maybe.", "playerinventory"));
    
    main_objects.insert(main_objects.end(), game_object("item", "chest key", "This is, almost certainly, "
    "the key to a chest. It's quite hard to miss the engraving on the key that says \"Chest Key\".", "")); // location undecided

    main_objects.insert(main_objects.end(), game_object("item", "chest", "You look at the chest and see "
    "that it is... a chest. What, did you expect a mimic or something?", "")); // location undecided

    main_objects.insert(main_objects.end(), game_object("item", "paper", "Map tips for new soldiers within King Akhem's Palace: "
    "Go to the underground lair that King Akhem has. This has all of his riches and treasures, as well as any potions or weapons "
    "that we could use for war. To get to his main room, you must talk to Spyro, a Sphynx who doesn't take kindly to strangers. "
    "Beware of him, and if he attacks you, you will need a confusion potion to get past him, or you can use a strength potion to "
    "take him head on. And newbies, the potion room might be inside the palace, but don't get ahead of yourselves.", "outside palace")); 

	main_objects.insert(main_objects.end(), game_object("item", "drink", "Well, it wouldn't be a tavern without any "
    "drinks. It looks like a shot of whisky - why not take a drink?", "tavern"));

    main_objects.insert(main_objects.end(), game_object("item", "confusion potion", "When this potion is thrown at someone, "
    "they will enter a state of amnesia and forget the reason why they are fighting you. This will give you the chance to "
    "sneak past them to do something else. without any consequences... probably.", "potion room"));

    main_objects.insert(main_objects.end(), game_object("item", "fire potion", "When the liquid is exposed to air, "
    "the liquid turns into flying fire. This is a prototype, so we must be careful testing it.", "potion room"));

    main_objects.insert(main_objects.end(), game_object("item", "hunger potion", "When this is thrown at someone or "
    "consumed by mouth, the victim will become famished.", "potion room"));

    main_objects.insert(main_objects.end(), game_object("item", "strength potion", "When this potion is splashed "
    "on the skin or consumed by mouth, your muscles will expand, and you will feel like a mighty "
    "warrior..", "potion room"));

    main_objects.insert(main_objects.end(), game_object("item", "coffee", "It's a hot cup of coffee, brewed at "
    "Coco's Coffee House, using the finest beans that were imported from a rich land far away. "
    "It'd be nice to get a drink I bet.", "coffee shop"));

    main_objects.insert(main_objects.end(), game_object("item", "armor of torren", "From a moments glance, "
    "the armor looks amazing. It's a metal set with golden-plated designs throughout. However, after closer "
    "inspection, you can see that this armor is not worth much. It's rusted on the inside, the helmet has a "
    "few loose screws, and the leg pieces squeak when you walk.", "general store"));

    main_objects.insert(main_objects.end(), game_object("item", "book", "This is a dusty old book used for "
    "potion crafting. Hey, don't forget that there's a sign that says not to pick up the book!", 
    "potion room"));

    // Initializing characters (objects of type "character")
    main_objects.insert(main_objects.end(), game_object("character", "bandit", "He looks ragged, with "
    "torn clothes and a dented sword.", "tavern", {{"is_alive", true}, {"known_evil", true}}));

    main_objects.insert(main_objects.end(), game_object("character", "old lady", "You see an old lady "
    "who seems to be having trouble with something, although you can't quite make out what it is "
	"she's having trouble with. Maybe you should try talking to her? But be cautious, she "
    "may not be as hamrless as you think.", "abandoned town", {{"is_alive", true}, {"known_evil", false}}));

	main_objects.insert(main_objects.end(), game_object("character", "barkeep", "The barkeep is keeping "
    "themselves occupied by wiping down glasses.", "tavern", {{"is_alive", true}}));

    main_objects.insert(main_objects.end(), game_object("character", "guards", "These are some strong looking "
    "guards; it's probably for the best not to fight them.", "gate", {{"is_alive", true}}));

    main_objects.insert(main_objects.end(), game_object("character", "guard", "this soldier is currently by himself. "
    "He is guarding a side entrance to the palace. Maybe this could a way in?", "palace", {{"is_alive", true}}));

    main_objects.insert(main_objects.end(), game_object("character", "spyro", "He is a large black feline, "
    "like... really large. He has a metal plate around his torso, as well as a golden helmet around his head. "
    "His eyes are beat red, and his claws are razor sharp. Upon looking at you, he snarls and sticks out his sharp"
    "fangs. His eyes glow red and his muscles begin to flare up.", "spyro's lair", {{"is_alive", true}}));

    main_objects.insert(main_objects.end(), game_object("character", "king akhem", "You lunge at King Akhem in an "
    "attempt to grab him by the arm. He flings you off like a piece of spaghetti, and the impact of hitting the "
    "ground knocks you out straight away. Once you wake up, you realize you've been taken out of the palace.", 
    "the king's throne", {{"is_alive", true}}));

    main_objects.insert(main_objects.end(), game_object("character", "shopkeeper", "The shopkeeper appears to be "
    "elderly. She is wrinkly in the face, is missing some teeth, and has a limp. However, she appears to be "
    "friendly, even to outsiders like you.", "general store", {{"is_alive", true}}));

    main_objects.insert(main_objects.end(), game_object("character", "locals","\nYou "
    "might just want to move along.","", {{"is_alive", true}})); // location left empty on purpose
}

/*
Things that we still have to work on:
- Description for guards
- Cases for using the wrong potion against Spyro
- Take armor for the take function in object actions
- Dialogue before the boss and mini boss battles 

- ask connor about Spyro's lair part 2 implementation
*/

#endif