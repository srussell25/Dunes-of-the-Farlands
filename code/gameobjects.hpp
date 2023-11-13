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
        game_object(std::string obj_type, std::string obj_name, std::string obj_desc, 
            std::optional<std::string> obj_loc = std::nullopt, 
            std::optional<std::vector<std::pair<std::string, bool>>> obj_flags = std::nullopt, 
            std::optional<std::set<std::string>> synonyms = std::nullopt)
        {
            object_type = obj_type;
            object_name = obj_name;
            object_desc = obj_desc;
            // Using std::optional so we don't have a lot of constructors
            if (obj_loc.has_value())
            {
                object_location = obj_loc.value();
            }
            if (obj_flags.has_value())
            {
                assign_map_values(object_flags, obj_flags.value());
            }
            if (synonyms.has_value())
            {
                object_synonyms = synonyms.value();
            }
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
        bool get_object_flag(std::string flag) // If flag exists & is set, returns true.
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
        void set_object_flag(std::string name, bool val) // Adds or sets a value of 'val' to the flag 'name'
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
        bool check_object_synonyms() // If synonyms exist, returns true.
        {
            return !object_synonyms.empty();
        }
        std::set<std::string> get_object_synonyms() 
        {
            return object_synonyms;
        }
};

// Specifying main_objects and empty_object inside of a namespace to keep them out of the global scope
namespace specificvars
{
    std::vector<game_object> main_objects = {}; // The main vector of all objects in the game (other than the player)

    game_object empty_object = game_object(); // Empty game_object used for comparison by reference

    std::set<std::string> location_set_one = {"abandoned town", "game start", "oasis"}; // at start
    std::set<std::string> location_set_two = {"abandoned town", "farlands", "tavern"}; // at abandoned town
    std::set<std::string> location_set_three = {"city square", "farlands"}; // at farlands
    std::set<std::string> location_set_four = {"city square", "coffee shop", "general store", "palace", "sarabi's egyptian cuisine"}; // at city square
    std::set<std::string> location_set_five = {"inside palace", "palace", "side gate"}; // at palace
    std::set<std::string> location_set_six = {"inside palace", "potion room", "spyro's lair"}; // at inside palace
    std::set<std::string> location_set_seven = {"king's throne", "spyro's lair"}; // at spyro's lair
};

