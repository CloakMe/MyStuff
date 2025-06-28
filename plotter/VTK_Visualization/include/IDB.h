#pragma once
#include <string>
#include <memory>
#include "AbstractDB.h"

namespace visu
{
    
enum LoadType
{
    Next,
    Previous,
    Specific
};

class IDB
{
  public:
    virtual void Load() = 0;
    virtual void LoadSpecific(LoadType loadType, std::string value) = 0;
    virtual std::unique_ptr<AbstractDB> GetAbstractDb() = 0;
};
    
}
