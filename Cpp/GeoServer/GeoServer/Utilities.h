#pragma once
#include <string>
#include <list>

class Utilities
{
public:
    static std::list<std::string> SplitString(const std::string& str, const char delimiter);
    static bool IsFloat(const std::string& str);
    static double GeoToMeters(float lat1, float lon1, float lat2, float lon2);    
};

