#include "KeyControlsConfigurator.h"
#include "JSONConfigParser.h"

visu::KeyControlsConfigurator::KeyControlsConfigurator()
{
}

visu::KeyControlsConfigurator::~KeyControlsConfigurator()
{
}

std::string visu::getKeyVisuChanger()
{
    JSONConfigParser::Instance().GetVisualizationValue();
}
