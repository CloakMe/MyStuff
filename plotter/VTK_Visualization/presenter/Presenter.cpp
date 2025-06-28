#include "Presenter.h"
#include "IVisualizer.h"
#include <memory>

using namespace visu;
using namespace std;

Presenter::Presenter(unique_ptr<IDB> database, unique_ptr<IVisualizer> ui)
  : m_database(std::move(database)) 
  , m_IVisualizer(std::move(ui))
  , m_visuType(VisuType::Mesh)
{
    
}

void Presenter::Load()
{
    m_database->Load();
}

void Presenter::LoadSpecific(LoadType loadType, std::string value)
{
    m_database->LoadSpecific(loadType, value);
}

void Presenter::SetVisualizationType(VisuType mode)
{
// — switch between mesh or vector field.
}

void Presenter::SetCrossSection(const CrossSection& crossSection)
{
    
}

void Presenter::UpdateView()
{//— triggers the UI to redraw or refresh.
    m_IVisualizer->Render(m_database->GetAbstractDb());
} 