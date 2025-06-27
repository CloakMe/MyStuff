#include "VTK_CFDVisualizer.h"
#include "VTK_DBWrapper.h"

using namespace visu;
using namespace std;

VTK_CFDVisualizer::VTK_CFDVisualizer()
{
    //renderWindow->AddRenderer(renderer);
    //interactor->SetRenderWindow(m_renderWindow);
    //configurator.configure(manager, dataset);
    setupUI();
}
        
void VTK_CFDVisualizer::Render(std::unique_ptr<AbstractDB> input)
{
    VTK_DBWrapper* vtk_input = static_cast<VTK_DBWrapper*>(input.release());
    m_dataset = (*vtk_input)();
    //========
    // Mapper and actor
    //vtkNew<vtkPolyDataMapper> mapper;
    //mapper->SetInputData(m_dataset);

    //vtkNew<vtkActor> actor;
    //actor->SetMapper(mapper);
    //actor->GetProperty()->SetColor(1, 0, 0); // Explicit red color
    VisualizationFactory factory;
    std::unique_ptr<VisualizationStrategy> visualization = factory.createStrategy(VisuType::Velocity, m_dataset);
    
    //=======
    // Renderer and window
    vtkNew<vtkRenderer> renderer;
    visualization->addToRenderer(renderer);
    //renderer->AddActor(actor);
    renderer->SetBackground(0.2, 0.3, 0.4); // Non-black background
        
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(800, 600);
    renderWindow->SetWindowName("Working VTK Example");

    // Interactor
    vtkNew<vtkRenderWindowInteractor> interactor;
    interactor->SetRenderWindow(renderWindow);

    
    renderWindow->Render();
    interactor->Start();
    
    visualization->removeFromRenderer(renderer);
}

void VTK_CFDVisualizer::setupUI()
{
/*    m_interactor->AddObserver(vtkCommand::KeyPressEvent, [this](vtkObject*, unsigned long, void*) {
        //m_manager.showNext();
        m_renderWindow->Render();
    });*/
}

void VTK_CFDVisualizer::OnKeyPress() 
{
    //manager.showNext();
    //m_renderWindow->Render();
}