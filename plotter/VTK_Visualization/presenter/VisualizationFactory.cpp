#include "VisualizationFactory.h"
#include "MeshVisualization.h"
#include "PressureVisualization.h"
#include "VelocityVisualization.h"
#include "VisuType.h"

using namespace visu;

// Factory implementation
std::unique_ptr<VisualizationStrategy> VisualizationFactory::createStrategy(
    VisuType visuType, vtkDataSet* dataset)
{
    if (!dataset) {
        std::cerr << "vtkDataSet pointer is null!" << std::endl;
        return nullptr;
    }

    if (visuType == VisuType::Mesh) 
    {
        auto strategy = std::make_unique<MeshVisualization>();
        strategy->createActors(dataset);
        return strategy;
    }
    else if (visuType == VisuType::Pressure) 
    {
        auto strategy = std::make_unique<PressureVisualization>();
        strategy->createActors(dataset);
        return strategy;
    }
    else if (visuType == VisuType::Velocity) 
    {
        auto strategy = std::make_unique<VelocityVisualization>();
        strategy->createActors(dataset);
        return strategy;
    }
    throw std::runtime_error("Unknown visualization mode");
}
