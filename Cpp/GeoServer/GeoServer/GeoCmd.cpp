#include "GeoCmd.h"
#include "Utilities.h"
#include "Constants.h"
#include "Utilities.h"

GeoCmd::GeoCmd(const std::string& cmd)
{
    this->cmd = Utilities::SplitString(cmd);
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

CmdResult GeoCmd::GetResult() 
{
    char const * const type = GetCmdType();
    if(type == Constants::CMD_SET)
    {
        LObjectResult result;
        ObjectLocation loc;
        std::list<std::string>::iterator it = cmd.begin();

        //loc.latitude = 
    }

}

GeoCmd::~GeoCmd(void)
{
}
