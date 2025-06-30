#pragma once
#include <string>

namespace visu
{

class IVisualizationConfigurator
{
    virtual std::string getVisuType() = 0;
};

}


