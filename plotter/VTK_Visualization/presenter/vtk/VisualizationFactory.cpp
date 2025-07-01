#include "VisualizationFactory.h"
#include "MeshVisualization.h"
#include "PressureVisualization.h"
#include "VelocityVisualization.h"
#include "VisuType.h"

using namespace visu;
using namespace std;

// Factory implementation
VisualizationFactory::VisualizationFactory(std::unique_ptr<IVisualizationConfigurator> visualizationConfigurator)
{
    m_visualizationConfigurator = move(visualizationConfigurator);
}

std::unique_ptr<VisualizationStrategy> VisualizationFactory::createStrategy(
    VisuType visuType, vtkSmartPointer<vtkDataSet> dataset)
{
    if (!dataset) {
        cerr << "vtkDataSet pointer is null!" << endl;
        return nullptr;
    }
/*    unique_ptr<VTK_DBWrapper> vtk_database = move(database);
    vtkDataSet* dataset = *((*vtk_database)());*/
    unique_ptr<VisualizationStrategy> strategy = nullptr;
    if (visuType == VisuType::Mesh) 
    {
        strategy = make_unique<MeshVisualization>(*m_visualizationConfigurator);
        strategy->createActors(dataset);
        return strategy;
    }
    else if (visuType == VisuType::Pressure) 
    {
        strategy = make_unique<PressureVisualization>(*m_visualizationConfigurator);
        strategy->createActors(dataset);
        return strategy;
    }
    else if (visuType == VisuType::Velocity) 
    {
        strategy = make_unique<VelocityVisualization>(*m_visualizationConfigurator);
        strategy->createActors(dataset);
        return strategy;
    }
    cerr << "Unknown visualization mode!" << endl;
    return nullptr;
}
