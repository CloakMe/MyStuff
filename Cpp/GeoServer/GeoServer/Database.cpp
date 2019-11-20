#include "Database.h"
#include "Utilities.h"
#include <fstream>
#include "Constants.h"
#include <string>

std::list<MapLocation> Database::mLocations;
std::map<std::string, std::list<ObjectLocation>> Database::mObjects;

bool Database::ReadLocations(const std::string& pathFileName)
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
            if(output.size()<=1)
                continue;

            std::list<std::string> splitOutput = Utilities::SplitString(output, Constants::COMMA);
            
			MapLocation newLocation;
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
                    if( !Utilities::IsFloat(*str) )
                        break;
					newLocation.latitude = static_cast<float>(std::atof(str->c_str()));

				}else if(counter == 2)
				{
                    if( !Utilities::IsFloat(*str) )
                        break;
					newLocation.longtitude = static_cast<float>(std::atof(str->c_str()));
				}else if(counter == 3)
				{
                    if( !Utilities::IsFloat(*str) )
                        break;
					newLocation.radius = 1000.0f * static_cast<float>(std::atof(str->c_str()));
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

void Database::SetObjectLocation(const std::string& object, const ObjectLocation& loc)
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

float Database::GetAverageVelocity(const std::string& objectName)
{
	std::map<std::string, std::list<ObjectLocation> >::iterator it = mObjects.find(objectName);

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
		float longtitude = listIt->longtitude;
		float latitude = listIt->latitude;
		++listIt;
		for(  ;listIt != it->second.end(); ++listIt)
		{
			distance += Utilities::GeoToMeters(listIt->latitude, listIt->longtitude, latitude, longtitude);

			longtitude = listIt->longtitude;
			latitude = listIt->latitude;
		}

		float result = static_cast<float>(distance/seconds);
		return result;
	}
}


std::string Database::GetMapLocations(const std::string& object, const ObjectLocation& loc)
{
    std::string mapLocations;
    if(mLocations.empty())
        return mapLocations;

    std::list<MapLocation>::const_iterator iterator =  mLocations.begin();
    for( ;iterator != mLocations.end(); iterator++)
    {
        double distance = Utilities::GeoToMeters(iterator->latitude, iterator->longtitude, loc.latitude, loc.longtitude);
        if(distance <= iterator->radius)
        {
            mapLocations.append(" ");
            mapLocations.append(iterator->name);
            mapLocations.append(",");
        }
    }

    if(!mapLocations.empty())
    {
        mapLocations.pop_back(); //erase trailing comma
        mapLocations.append("\r\n");
        std::string insertStr = object + " is in";
        mapLocations.insert(0, insertStr);
    }

    return mapLocations;
}


unsigned int Database::ObjectCount()
{
    return mObjects.size();
}

unsigned int Database::LocationCount()
{
    unsigned int count = 0;
    for(std::map<std::string, std::list<ObjectLocation>>::const_iterator it = mObjects.begin();
        it != mObjects.end();
        it++)
    {
        count += it->second.size();
    }
    return count;
}



