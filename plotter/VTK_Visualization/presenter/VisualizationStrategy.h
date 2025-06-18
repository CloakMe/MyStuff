#pragma once
#include <vtkDataSet.h>
#include <vtkRenderer.h>
namespace visu
{

class VisualizationStrategy 
{
public:
    //virtual ~VisualizationStrategy() = default;
    virtual void createActors(vtkDataSet* dataset) = 0;
    virtual void addToRenderer(vtkRenderer* renderer) = 0;
    virtual void removeFromRenderer(vtkRenderer* renderer) = 0;
};

}


