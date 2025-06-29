#pragma once

#include "IVisualizer.h"
#include "VisualizationFactory.h"
#include "VisuType.h"
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
    VTK_CFDVisualizer();
    
    void Render(std::unique_ptr<AbstractDB> input) override;
    void Change(VisuType displayType) override;
    
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
    VisuType m_visuType;
};

}
