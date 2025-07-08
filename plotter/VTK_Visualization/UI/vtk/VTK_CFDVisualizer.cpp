#include "VTK_CFDVisualizer.h"
#include "VTK_DBWrapper.h"
#include "IKeyControlsConfigurator.h"
#include <vtkCallbackCommand.h>
//#include <vtkPointData.h>
//#include <vtkDataArray.h>

using namespace visu;
using namespace std;

VTK_CFDVisualizer::VTK_CFDVisualizer(
    std::unique_ptr<IKeyControlsConfigurator> keyControlsConfigurator, 
    std::unique_ptr<VisualizationFactory> visualizationFactory)
{
    m_visuType = VisuType::Mesh;
    m_keyControlsConfigurator = move(keyControlsConfigurator);
    m_visualizationFactory = move(visualizationFactory);
}
        
void VTK_CFDVisualizer::Render(std::unique_ptr<AbstractDB> input)
{
    VTK_DBWrapper* vtk_input = static_cast<VTK_DBWrapper*>(input.release());
    m_dataset = (*vtk_input)();
    
/*    vtkPointData* pointData = m_dataset->GetPointData();
    int numArrays = pointData->GetNumberOfArrays();

    for (int i = 0; i < numArrays; ++i) {
        vtkDataArray* array = pointData->GetArray(i);
        if (array && array->GetNumberOfComponents() == 3) {
            std::cout << "Vector array with 3 components found: " << array->GetName() << std::endl;
        }else if(array)
            std::cout << "Vector array found: " << array->GetName() << std::endl;
    }*/
 
    Render();
}

void VTK_CFDVisualizer::Render()
{
    if(m_dataset == nullptr)
        return;
    
    // vtk Actor and Mapper
    std::unique_ptr<VisualizationStrategy> visualization = m_visualizationFactory->createStrategy(m_visuType, m_dataset);
    if(visualization.get() == nullptr)
        return;
    // vtk Renderer and Window
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    visualization->addToRenderer(renderer);
    //renderer->AddActor(actor);
    renderer->SetBackground(0.2, 0.3, 0.4); // Non-black background
        
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(800, 600);
    renderWindow->SetWindowName("Working VTK Example");

    // vtk Interactor
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
	    vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);
    
    // Callback
    vtkSmartPointer<vtkCallbackCommand> keypressCallback = 
	    vtkSmartPointer<vtkCallbackCommand>::New();
    keypressCallback->SetClientData(this);
    keypressCallback->SetCallback(KeyPressCallback);
    interactor->AddObserver(vtkCommand::KeyPressEvent, keypressCallback.GetPointer());
    
    
    renderWindow->Render();
    interactor->Initialize();
    interactor->Start();
    
    cout << "Successfully ended the render method!" << endl;
    //visualization->removeFromRenderer(renderer);
}

void VTK_CFDVisualizer::setupUI()
{
/*    m_interactor->AddObserver(vtkCommand::KeyPressEvent, [this](vtkObject*, unsigned long, void*) {
        //m_manager.showNext();
        m_renderWindow->Render();
    });*/
}

void VTK_CFDVisualizer::OnKeyPress(vtkObject* caller, long unsigned int eventId, void* callData) 
{
    auto interactor = static_cast<vtkRenderWindowInteractor*>(caller);
    std::string key = interactor->GetKeySym();
    
    if (key == m_keyControlsConfigurator->getKeyVisuChanger()) 
    {
        // Close the render window
        interactor->GetRenderWindow()->Finalize();

        // Stop the interactor event loop
        interactor->TerminateApp();
        if(m_visuType == VisuType::Velocity)
        {
            m_visuType = VisuType::Mesh;
            Render();
        }
        else if(m_visuType == VisuType::Mesh)
        {
            m_visuType = VisuType::Pressure;
            Render();
        }
        else if(m_visuType == VisuType::Pressure)
        {
            m_visuType = VisuType::Velocity;
            Render();
        }
    }
}