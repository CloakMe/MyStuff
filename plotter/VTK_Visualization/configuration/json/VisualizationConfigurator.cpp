#include "VisualizationConfigurator.h"
#include "JSONConfigParser.h"

visu::VisualizationConfigurator::VisualizationConfigurator()
{
}

visu::VisualizationConfigurator::~VisualizationConfigurator()
{
}

std::string visu::VisualizationConfigurator::getVisuType(VisuType visuType) const
{
    JSONConfigParser& config = JSONConfigParser::Instance();
    switch(visuType)
    {
        case VisuType::Pressure:
            return config.GetPressureValue();
        case VisuType::Velocity:
            return config.GetVelocityValue();
        default:
            return config.GetMeshValue();
    }
    return "";
}