// Add necessary includes & imports here
#include "catch.hpp"
#include <iostream>
#include <algorithm>

class gameObject
{
    private:
    std::string objectType = "object type goes here";
    std::string objectName = "object name goes here";
    std::string objectDescription = "object descrition goes here"; 
    std::vector<std::string> objectFlags = {};
    std::vector<std::string>::iterator flagIter;

    public:
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
    void add_object_flag(auto flag)
    {
        objectFlags.insert(objectFlags.begin(), flag);
    }
    void remove_object_flag(auto flag)
    {
        flagIter = std::find(objectFlags.begin(), objectFlags.end(), flag);
        objectFlags.erase(flagIter);
    }
};

std::vector<gameObject> mainObjects = {};

//items
gameObject sword;
gameObject sheild;
gameObject key;
gameObject chest;
gameObject note;

//locations
gameObject gameStart;
gameObject abandonedTown;
gameObject oasis;
gameObject tavern;

//characters
gameObject bandit;
gameObject oldLady;
gameObject barKeep;
