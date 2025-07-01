#pragma once
#include <string>
#include "VisuType.h"

namespace visu
{

class IVisualizationConfigurator
{
public:
    virtual std::string getVisuType(VisuType visuType) const = 0;
};

}


