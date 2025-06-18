#pragma once
#include "VisuType.h"

namespace visu
{
    class IUI
    {
    public:
        virtual void Draw(VisuType drawType)=0;
    };
}
