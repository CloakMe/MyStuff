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
            return config.GetVelocityValue();
        case VisuType::Velocity:
            return config.GetPressureValue();
        default:
            return config.GetMeshValue();
    }
    return "";
}