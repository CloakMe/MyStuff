#pragma once

namespace visu
{

class AbstractDB
{
public:
    virtual ~AbstractDB() = default;
    //virtual void* operator()();
protected:
    AbstractDB() = default;
};

}
