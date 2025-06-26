#include "VTK_CFDVisualizer.h"

using namespace visu;
using namespace std;

VTK_CFDVisualizer::VTK_CFDVisualizer(VisualizationConfigurator& configurator)
{
    renderWindow->AddRenderer(renderer);
    interactor->SetRenderWindow(renderWindow);
    configurator.configure(manager, dataset);
    setupUI();
}
        
void VTK_CFDVisualizer::Render(VisuType drawType)
{
   m_renderWindow->Render();
   m_interactor->Start();
}

void VTK_CFDVisualizer::setupUI()
{
/*    m_interactor->AddObserver(vtkCommand::KeyPressEvent, [this](vtkObject*, unsigned long, void*) {
        //m_manager.showNext();
        m_renderWindow->Render();
    });*/
}

void VTK_CFDVisualizer::OnKeyPress() {
            //manager.showNext();
            m_renderWindow->Render();
        }