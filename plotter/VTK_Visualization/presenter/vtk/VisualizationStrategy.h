#pragma once
#include "IVisualizationConfigurator.h"
#include <vtkDataSet.h>
#include <vtkRenderer.h>
#include <string>
#include <memory>

namespace visu
{

class VisualizationStrategy
{
public:
    virtual void createActors(vtkDataSet* dataset) = 0;
    virtual void addToRenderer(vtkRenderer* renderer) = 0;
    virtual void removeFromRenderer(vtkRenderer* renderer) = 0;

protected:
    std::unique_ptr<IVisualizationConfigurator> m_visuConfigurator;
};

}


