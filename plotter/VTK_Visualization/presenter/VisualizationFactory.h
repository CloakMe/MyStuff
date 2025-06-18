#pragma once
#include "vtkDataSet.h"
namespace visu
{   
    class VisualizationFactory 
    {
    public:
        std::unique_ptr<VisualizationStrategy> createStrategy(
            const std::string& mode, vtkDataSet* dataset);
    };
    
}