// This function takes in a string meant to represent the name of a game_object, and then 
// searches within the vector main_objects to see if that game_object exists. If it exists, 
// the function returns the game_object by reference; otherwise, it returns empty_object by reference.
game_object& find_object(std::string name)
{
    using namespace specificvars;

    std::vector<game_object>::iterator iter = std::find_if(main_objects.begin(), main_objects.end(), 
    [name](game_object obj) 
    { 
        if (obj.check_object_synonyms())
        {
            return (obj.get_object_name() == name || obj.get_object_synonyms().contains(name));
        }
        else
        {
            return obj.get_object_name() == name;
        }
    });
    
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

    main_objects.insert(main_objects.end(), game_object("location", "around", "")); // desc left empty on purpose

    main_objects.insert(main_objects.end(), game_object("location", "abandoned town", "The town seems "
    "abandoned. All you can see is dilapidated buildings.", "", {}, (std::set<std::string>) {"nekhem", "north", "town"}));

    main_objects.insert(main_objects.end(), game_object("location", "oasis", "You look at what seems "
    "to be a beautiful oasis."));

    main_objects.insert(main_objects.end(), game_object("location", "tavern", "It's a tavern; "
    "I wonder if there's anyone inside?", "", {}, (std::set<std::string>) {"bar", "saloon", "sand dune saloon"}));

    main_objects.insert(main_objects.end(), game_object("location", "palace", "The King's palace is essentially a "
    "fortress. It's massive, gated, and has King Akhem's guards patrolling around the perimeter armed to the "
    "teeth with swords, javelins, and shields. Yet, as you're looking around, you do spot what appears to "
    "be a side gate guarded by only one person. Surely going over there wouldn't work... right?", "", {},
    (std::set<std::string>) {"fortress", "king akhem palace", "king akhem's palace"}));

    main_objects.insert(main_objects.end(), game_object("location", "side gate", "The side entrance to the "
    "inside of the palace seems guarded by only one person.", "", {}, (std::set<std::string>) {"gate"}));

    main_objects.insert(main_objects.end(), game_object("location", "inside palace", "The inside of the palace "
    "is not heavely guarded like the outside. Actually, it's mostly dark inside, except for two doors lit by torches. "
    "It's... almost scary how little detail there is on the inside of the palace compared to the outside.", "", {}, 
    (std::set<std::string>) {"inside of the palace", "inside the palace"})); // TODO: Add description

    main_objects.insert(main_objects.end(), game_object("location", "farlands", "The entrance to "
    "the Farlands consists of a gate that is a light brown, likely from the hot sun beaming on it "
    "all day. The doors of the gate are ginormous, about 15 feet tall. Said door handles are also "
    "made of gold, clearly imported. There are some symbols on the door that resemble Egyptian writing, "
    "indicating that this is an Egyptian city.", "", {}, (std::set<std::string>) {"east"}));
    
    main_objects.insert(main_objects.end(), game_object("location", "city square", "You are in the City Square "
    "of the Farlands. You see a shop called Coco's Coffee filled that has friendly-looking locals, a Nunu's "
    "General Store, Sarabi's Egyptian Cuisine, and farther down you see King Akhem's Palace", "", {}, 
    (std::set<std::string>) {"city"}));

    main_objects.insert(main_objects.end(), game_object("location", "general store", "Right ahead of you "
    "appears to be a huge tent - you see a variety of clothes, hats, shoes, and toys within.", "", {}, 
    (std::set<std::string>) {"nunu's general store", "nunu's store", "nunus general store", "nunus store", "tent"}));

    main_objects.insert(main_objects.end(), game_object("location", "coffee shop", "The shop itself seems "
    "very old at first glance, with cracked walls and faded windows. Doesn't seem to bother the locals, though "
    "- you see many happy faces inside.", "", {}, (std::set<std::string>) {"coco's coffee", "cocos coffee"}));

    main_objects.insert(main_objects.end(), game_object("location", "sarabi's egyptian cuisine", "The "
    "outside of the building seems pretty plain, but another glance reveals quite the beautiful entryway.", 
    "", {}, (std::set<std::string>) {"cuisine", "egytian cuisine", "restaurant", "sarabi's store", 
    "sarabis egytian cuisine", "sarabis store"}));

    main_objects.insert(main_objects.end(), game_object("location", "potion room", "This potion room is rather "
    "windowless and small. The room is lined with shelves that have many colorful potions on them. "
    "You see a countertop that has a dusty old book on it. You notice there is a note on the book "
    "that says, 'Apprentices should not take the book outside of the Potion Room.' Your inventory "
    "can only hold one potion, so choose wisely.", "", {}, (std::set<std::string>) {"door one"}));

    main_objects.insert(main_objects.end(), game_object("location", "spyro's lair", "Spyro's lair is a dimly "
    "lit room, with a few windows higher up in the wall toward the ceiling. There is a candle-lit chandlier "
    "in the middle of the room, and the room seems to be made out of stone blocks.", "", {},
    (std::set<std::string>) {"door two", "lair", "sphynx lair", "sphynx's lair", "spyros lair"}));

    main_objects.insert(main_objects.end(), game_object("location", "king's throne", "The King's Throne room "
    "is exactly like Spyro's liar. However, he has a bed AND a rug. He is a simple man. There have been reports "
    "of the King firing multiple interior designers in the past.", "", {}, (std::set<std::string>) {"king's room",
    "king's throne room", "kings room", "kings throne room", "kings throne", "ominous space", "throne room", "throne"}));

    // Initializing items (objects of type "item") starting w/ items for the player inventory
    main_objects.insert(main_objects.end(), game_object("item", "sword", "You look upon an ordinary sword; "
    "it's not pretty, but it gets the job done.", "playerinventory"));

    main_objects.insert(main_objects.end(), game_object("item", "shield", "You look upon an ordinary shield; "
    "it may be made out of wood, but it'll protect you well enough. Maybe.", "playerinventory"));

    main_objects.insert(main_objects.end(), game_object("item", "paper", "Map tips for new soldiers within King Akhem's Palace: "
    "Go to the underground lair that King Akhem has. This has all of his riches and treasures, as well as any potions or weapons "
    "that we could use for war. To get to his main room, you must talk to Spyro, a Sphynx who doesn't take kindly to strangers. "
    "Beware of him, and if he attacks you, you will need a confusion potion to get past him, or you can use a strength potion to "
    "take him head on. And newbies, the potion room might be inside the palace, but don't get ahead of yourselves.", "side gate")); 

	main_objects.insert(main_objects.end(), game_object("item", "whiskey", "Well, it wouldn't be a tavern without any "
    "drinks. It looks like a shot of whiskey - why not take a drink?", "tavern", {}, (std::set<std::string>) {"drink", "whisky"}));

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
    "few loose screws, and the leg pieces squeak when you walk.", "general store", {},
    (std::set<std::string>) {"armor", "torren armor"}));

    main_objects.insert(main_objects.end(), game_object("item", "book", "This is a dusty old book used for "
    "potion crafting. Hey, don't forget that there's a sign that says not to pick up the book!", 
    "potion room"));

    main_objects.insert(main_objects.end(), game_object("item", "clothes", "A selection of various types of "
    "clothing. Although simple, they seem quite sturdy. Well suited to life in the farlands.", "general store"));

    main_objects.insert(main_objects.end(), game_object("item", "toys", "An assortment of childrens toys of "
    "various shapes and sizes. The craftsman seems to have put a lot of care into their creation.", "general store"));

    main_objects.insert(main_objects.end(), game_object("item", "shoes", "A few pairs of shoes. Most seem "
    "to be a type of sandal, though there are a few that look more decorative than the others.", "general store"));

    // Initializing characters (objects of type "character")
    main_objects.insert(main_objects.end(), game_object("character", "bandit", "He looks ragged, with "
    "torn clothes and a dented sword.", "tavern", (std::vector<std::pair<std::string, bool>>) 
    {{"is_alive", true}, {"known_evil", true}}, {}));

    main_objects.insert(main_objects.end(), game_object("character", "old lady", "You see an old lady "
    "who seems to be having trouble with something, although you can't quite make out what it is "
	"she's having trouble with. Maybe you should try talking to her? But be cautious, she "
    "may not be as hamrless as you think.", "abandoned town", (std::vector<std::pair<std::string, bool>>)
    {{"is_alive", true}, {"known_evil", false}}, (std::set<std::string>) {"lady"}));

	main_objects.insert(main_objects.end(), game_object("character", "barkeep", "The barkeep is keeping "
    "themselves occupied by wiping down glasses.", "tavern", (std::vector<std::pair<std::string, bool>>) 
    {{"is_alive", true}}, (std::set<std::string>) {"bartender"}));

    main_objects.insert(main_objects.end(), game_object("character", "lookouts", "They might be lookouts, but "
    "they look quite strong; it might be in your best interest not to fight them.", "gate", 
    (std::vector<std::pair<std::string, bool>>) {{"is_alive", true}}, {}));

    main_objects.insert(main_objects.end(), game_object("character", "guards", "The guards have large swords "
    "that could kill an unprepared civilian with only one swing. There are a lot of guards, but you do see "
    "one guard alone next to a side gate. A perfect time to strike...", "palace", 
    (std::vector<std::pair<std::string, bool>>) {{"is_alive", true}}, {}));

    main_objects.insert(main_objects.end(), game_object("character", "guard", "This soldier is currently by himself. "
    "He's guarding a gate off to the side of the palace. Maybe this could a way inside?", "side gate", 
    (std::vector<std::pair<std::string, bool>>) {{"is_alive", true}}, {}));

    main_objects.insert(main_objects.end(), game_object("character", "spyro", "He is a large black feline, "
    "like... really large. He has a metal plate around his torso, as well as a golden helmet around his head. "
    "His eyes are beat red, and his claws are razor sharp. Upon looking at you, he snarls and sticks out his sharp"
    "fangs. His eyes glow red and his muscles begin to flare up.", "spyro's lair", 
    (std::vector<std::pair<std::string, bool>>) {{"is_alive", true}}, (std::set<std::string>) {"sphynx"}));

    main_objects.insert(main_objects.end(), game_object("character", "king akhem", "You lunge at King Akhem in an "
    "attempt to grab him by the arm. He flings you off like a piece of spaghetti, and the impact of hitting the "
    "ground knocks you out straight away. Once you wake up, you realize you've been taken out of the palace.", 
    "king's throne", (std::vector<std::pair<std::string, bool>>) {{"is_alive", true}}, (std::set<std::string>) 
    {"akhem", "king"}));

    main_objects.insert(main_objects.end(), game_object("character", "shopkeeper", "The shopkeeper appears to be "
    "elderly. She is wrinkly in the face, is missing some teeth, and has a limp. However, she appears to be "
    "friendly, even to outsiders like you.", "general store", (std::vector<std::pair<std::string, bool>>) 
    {{"is_alive", true}}, (std::set<std::string>) {"owner", "shopkeep", "store owner", "trader"}));

    main_objects.insert(main_objects.end(), game_object("character", "locals","\nYou "
    "might just want to move along.", "", (std::vector<std::pair<std::string, bool>>)
    {{"is_alive", true}}, (std::set<std::string>) {"local"})); // location left empty on purpose
}

#endif