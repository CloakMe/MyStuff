#pragma once
#include "VisualizationStrategy.h"
#include <vtkDataSet.h>
#include <memory>

namespace visu
{   
    class VisualizationFactory 
    {
    public:
        std::unique_ptr<VisualizationStrategy> createStrategy(
            const std::string& mode, vtkDataSet* dataset);
    };
    
}