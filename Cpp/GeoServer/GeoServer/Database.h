#pragma once
#include <string>
#include <list>
#include <map>
#include <time.h>  

struct MapLocation
{
	float latitude; //x position
	float longtitude;//y position
	float radius;
	std::string name;
};

struct ObjectLocation
{
	float latitude; //x position
	float longtitude;//y position
	time_t time;
};

class Database
{
    public:
	static bool ReadLocations(const std::string& pathFileName);
	static void SetObjectLocation(const std::string& object, const ObjectLocation& loc);
	static float GetAverageVelocity(const std::string& object);
    static std::string GetMapLocations(const std::string& object, const ObjectLocation& loc);

    static unsigned int ObjectCount();
    static unsigned int LocationCount();
    //static void TrimString(std::string& str);
private:
	static std::list<MapLocation> mLocations;
	static std::map<std::string, std::list<ObjectLocation>> mObjects;
};

