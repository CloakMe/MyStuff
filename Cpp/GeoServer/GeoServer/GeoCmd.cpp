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
    }else if(cmd.begin()->compare( Constants::CMD_SPEED ) == 0 && cmd.size() == Constants::CMD_SPEED_SIZE )
    {
        return Constants::CMD_SPEED;
    }else if(cmd.begin()->compare( Constants::CMD_EXIT ) == 0 && cmd.size() == Constants::CMD_EXIT_SIZE )
    {
        return Constants::CMD_EXIT;
    }//else
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
            Database::SetObjectLocation(objectName, loc);
            //to do create server response
            response = Database::GetMapLocations(objectName, loc);
        }
    }else if(GetCmdType() == Constants::CMD_SPEED)
    {
        std::string objectName;
        SetObjectName(objectName);
        if(!objectName.empty())
        {
            float averageVelocity = Database::GetAverageVelocity(objectName);
            response = std::to_string(averageVelocity);
            response.append(" m/s\r\n");
        }
    }else if(GetCmdType() == Constants::CMD_EXIT)
    {
        response.append("exit");
    }//else
    return response;
}

std::string GeoCmd::CmdWrapper(std::string input)
{
    std::list<std::string> splitedString = Utilities::SplitString(input, '\n');
    
    if(splitedString.size() == 0)
        return std::string();
    else if(splitedString.size() == 1)
    {
        GeoCmd geoCmd(*splitedString.begin());
        return geoCmd.CmdResponse();
    }//else
    //just process the last message, otherwise it is a bug
    //GeoCmd geoCmd(*splitedString.rbegin());
    //return geoCmd.CmdResponse();

    //for the sake of testing:
    std::string multipleResponse;        
    for(std::list<std::string>::const_iterator it = splitedString.begin();
        it != splitedString.end();
        it++)
    {
        GeoCmd geoCmd(*it);
        std::string cmdResponse = geoCmd.CmdResponse();
        if(!cmdResponse.empty())
        {
            multipleResponse.append( cmdResponse );
            multipleResponse.append("\r\n");
        }
    }
        
    return multipleResponse;
}

GeoCmd::~GeoCmd(void)
{
}
