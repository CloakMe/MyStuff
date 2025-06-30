#pragma once
#include "VisualizationStrategy.h"
#include "VisuType.h"
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include <memory>

namespace visu
{
    
class VisualizationFactory 
{
public:
    std::unique_ptr<VisualizationStrategy> createStrategy(
        VisuType visuType, vtkSmartPointer<vtkDataSet> dataset);
};

}