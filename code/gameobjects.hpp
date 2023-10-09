// Add necessary includes & imports here
#include "catch.hpp"
#include <iostream>
#include <algorithm>


class gameObject
{
    private:
    std::string objectType;
    std::string objectName;
    std::string objectDescription; 
    std::vector<std::string> objectFlags;
    std::vector<std::string>::iterator flagIter;

    public:
    
    void set_object_name(std::string name)
    {
        objectName = name;
    }
    gameObject(std::string oType, std::string oName, std::string oDesc,std::vector<std::string> oFlags )
    {
        objectType = oType;
        objectName = oName;
        objectDescription = oDesc;
        objectFlags = oFlags;
        
    }
    gameObject(std::string oType, std::string oName, std::string oDesc)
    {
        objectType = oType;
        objectName = oName;
        objectDescription = oDesc;
    
        
    }
//    std::string get_objectType(){
//       return objectType;
//   }
//   std::string get_objectName(){
//        return objectName;
//    }
//   std::string get_objectDescription(){
//       return objectDescription;
//   }
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
//if you think of any cool characters or locations or even items you want to add freel free to add them
//if you do add something just make a description for the obkect, and fill in all the other requrements 
gameObject sword("items","sword","");
gameObject sheild("items","sheild","");
gameObject key;
gameObject chest;
gameObject note;


//locations
gameObject gameStart;
gameObject abandonedTown;
gameObject oasis;
gameObject tavern;

//characters

gameObject bandit("character","bandit","",{"is alive"});/*the is alive is a flag,
it is used for anything that can block you from progressing*/
gameObject oldLady;
gameObject barKeep;

