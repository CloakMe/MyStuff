#pragma once
#include <string>

namespace visu
{

class IKeyControlsConfigurator
{
    virtual std::string getKeyVisuChanger() = 0;
};

}


