#pragma once
#include "VisualizationStrategy.h"
#include "IVisualizationConfigurator.h"
#include <vtkDataSet.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>

namespace visu
{

class MeshVisualization : public VisualizationStrategy 
{
public:
    MeshVisualization(const IVisualizationConfigurator& visualizationConfigurator);
    void createActors(vtkDataSet* dataset) override;
    void addToRenderer(vtkRenderer* renderer) override;
    void removeFromRenderer(vtkRenderer* renderer) override;

private:
    vtkNew<vtkDataSetMapper> mapper;
    vtkNew<vtkActor> actor;
    const IVisualizationConfigurator& m_visualizationConfigurator;
};

}

