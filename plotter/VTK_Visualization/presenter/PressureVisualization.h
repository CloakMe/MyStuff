#pragma once
#include <vtkDataSet.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>

namespace visu
{

class PressureVisualization : public VisualizationStrategy 
{
public:
    void createActors(vtkDataSet* dataset) override;
    void addToRenderer(vtkRenderer* renderer) override;
    void removeFromRenderer(vtkRenderer* renderer) override;

private:
    vtkNew<vtkDataSetMapper> mapper;
    vtkNew<vtkActor> actor;
};

}

