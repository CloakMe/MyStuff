#pragma once
#include "VisualizationStrategy.h"
#include "IConfigurator.h"
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include <vtkActor.h>
#include <vtkRenderer.h>

namespace visu
{

class VelocityGlyphVisualization : public VisualizationStrategy 
{
public:
    VelocityGlyphVisualization(const IConfigurator& configurator);
    vtkSmartPointer<vtkActor> createActors(vtkSmartPointer<vtkDataSet> dataset) override;
    //void addToRenderer(vtkRenderer* renderer) override;
    //void removeFromRenderer(vtkRenderer* renderer) override;

private:
    const IConfigurator& m_configurator;
};

}

