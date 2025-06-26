#include "VTK_Presenter.h"
#include "VisualizationFactory.h"
#include <memory>

using namespace visu;
using namespace std;

VTK_Presenter::VTK_Presenter(unique_ptr<VTK_FileLoader> fileLoader, unique_ptr<IVisualizer> ui)
  : m_fileLoader(std::move(fileLoader)) 
  , m_IVisualizer(std::move(ui))
  , m_visuType(VisuType::Mesh)
{
    
}

void VTK_Presenter::Load()
{
    m_fileLoader->Load();
}

void VTK_Presenter::LoadSpecific(LoadType loadType, std::string value)
{
    m_fileLoader->LoadSpecific(loadType, value);
}

void VTK_Presenter::SetVisualizationType(VisuType mode)
{
// — switch between mesh or vector field.
    VisualizationFactory factory;
    unique_ptr<VisualizationStrategy> strategy = factory.createStrategy(mode, m_fileLoader->getDataSet());
}

void VTK_Presenter::SetCrossSection(const CrossSection& crossSection)
{
    
}

void VTK_Presenter::UpdateView()
{//— triggers the UI to redraw or refresh.    
    m_IVisualizer->Render(m_visuType);
} 