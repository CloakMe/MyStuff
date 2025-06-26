#include "VTK_FileSeries.h"
#include <vtkDataSetReader.h>


using namespace visu;
using namespace std;

VTK_FileSeries::VTK_FileSeries(const std::string& fileSeries)
  : m_fileSeries(fileSeries)
{}

void VTK_FileSeries::Load()
{   // Auto-detect file type
    vtkNew<vtkDataSetReader> reader;
    reader->SetFileName(m_fileSeries.c_str());
    reader->Update();
    m_dataset = reader->GetOutput();
}

void VTK_FileSeries::LoadSpecific(LoadType loadType, std::string value)
{
    
}

vtkSmartPointer<vtkDataSet> VTK_FileSeries::getDataSet() const 
{
    return m_dataset;
}