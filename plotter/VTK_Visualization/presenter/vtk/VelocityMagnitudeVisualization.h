#pragma once
#include "VisualizationStrategy.h"

namespace visu
{

class VelocityMagnitudeVisualization : public VisualizationStrategy
{
public:
    VelocityMagnitudeVisualization(const IConfigurator& configurator);
    vtkSmartPointer<vtkActor> createActors(vtkSmartPointer<vtkDataSet> dataset) override;

    //void addToRenderer(vtkRenderer* renderer) override;
    //void removeFromRenderer(vtkRenderer* renderer) override;

private:
    const IConfigurator& m_configurator;

};

}

