#pragma once
#include "VisualizationStrategy.h"
#include "AbstractDB.h"
#include <vtkDataSet.h>
#include <memory>
#include "VisuType.h"
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>

namespace visu
{
    
class VisualizationFactory 
{
public:
    std::unique_ptr<VisualizationStrategy> createStrategy(
        VisuType visuType, vtkSmartPointer<vtkDataSet> dataset);
};

/*class VisualizationConfigurator 
{
public:
    void configure(vtkSmartPointer<vtkDataSet> dataset) 
    {
        VisualizationFactory factory;
        m_visualizations.push_back(factory.createStrategy(VisuType::Mesh, dataset));
        m_visualizations.push_back(factory.createStrategy(VisuType::Pressure, dataset));
        m_visualizations.push_back(factory.createStrategy(VisuType::Velocity, dataset));
    }
private:
    std::vector<std::unique_ptr<VisualizationStrategy>> m_visualizations;
};*/

}