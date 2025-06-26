#pragma once

#include "IVisualizer.h"
#include <memory>
#include <vtkDataSet.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkNew.h>

namespace visu
{
    class VTK_CFDVisualizer : public IVisualizer
    {
    public:
        VTK_CFDVisualizer(VisualizationConfigurator& configurator);
        
        void Render(VisuType drawType) override;

    private:
        void setupUI();

        static void KeyPressCallback(vtkObject* caller, unsigned long eid, void* clientdata, void* calldata) 
        {
            VTK_CFDVisualizer* self = static_cast<VTK_CFDVisualizer*>(clientdata);
            self->OnKeyPress();
        }

        void OnKeyPress();
    
        vtkNew<vtkRenderWindow> m_renderWindow;
        vtkNew<vtkRenderer> m_renderer;
        vtkNew<vtkRenderWindowInteractor> m_interactor;
        vtkSmartPointer<vtkDataSet> m_dataset;
    };
}