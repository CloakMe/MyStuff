#include <string>
#include <list>
#include "Utilities.h"

//struct CmdResult{
//    virtual ~CmdResult(void){}
//};
//
//struct LObjectResult : public CmdResult{
//    ObjectLocation objectLocation;
//    ~LObjectResult(){}
//};
//
//struct SpeedResult : public CmdResult{
//    float averageSpeed;
//    ~SpeedResult(){}
//};

class GeoCmd
{
public:

    GeoCmd(const std::string& cmd);
    ~GeoCmd(void);

    char const * const GetCmdType() const;
    
    std::string CmdResponse() const;

private:
    std::list<std::string> cmd;
    bool SetLocation(ObjectLocation& loc, std::string& objectName) const;
    void SetObjectName(std::string& objectName) const;
};

