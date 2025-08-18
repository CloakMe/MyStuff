#pragma once
#include <vtkMapper.h>

namespace visu
{

class ScalarBarFactory
{
public:
    ScalarBarFactory() = default;
    vtkSmartPointer<vtkScalarBarActor> visu::ScalarBarFactory::GetScalarBar(vtkSmartPointer<vtkMapper> mapper);
};

}

