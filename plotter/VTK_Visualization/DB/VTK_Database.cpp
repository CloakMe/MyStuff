#include "VTK_Database.h"
#include <vtkDataSetReader.h>


using namespace visu;
using namespace std;

VTK_Database::VTK_Database(const std::string& fileSeries)
  : m_fileSeries(fileSeries)
{}

void VTK_Database::Load()
{   // Auto-detect file type
    vtkNew<vtkDataSetReader> reader;
    reader->SetFileName(m_fileSeries.c_str());
    reader->Update();
    m_dataset = reader->GetOutput();
}

void VTK_Database::LoadSpecific(LoadType loadType, std::string value)
{
    
}

vtkSmartPointer<vtkDataSet> VTK_FileSeries::getDataSet() const 
{
    return m_dataset;
}