#pragma once
#include "AbstractDB.h"
#include <vtkDataSet.h>
#include <vtkSmartPointer.h>

namespace visu
{

class VTK_DBWrapper : public AbstractDB
{
public:
    VTK_DBWrapper(vtkSmartPointer<vtkDataSet> dataset);
    ~VTK_DBWrapper();
    vtkSmartPointer<vtkDataSet> operator()();

private:    
    vtkSmartPointer<vtkDataSet> m_dataset;
};

}

