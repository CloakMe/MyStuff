#pragma once
#include "IVisualizationConfigurator.h"
#include "VisuType.h"

namespace visu
{

class VisualizationConfigurator : public IVisualizationConfigurator
{
public:
    VisualizationConfigurator();
    ~VisualizationConfigurator();
    std::string getVisuType(VisuType visuType) const override;
};

}

