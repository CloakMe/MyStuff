#include "GeoCmd.h"
#include "Utilities.h"
#include "Constants.h"
#include <time.h>  

GeoCmd::GeoCmd(const std::string& cmd)
{
    this->cmd = Utilities::SplitString(cmd, Constants::SPACE);
}

char const * const GeoCmd::GetCmdType() const
{
    if(cmd.empty())
        return Constants::CMD_UNKNOWN;

    if(cmd.begin()->compare( Constants::CMD_SET ) == 0 && cmd.size() == Constants::CMD_SET_SIZE )
    {
        return Constants::CMD_SET;
    }

    if(cmd.begin()->compare( Constants::CMD_SPEED ) == 0 && cmd.size() == Constants::CMD_SPEED_SIZE )
        return Constants::CMD_SPEED;

    return Constants::CMD_UNKNOWN;
}


bool GeoCmd::SetLocation(ObjectLocation& loc, std::string& objectName) const
{
    std::list<std::string>::const_iterator str = cmd.begin();

    str++; // set
    objectName = *str; //name
    str++;
    if( !Utilities::IsFloat(*str) )
        return false;
    loc.latitude = static_cast<float>(std::atof(str->c_str()));  //lati
    str++;
    if( !Utilities::IsFloat(*str) )
        return false;
    loc.longtitude = static_cast<float>(std::atof(str->c_str())); //longti

    loc.time = time(NULL);

    return true;
}

void GeoCmd::SetObjectName(std::string& objectName) const
{
        std::list<std::string>::const_iterator str = cmd.begin();

        str++; // speed
        objectName = *str; //name
}

std::string GeoCmd::CmdResponse() const
{
    std::string response;
    if(GetCmdType() == Constants::CMD_SET)
    {
        ObjectLocation loc;
        std::string objectName;
        if(SetLocation(loc, objectName))
        {
            Utilities::SetObjectLocation(objectName, loc);
            //to do create server response
            response = Utilities::GetMapLocations(objectName, loc);
        }
    }else if(GetCmdType() == Constants::CMD_SPEED)
    {
        std::string objectName;
        SetObjectName(objectName);
        if(!objectName.empty())
        {
            float averageVelocity = Utilities::GetAverageVelocity(objectName);
            response = std::to_string(averageVelocity);
            response.append(" m/s");
        }
    }//else
    return response;
}

GeoCmd::~GeoCmd(void)
{
}
