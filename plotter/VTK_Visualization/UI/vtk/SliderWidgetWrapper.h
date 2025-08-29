#pragma once

#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPlane.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkClipDataSet.h>
#include <vtkMapper.h>
#include <vtkDataSet.h>
#include <vtkAlgorithmOutput.h>
#include <functional>

namespace visu{
    
enum class Axis { X, Y, Z };

class SliderWidgetWrapper {
public:
    // Constructor: interactor, clipPlane, axis selection, bounds for slider
    SliderWidgetWrapper();

    // Change the axis - update internal state, plane normal, slider range
    void SetAxis(Axis newAxis);
    
    // Get current axis
    Axis GetAxis() const;
    
    // Set m_callback for slider value changes (optional)
    void SetValueChangedCallback(std::function<void(double)> m_callback);
    
	// setup clip axis and cut value
    void SetupClipPlane(vtkSmartPointer<vtkDataSet> dataset, Axis newAxis);
    
    void Update(
        vtkSmartPointer<vtkDataSet> dataset,
        vtkSmartPointer<vtkRenderWindowInteractor> interactor,
        Axis axis);
        
    vtkAlgorithmOutput* GetOutputPort();
        
private:
    vtkSmartPointer<vtkSliderWidget> m_sliderWidget;
    vtkSmartPointer<vtkPlane> m_clipPlane;
    vtkSmartPointer<vtkSliderRepresentation2D> m_sliderRepresentation;
    vtkSmartPointer<vtkClipDataSet> m_clipper;
    Axis m_axis;
    
    // Optional user m_callback to notify axis value changes
    std::function<void(double)> userCallback;
    
    // Callback class listens to slider interaction
    class SliderCallback : public vtkCommand {
    public:
        static SliderCallback* New() { return new SliderCallback; }
        void Execute(vtkObject* caller, unsigned long eventId, void* callData) override;

        SliderWidgetWrapper* parent = nullptr;
    };
    vtkSmartPointer<SliderCallback> m_callback;
};

}
