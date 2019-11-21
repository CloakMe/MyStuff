#pragma once
#include <string>
#include <list>
#include "Database.h"

class GeoCmd
{
public:

    GeoCmd(const std::string& cmd);
    ~GeoCmd(void);

    char const * const GetCmdType() const;
    
    std::string CmdResponse() const;

    static std::string CmdWrapper(std::string input);
private:
    std::list<std::string> cmd;
    bool SetLocation(ObjectLocation& loc, std::string& objectName) const;
    void SetObjectName(std::string& objectName) const;
};

