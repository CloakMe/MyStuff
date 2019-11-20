#include "Utilities.h"
#include "Constants.h"
#include "Database.h"


double Utilities::GeoToMeters(float lat1, float lon1, float lat2, float lon2)
{  
    double dLat = lat2 * Constants::PI / 180.0 - lat1 * Constants::PI / 180.0;
    double dLon = lon2 * Constants::PI / 180.0 - lon1 *Constants::PI / 180.0;
    double a = sin(dLat/2) * sin(dLat/2) +
                cos(lat1 * Constants::PI / 180.0) * cos(lat2 * Constants::PI / 180.0) *
                sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2( sqrt(a), sqrt(1-a));
    double d = Constants::EARTH_RADIUS * c;
    return d; // meters
}

std::list<std::string> Utilities::SplitString(const std::string& output, const char delimiter)
{
    std::list<std::string> splitedString;
    unsigned int start = 0U;
	unsigned int end = output.find(delimiter);

	MapLocation newLocation;
	while (true)// split string
	{
		std::string str = output.substr(start, end - start);
        // trim string
        str.erase(str.find_last_not_of(Constants::TRIM_CHARS) + 1);
        str.erase(0, str.find_first_not_of(Constants::TRIM_CHARS));

        splitedString.push_back(str);

		//end condition
		if(end == std::string::npos)
			break;

        while (end != std::string::npos)// split string
	    {
		    start = end + 1;
		    end = output.find(delimiter, start);
            if(end != start)
                break;
        }
	} //end while split string

    return splitedString;
}

bool Utilities::IsFloat(const std::string& string)
{    
    std::string::const_iterator it = string.begin();
    bool decimalPoint = false;
    unsigned int minSize = 0;
    if( string.size()>0 && (string[0] == '-' || string[0] == '+')){
        it++;
        minSize++;
    }
    while(it != string.end())
    {
        if(*it == '.')
        {
            if(!decimalPoint) 
                decimalPoint = true;
            else 
                break;
        }else if(!isdigit(*it) && ((*it!='f') || it+1 != string.end() || !decimalPoint))
        {
            break;
        }
        ++it;
    }
    return string.size()>minSize && it == string.end();
}

