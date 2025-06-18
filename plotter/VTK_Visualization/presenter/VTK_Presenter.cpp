#include "VTK_Presenter.h"

using namespace visu;
using namespace std;

VTK_Presenter::VTK_Presenter(unique_ptr<IDB> database, unique_ptr<IUI> ui) :
    m_IDB(std::move(database)), 
    m_IUI(std::move(ui))
{
    
}

void VTK_Presenter::Load()
{
    // — calls IDB::Load internally.
}

void VTK_Presenter::LoadSpecific(LoadType loadType, std::string value)
{
    
}
void VTK_Presenter::SetVisualizationType(VisuType mode)
{
// — switch between mesh or vector field.
}

void VTK_Presenter::SetCrossSection(const CrossSection& crossSection)
{
    
}
void VTK_Presenter::UpdateView()
{
 //— triggers the UI to redraw or refresh.    
} 