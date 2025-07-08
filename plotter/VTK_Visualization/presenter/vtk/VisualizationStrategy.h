#pragma once
#include "IVisualizationConfigurator.h"
#include <vtkDataSet.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <string>

namespace visu
{

class VisualizationStrategy
{
public:
    virtual vtkSmartPointer<vtkActor> createActors(vtkSmartPointer<vtkDataSet> dataset) = 0;
    //virtual void addToRenderer(vtkRenderer* renderer) = 0;
    //virtual void removeFromRenderer(vtkRenderer* renderer) = 0;
};

}


