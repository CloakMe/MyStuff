#include "VisualizationConfigurator.h"
#include "JSONConfigParser.h"

visu::VisualizationConfigurator::VisualizationConfigurator(VisuType visuType)
  : m_visuType(visuType)
{
}

visu::VisualizationConfigurator::~VisualizationConfigurator()
{
}

std::string visu::VisualizationConfigurator::getVisuType()
{
    JSONConfigParser& config = JSONConfigParser::Instance();
    switch(m_visuType)
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