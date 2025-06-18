#pragma once
#include "VisuType.h"

namespace visu
{
    class IVisualizer
    {
    public:
        virtual void Render(VisuType drawType)=0;
    };
}
