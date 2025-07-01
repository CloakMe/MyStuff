#pragma once
#include <string>

namespace visu
{

class IKeyControlsConfigurator
{
public:
    virtual std::string getKeyVisuChanger() = 0;
};

}


