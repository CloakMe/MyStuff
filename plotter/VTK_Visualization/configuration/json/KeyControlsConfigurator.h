#pragma once
#include "IKeyControlsConfigurator.h"

namespace visu
{

class KeyControlsConfigurator : public IKeyControlsConfigurator
{
public:
    KeyControlsConfigurator();
    ~KeyControlsConfigurator();
    virtual std::string getKeyVisuChanger() override;
};

}

