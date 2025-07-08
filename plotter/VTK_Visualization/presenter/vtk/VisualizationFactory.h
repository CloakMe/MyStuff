#pragma once
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
    VisualizationFactory(std::unique_ptr<IVisualizationConfigurator> visualizationConfigurator);
    std::unique_ptr<VisualizationStrategy> createStrategy(VisuType visuType);
private:
    std::unique_ptr<IVisualizationConfigurator> m_visualizationConfigurator;
};

}