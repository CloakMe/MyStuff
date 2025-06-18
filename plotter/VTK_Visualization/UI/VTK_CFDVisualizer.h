#pragma once

#include "IVisualizer.h"
#include <memory>

namepsace visu
{
    class VTK_CFDVisualizer : public IVisualizer
    {
    public:
        VTK_CFDVisualizer(std::unique_ptr<vtkDataSet> dataset);
        
        void Render(VisuType drawType) override;

    private:
        void setupUI();

        vtkNew<vtkRenderWindow> m_renderWindow;
        vtkNew<vtkRenderer> m_renderer;
        vtkNew<vtkRenderWindowInteractor> m_interactor;
        std::unique_ptr<vtkDataSet> m_dataset;
    };
}