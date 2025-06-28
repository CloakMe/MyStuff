#include "VTK_Database.h"
#include "VTK_DBWrapper.h"
#include <vtkDataSetReader.h>


using namespace visu;
using namespace std;

VTK_Database::VTK_Database(const std::string& filepath)
  : m_filepath(filepath)
{}

void VTK_Database::Load()
{   // Auto-detect file type
    vtkNew<vtkDataSetReader> reader;
    reader->SetFileName(m_filepath.c_str());
    reader->Update();
    m_dataset = reader->GetOutput();
}

void VTK_Database::LoadSpecific(LoadType loadType, std::string value)
{
    
}

std::unique_ptr<AbstractDB> VTK_Database::GetAbstractDb() 
{
    return make_unique<VTK_DBWrapper>(m_dataset);
}