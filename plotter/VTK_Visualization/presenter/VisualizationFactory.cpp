#include "VisualizationFactory.h"
#include "MeshVisualization.h"
#include "PressureVisualization.h"
#include "VelocityVisualization.h"

using namespace visu;

// Factory implementation
std::unique_ptr<VisualizationStrategy> VisualizationFactory::createStrategy(
    const std::string& mode, vtkDataSet* dataset)
{
    if (!dataset) {
        std::cerr << "vtkDataSet pointer is null!" << std::endl;
        return nullptr;
    }

    if (mode == "mesh") {
        auto strategy = std::make_unique<MeshVisualization>();
        strategy->createActors(dataset);
        return strategy;
    }
    else if (mode == "pressure") {
        auto strategy = std::make_unique<PressureVisualization>();
        strategy->createActors(dataset);
        return strategy;
    }
    else if (mode == "velocity") {
        auto strategy = std::make_unique<VelocityVisualization>();
        strategy->createActors(dataset);
        return strategy;
    }
    throw std::runtime_error("Unknown visualization mode");
}