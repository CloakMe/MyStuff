#pragma once
#include <string>

namespace visu
{
    enum LoadType
    {
        Next,
        Previous,
        Specific
    };
    
    public class IDB
    {
      public:
        virtual void Load() = 0;
        virtual void LoadSpecific(LoadType loadType, std::string value) = 0;
    };
}
