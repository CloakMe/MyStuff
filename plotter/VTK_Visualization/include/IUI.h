#pragma once
#include "Type.h"

namespace visu
{
    public class IUI
    {
    public:
        virtual void Draw(Type drawType)=0;
    };
}
