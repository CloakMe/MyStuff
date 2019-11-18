#pragma once
#include <string>
#include <list>
#include <map>
#include <set>
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

class Utilities
{
public:
	static bool ReadLocations(const std::string& pathFileName);
	static void SetObjectLocation(const std::string& object, const ObjectLocation& loc);
	static float GetAverageVelocity(const std::string& object);
    static std::string GetMapLocations(const std::string& object, const ObjectLocation& loc);

    static std::list<std::string> SplitString(const std::string& str, char delimiter);

    static bool IsFloat(const std::string& str);
    //static void TrimString(std::string& str);
private:
	static std::list<MapLocation> mLocations;
	static std::map<std::string, std::list<ObjectLocation>> mObjects;

    static double GeoToMeters(float lat1, float lon1, float lat2, float lon2);
};

