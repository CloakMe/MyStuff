#pragma once
#include "VisuType.h"
#include "AbstractDB.h"
#include <memory>

namespace visu
{
    class IVisualizer
    {
    public:
        virtual void Render(std::unique_ptr<AbstractDB> input)=0;
    };
}
