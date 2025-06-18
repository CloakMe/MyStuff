#include "VTK_CFDVisualizer.h"

using namespace visu;
using namespace std;

void VTK_CFDVisualizer::Render(VisuType drawType)
{
   m_renderWindow->Render();
   m_interactor->Start();
}

VTK_CFDVisualizer::VTK_CFDVisualizer(std::unique_ptr<vtkDataSet> dataset) :
    m_dataset(std::move(dataset))
{
    setupUI();
}

void VTK_CFDVisualizer::setupUI() 
{
    interactor->AddObserver(vtkCommand::KeyPressEvent, [this](vtkObject*, unsigned long, void*) {
        manager.showNext();
        renderWindow->Render();
    });
}