#include "IDB.h"
#include "IVisualizer.h"
#include "VisualizationFactory.h"
#include "VTK_Presenter.h"
#include "CrossSection.h"
#include <memory>

using namespace visu;
using namespace std;

VTK_Presenter::VTK_Presenter(unique_ptr<IDB> database, unique_ptr<IVisualizer> view)
  : m_database(std::move(database)) 
  , m_IVisualizer(std::move(view))
  , m_visuType(VisuType::Mesh)
{
    
}

void VTK_Presenter::Load()
{
    m_database->Load();
}

void VTK_Presenter::LoadSpecific(LoadType loadType, std::string value)
{
    m_database->LoadSpecific(loadType, value);
}

void VTK_Presenter::SetVisualizationType(VisuType mode)
{
// — switch between mesh or vector field.
    //VisualizationFactory factory;
    //unique_ptr<VisualizationStrategy> strategy = factory.createStrategy(mode, m_database->getAbstractDB());
}

void VTK_Presenter::SetCrossSection(const CrossSection& crossSection)
{
    
}

void VTK_Presenter::UpdateView()
{//— triggers the UI to redraw or refresh.    
    m_IVisualizer->Render(m_database->GetAbstractDb());
} 