#include "VTK_CFDVisualizer.h"
#include "IConfigurator.h"
#include "VTK_DBWrapper.h"
#include "SliderWidgetWrapper.h"
#include "vtkClipDataSet.h"

#include <vtkActor.h>
#include <vtkCallbackCommand.h>
#include <memory>

using namespace visu;
using namespace std;

VTK_CFDVisualizer::VTK_CFDVisualizer(const IConfigurator& configurator,
                                     std::unique_ptr<VisualizationFactory> visualizationFactory)
                                     : m_configurator(configurator)
{
    m_visuType = VisuType::Mesh;
    m_visualizationFactory = move(visualizationFactory);
    m_initialized = false;
}

void VTK_CFDVisualizer::Render(std::unique_ptr<AbstractDB> input)
{
    VTK_DBWrapper* vtk_input = static_cast<VTK_DBWrapper*>(input.release());
    m_dataset = (*vtk_input)();

    Render();
}

void VTK_CFDVisualizer::Render()
{
    if(m_dataset == nullptr)
        return;

    cout << "Successfully started the render method!" << endl;

    std::unique_ptr<VisualizationStrategy> visualization = m_visualizationFactory->createStrategy(m_visuType);
    if(visualization.get() == nullptr)
        return;
    if(!m_initialized) 
    {
        cout << "Initialize render window, renderer and interactor!" << endl;
        m_renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
        m_renderer = vtkSmartPointer<vtkRenderer>::New();
        m_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    }
    // vtk Actor and Mapper
    vtkSmartPointer<vtkActor> actor = visualization->createActors(m_dataset);
    cout << "Successfully created actor and mapper!" << endl;
       
   
    // vtk Renderer and Window

    m_renderer->AddActor(actor);
    vector<double> rgb_color = m_configurator.GetBackgroundColor();
    if(rgb_color.size() == 3)
        m_renderer->SetBackground(rgb_color[0], rgb_color[1], rgb_color[2]); // Non-black background

    m_renderWindow->AddRenderer(m_renderer);
    vector<int> windowSize = m_configurator.GetWindowSize();
    if(windowSize.size() == 2)
        m_renderWindow->SetSize(windowSize[0], windowSize[1]);
    m_renderWindow->SetWindowName(m_configurator.GetWindowTitle().c_str());
    cout << "Successfully created Window properties!" << endl;

    // vtk Interactor
    m_interactor->SetRenderWindow(m_renderWindow);

    m_renderWindow->Render();
    cout << "Successfully rendered the window!" << endl;
    if(!m_initialized) {
        // Get bounds to determine slider range (xMin, xMax)
        double bounds[6];
        m_dataset->GetBounds(bounds);
        double xMin = bounds[0];
        double xMax = bounds[1];

        // Create clipping plane with normal along +X axis
        vtkSmartPointer<vtkPlane> clipPlane = vtkSmartPointer<vtkPlane>::New();
        clipPlane->SetNormal(1.0, 0.0, 0.0);
        clipPlane->SetOrigin(xMax, 0.0, 0.0);

        vtkSmartPointer<vtkClipDataSet> clipper = vtkSmartPointer<vtkClipDataSet>::New();
        clipper->SetInputData(m_dataset); // generic vtkDataSet
        clipper->SetClipFunction(clipPlane);
        clipper->InsideOutOn();
        clipper->Update();
        m_slider = make_unique<SliderWidgetWrapper>(m_interactor, clipPlane, Axis::X, xMin, xMax);
        
        // Callback
        vtkSmartPointer<vtkCallbackCommand> keypressCallback = vtkSmartPointer<vtkCallbackCommand>::New();
        keypressCallback->SetClientData(this);
        keypressCallback->SetCallback(KeyPressCallback);
        m_interactor->AddObserver(vtkCommand::KeyPressEvent, keypressCallback.GetPointer());
        m_initialized = true;
        cout << "Successfully added Callback Observer!" << endl;
        // Init and start interactor
        m_interactor->Initialize();
        m_interactor->Start();
    }    
    
    cout << "Successfully ended the render method!" << endl;
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

    if(key == m_configurator.GetVisualizationValue()) 
    {
        m_renderer->RemoveAllViewProps();

        if(m_visuType == VisuType::Velocity) {
            m_visuType = VisuType::Mesh;
            Render();
        } else if(m_visuType == VisuType::Mesh) {
            m_visuType = VisuType::Pressure;
            Render();
        } else if(m_visuType == VisuType::Pressure) {
            m_visuType = VisuType::Velocity;
            Render();
        }
    }
}