#ifndef GAMEOBJECTS_HPP
#define GAMEOBJECTS_HPP

// This class contains information about any object within the game
class game_object
{
    private:
        std::string objectType;
        std::string objectName;
        std::string objectDescription; 
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
            return !(x == y);
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
            return *std::find(objectFlags.begin(), objectFlags.end(), flag);
        }
        void add_object_flag(std::string flag)
        {
            objectFlags.insert(objectFlags.begin(), flag);
        }
        void remove_object_flag(std::string flag)
        {
            flagIter = std::find(objectFlags.begin(), objectFlags.end(), flag);
            objectFlags.erase(flagIter);
        }
};

// The master list of all objects in the game; add objects to this vector after creation.
std::vector<game_object> mainObjects = {};

game_object gameStart;
game_object abandonedTown;
game_object oasis;
game_object tavern;
game_object bandit;
game_object oldLady;
game_object sword;
game_object shield;
game_object chestkey;
game_object chest;
game_object note;
game_object drink;
game_object barkeep;

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
    sword = game_object("item", "sword", "You look upon an ordinary sword; "
    "it's not pretty, but it gets the job done.");
    shield = game_object("item", "shield", "You look upon an ordinary shield; "
    "it may be made out of wood, but it'll protect you well enough. Maybe.");
    chestkey = game_object("item", "chestkey", "This is, almost certainly, "
    "the key to the chest. The engraving on the side says 'chest key';"
    " I'd be surprised if it was for anything else.");
    chest = game_object("item", "chest", "You look at the chest and see "
    "that it is... a chest. What, did you expect a mimic or something?");
    note = game_object("item", "note", "The note reads: 'January 18th. "
    "Seen some bandits around here recently. Trying to stay out of sight. I know it's part of"
    " my job to keep this chest protected, but I won't make it out here much longer.'");
    drink = game_object("item", "drink", "It's the drink the bartender gave you at the tavern."
    " You get the feeling it'd be nice to take a drink within the tavern.", {"at_tavern"});

    mainObjects.insert(mainObjects.end(), sword);
    mainObjects.insert(mainObjects.end(), shield);
    mainObjects.insert(mainObjects.end(), chestkey);
    mainObjects.insert(mainObjects.end(), chest);
    mainObjects.insert(mainObjects.end(), note); 
    mainObjects.insert(mainObjects.end(), drink);

    // Initializing locations (objects of type "location")
    gameStart = game_object("location", "gameStart", "It's shabby and a place of calm tension.", {"at_start"});
    abandonedTown = game_object("location", "abandonedTown", "This town seems abandoned. Everything here is old and rusty.");
    oasis = game_object("location", "oasis", "You look at what seems to be a beautiful oasis.");
    tavern = game_object("location", "tavern", "It's a tavern; I wonder if there's anyone inside?");

    mainObjects.insert(mainObjects.begin(), gameStart);
    mainObjects.insert(mainObjects.end(), abandonedTown);
    mainObjects.insert(mainObjects.end(), oasis);
    mainObjects.insert(mainObjects.end(), tavern);

    // Initializing characters (objects of type "character")
    bandit = game_object("character", "bandit", "This guy is looking rather shifty hanging out over there.", {"is_alive"});
    // NOTE: The "is_alive" string is an example of a flag being set; in this case, it's used for checking if the bandit is alive 
    //       (if the string exists, the flag is "set"; if the flag doesn't exist, it's not "set".)
    oldLady = game_object("character", "oldLady", "You see an old lady who seems to be having trouble with something,"
    " although you can't quite make out what it is she's having trouble with. Maybe you should try talking to her?");
    barkeep = game_object("character", "barkeep", "The barkeep is keeping themselves occupied by wiping down glasses.");

    mainObjects.insert(mainObjects.end(), bandit);
    mainObjects.insert(mainObjects.end(), oldLady);
    mainObjects.insert(mainObjects.end(), barkeep);
}

#endif