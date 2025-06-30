#pragma once
#include "IVisualizationConfigurator.h"
#include "VisuType.h"

namespace visu
{

class VisualizationConfigurator : public IVisualizationConfigurator
{
public:
    VisualizationConfigurator(VisuType visuType);
    ~VisualizationConfigurator();
    std::string getVisuType() override;
private:
    VisuType m_visuType;
};

}

