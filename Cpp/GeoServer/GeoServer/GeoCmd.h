#include <string>
#include <list>
struct ObjectLocation;

struct CmdResult{
    virtual ~CmdResult(void){}
};

struct LObjectResult : public CmdResult{
    ObjectLocation* objectLocation;
    //~LObjectResult{

    //}
};

struct SpeedResult : public CmdResult{
    float averageSpeed;

};

class GeoCmd
{
public:

    GeoCmd(const std::string& cmd);
    ~GeoCmd(void);

    char const * const GetCmdType() const;

    CmdResult GetResult();

private:
    std::list<std::string> cmd;
};

