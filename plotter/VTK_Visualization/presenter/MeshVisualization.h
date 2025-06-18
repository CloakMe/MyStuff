#pragma once
#include <vtkDataSet.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderer.h>

namespace visu
{

class MeshVisualization : public VisualizationStrategy 
{
    MeshVisualization() = default;
public:
    void createActors(vtkDataSet* dataset) override;
    void addToRenderer(vtkRenderer* renderer) override;
    void removeFromRenderer(vtkRenderer* renderer) override;

private:
    vtkNew<vtkDataSetMapper> mapper;
    vtkNew<vtkActor> actor;
};

}

