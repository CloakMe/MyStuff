#pragma once

#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPlane.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>
#include <functional>

enum class Axis { X, Y, Z };

class SliderWidgetWrapper {
public:
    // Constructor: interactor, clipPlane, axis selection, bounds for slider
    SliderWidgetWrapper(vtkSmartPointer<vtkRenderWindowInteractor> interactor,
                        vtkSmartPointer<vtkPlane> clipPlane,
                        Axis initialAxis,
                        double minValue,
                        double maxValue);

    // Change the axis - update internal state, plane normal, slider range
    void SetAxis(Axis newAxis);

    // Get current axis
    Axis GetAxis() const;

    // Get the slider widget (for attaching or customizations)
    vtkSmartPointer<vtkSliderWidget> GetSliderWidget() const;

    // Set callback for slider value changes (optional)
    void SetValueChangedCallback(std::function<void(double)> callback);

private:
    vtkSmartPointer<vtkSliderWidget> sliderWidget;
    vtkSmartPointer<vtkPlane> clipPlane;
    vtkSmartPointer<vtkSliderRepresentation2D> sliderRepresentation;
    
    Axis currentAxis;

    // Callback class listens to slider interaction
    class SliderCallback : public vtkCommand {
    public:
        static SliderCallback* New() { return new SliderCallback; }
        void Execute(vtkObject* caller, unsigned long eventId, void* callData) override;

        SliderWidgetWrapper* parent = nullptr;
    };

    vtkSmartPointer<SliderCallback> callback;

    // Internal helper to update slider range & plane normal based on axis
    void UpdateSliderAndPlane();

    // Optional user callback to notify axis value changes
    std::function<void(double)> userCallback;
};
