#pragma once
#include "VisualizationStrategy.h"
#include <vtkDataSet.h>
#include <memory>

namespace visu
{
    
class VisualizationFactory 
{
public:
    std::unique_ptr<VisualizationStrategy> createStrategy(
        VisuType visuType, vtkDataSet* dataset);
};
    
class VisualizationConfigurator 
{
public:
    void configure(std::vector<std::unique_ptr<VisualizationStrategy>>& m_visualizations, vtkSmartPointer<vtkDataSet> dataset) 
    {
        VisualizationFactory factory;
        m_visualizations.push_back(factory.createStrategy("mesh", dataset));
        m_visualizations.push_back(factory.createStrategy("pressure", dataset));
        m_visualizations.push_back(factory.createStrategy("velocity", dataset));
    }
private:
    std::vector<std::unique_ptr<VisualizationStrategy>> m_visualizations;
};

}