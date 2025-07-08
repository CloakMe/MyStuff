#pragma once

#include "IVisualizer.h"
#include "VisualizationFactory.h"
#include "VisuType.h"
#include "IConfigurator.h"
#include <memory>
#include <vtkDataSet.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkNew.h>
#include <vtkActor.h>


namespace visu
{
class VTK_CFDVisualizer : public IVisualizer
{
public:
    VTK_CFDVisualizer(const IConfigurator& configurator, std::unique_ptr<VisualizationFactory> visualizationFactory);
    
    void Render(std::unique_ptr<AbstractDB> input) override;
    
private:
    void Render();
    
    void setupUI();

    static void KeyPressCallback(vtkObject* caller, unsigned long eventId, void* clientdata, void* calldata) 
    {
        VTK_CFDVisualizer* self = static_cast<VTK_CFDVisualizer*>(clientdata);
        self->OnKeyPress(caller, eventId, calldata);
    }

    void OnKeyPress(vtkObject* caller, long unsigned int eventId, void* callData);

    vtkSmartPointer<vtkDataSet> m_dataset;
    const IConfigurator& m_configurator;
    std::unique_ptr<VisualizationFactory> m_visualizationFactory;
    VisuType m_visuType;
    //vtk visualization state
    bool m_initialized;
    vtkSmartPointer<vtkRenderWindow> m_renderWindow;
    vtkSmartPointer<vtkRenderer> m_renderer;
    vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;
};

}
