#include "VisualizationFactory.h"
#include "MeshVisualization.h"
#include "PressureVisualization.h"
#include "VelocityGlyphVisualization.h"
#include "VelocityMagnitudeVisualization.h"
#include "VisuType.h"
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkCellData.h>

using namespace visu;
using namespace std;

// Factory implementation
VisualizationFactory::VisualizationFactory(const IConfigurator& configurator)
    : m_configurator(configurator)
{
}

std::unique_ptr<VisualizationStrategy> VisualizationFactory::createStrategy(VisuType visuType)
{
    unique_ptr<VisualizationStrategy> strategy = nullptr;
    if (visuType == VisuType::Mesh) 
    {
        strategy = make_unique<MeshVisualization>(m_configurator);
        return strategy;
    }
    else if (visuType == VisuType::Pressure) 
    {
        strategy = make_unique<PressureVisualization>(m_configurator);
        return strategy;
    }
    else if (visuType == VisuType::VelocityMagnitude) 
    {
        strategy = make_unique<VelocityMagnitudeVisualization>(m_configurator);
        return strategy;
    }
    else if (visuType == VisuType::VelocityGlyph) 
    {
        strategy = make_unique<VelocityGlyphVisualization>(m_configurator);
        return strategy;
    }
    
    cerr << "Unknown visualization mode!" << endl;
    return nullptr;
}
