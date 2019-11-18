#include "Utilities.h"
//#include<iostream>
#include <fstream>
#include "Constants.h"
#include <string>

std::list<Location> Utilities::mLocations;
std::map<std::string, std::list<ObjectLocation>> Utilities::mObjects;

bool Utilities::ReadLocations(const std::string& pathFileName)
{
	std::ifstream readGeoLocationsFile;
	readGeoLocationsFile.open(pathFileName.c_str());
	std::string output;
	output.reserve(100);
	if (readGeoLocationsFile.is_open()) 
    {
		while (!readGeoLocationsFile.eof()) 
		{
			getline(readGeoLocationsFile, output); 
			std::list<std::string> splitOutput = SplitString(output);

			Location newLocation;
            std::list<std::string>::iterator str = splitOutput.begin();
            int counter = 0;
			for( ; str != splitOutput.end(); counter++, str++)
			{
				//assing location structure
				if(counter == 0)
				{
					newLocation.name = *str;
				}else if(counter == 1) 
				{
					newLocation.latitude = std::atof(str->c_str());
				}else if(counter == 2)
				{
					newLocation.longtitude = std::atof(str->c_str());
				}else if(counter == 3)
				{
					newLocation.radius = std::atof(str->c_str());
				}else{
					readGeoLocationsFile.close();
					return false;
				}
			} 

			if(counter == 4)
				mLocations.push_back(newLocation);
            else
            {
				readGeoLocationsFile.close();
				return false;
			}
		}//end while readGeoLocationsFile
	}else
	{
		return false;
	}

	readGeoLocationsFile.close();

	return true;
}

void Utilities::SetObjectLocation(const std::string& object, const ObjectLocation& loc)
{
	std::map<std::string, std::list<ObjectLocation> >::iterator it = mObjects.find(object);
	if(it == mObjects.end())
	{
		std::list<ObjectLocation> ls;
		ls.push_back(loc);
		mObjects.insert(std::pair<std::string, std::list<ObjectLocation>>(object, ls));
	}else
	{
		it->second.push_back(loc);
	}
}

float Utilities::GetAverageVelocity(const std::string& object)
{
	std::map<std::string, std::list<ObjectLocation> >::iterator it = mObjects.find(object);

	if(it == mObjects.end())
	{
		return 0.0f;
	}else
	{		
		const std::list<ObjectLocation>& ojbectLocationList = it->second;
		if(ojbectLocationList.size() <= 1)
			return 0.0f;

		time_t timeBegin = ojbectLocationList.begin()->time;
		time_t timeEnd = ojbectLocationList.rbegin()->time;
		double seconds = difftime(timeEnd, timeBegin);
		if(seconds < 1)
			return 0.0f;

		double distance = 0.0;
		
		std::list<ObjectLocation>::iterator listIt = it->second.begin();
		double longtitude = listIt->longtitude;
		double latitude = listIt->latitude;
		++listIt;
		for(  ;listIt != it->second.end(); ++listIt)
		{
			distance += GeoToMeters(listIt->latitude, listIt->longtitude, latitude, longtitude);

			longtitude = listIt->longtitude;
			latitude = listIt->latitude;
		}

		float result = static_cast<float>(distance/seconds);
		return result;
	}
}

double Utilities::GeoToMeters(float lat1, float lon1, float lat2, float lon2)
{  
    double dLat = lat2 * Constants::PI / 180 - lat1 * Constants::PI / 180;
    double dLon = lon2 * Constants::PI / 180 - lon1 *Constants::PI / 180;
    double a = sin(dLat/2) * sin(dLat/2) +
                cos(lat1 * Constants::PI / 180) * cos(lat2 * Constants::PI / 180) *
                sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2( sqrt(a), sqrt(1-a));
    double d = Constants::EARTH_RADIUS * c;
    return d; // meters
}

//void Utilities::TrimString(std::string& str)
//{
//	str.erase(str.find_last_not_of(Constants::TRIM_CHARS) + 1);
//    str.erase(0, str.find_first_not_of(Constants::TRIM_CHARS));
//}

std::list<std::string> Utilities::SplitString(const std::string& output)
{
    std::list<std::string> splitedString;
    unsigned int start = 0U;
	unsigned int end = output.find(Constants::DELIMITER);

	Location newLocation;
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

		start = end + 1;
		end = output.find(Constants::DELIMITER, start);
	} //end while split string

    return splitedString;
}