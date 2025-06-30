#include "VTK_DBWrapper.h"

visu::VTK_DBWrapper::VTK_DBWrapper(vtkSmartPointer<vtkDataSet> dataset) 
  : m_dataset(dataset)
{
}

visu::VTK_DBWrapper::~VTK_DBWrapper()
{
}

vtkSmartPointer<vtkDataSet> visu::VTK_DBWrapper::operator()() 
{
    return m_dataset;
}
