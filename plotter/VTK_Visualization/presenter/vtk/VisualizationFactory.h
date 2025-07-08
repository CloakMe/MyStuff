#pragma once
#include "IConfigurator.h"
#include "VisualizationStrategy.h"
#include "VisuType.h"
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include <memory>

namespace visu
{
    
class VisualizationFactory 
{
public:
    VisualizationFactory(const IConfigurator& configurator);
    std::unique_ptr<VisualizationStrategy> createStrategy(VisuType visuType);
private:
    const IConfigurator& m_configurator;
};

}