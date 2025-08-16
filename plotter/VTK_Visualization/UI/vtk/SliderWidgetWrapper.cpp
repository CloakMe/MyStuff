#include "SliderWidgetWrapper.h"

#include <vtkSliderWidget.h>
#include <vtkRenderWindow.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkClipDataSet.h>
#include <vtkDataSetMapper.h>
#include <vtkPlane.h>
#include <vtkCommand.h>

#include <iostream>
using namespace std;

SliderWidgetWrapper::SliderWidgetWrapper(vtkSmartPointer<vtkRenderWindowInteractor> interactor,
                                         vtkSmartPointer<vtkPlane> clipPlane_,
                                         Axis initialAxis,
                                         double minValue,
                                         double maxValue)
    : clipPlane(clipPlane_), currentAxis(initialAxis)
{
    // Create slider representation
    sliderRepresentation = vtkSmartPointer<vtkSliderRepresentation2D>::New();
    sliderRepresentation->SetTitleText("Cut Axis");

    // Slider position on screen (customize as needed)
    sliderRepresentation->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
    sliderRepresentation->GetPoint1Coordinate()->SetValue(0.8, 0.1);
    sliderRepresentation->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
    sliderRepresentation->GetPoint2Coordinate()->SetValue(0.95, 0.1);

    sliderWidget = vtkSmartPointer<vtkSliderWidget>::New();
    sliderWidget->SetInteractor(interactor);
    sliderWidget->SetRepresentation(sliderRepresentation);
    sliderWidget->SetAnimationModeToAnimate();
    sliderWidget->EnabledOn();

    // Setup callback
    callback = vtkSmartPointer<SliderCallback>::New();
    callback->parent = this;
    sliderWidget->AddObserver(vtkCommand::InteractionEvent, callback);

    UpdateSliderAndPlane();
}

void SliderWidgetWrapper::SetAxis(Axis newAxis) {
    currentAxis = newAxis;
    UpdateSliderAndPlane();
}

Axis SliderWidgetWrapper::GetAxis() const {
    return currentAxis;
}

void SliderWidgetWrapper::SetValueChangedCallback(std::function<void(double)> cb) {
    userCallback = cb;
}

void SliderWidgetWrapper::UpdateSliderAndPlane() {
    // Get current slider value range (can be cached or passed in constructor)

    // Example: you might want to store min/max somewhere; here assume fixed 0-1 for example purpose
    double minVal = 0.0, maxVal = 1.0; // ideally pass real bounds to constructor and store them!

    sliderRepresentation->SetMinimumValue(minVal);
    sliderRepresentation->SetMaximumValue(maxVal);

    // Set initial slider value to minVal for reset
    sliderRepresentation->SetValue(maxVal);

    // Set plane normal based on axis
    double normal[3] = {0,0,0};
    switch (currentAxis) {
        case Axis::X: normal[0] = 1.0; break;
        case Axis::Y: normal[1] = 1.0; break;
        case Axis::Z: normal[2] = 1.0; break;
    }
    clipPlane->SetNormal(normal);

    // Set plane origin position corresponding to minVal (assuming origin coords on axis)
    double origin[3] = {0, 0, 0};
    origin[0] = (currentAxis == Axis::X) ? minVal : 0.0;
    origin[1] = (currentAxis == Axis::Y) ? minVal : 0.0;
    origin[2] = (currentAxis == Axis::Z) ? minVal : 0.0;
    clipPlane->SetOrigin(origin);

    // Request render update if available (optional)

//    if (sliderWidget->GetInteractor()) {
//        sliderWidget->GetInteractor()->GetRenderWindow()->Render();
//    }
}

void SliderWidgetWrapper::SliderCallback::Execute(vtkObject* caller,
                                                  unsigned long,
                                                  void*)
{
    vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
    if (!sliderWidget || !parent || !parent->clipPlane)
        return;

    double value = static_cast<vtkSliderRepresentation*>(sliderWidget->GetRepresentation())->GetValue();

    // Update plane origin based on current axis
    double origin[3] = {0.0, 0.0, 0.0};
    switch (parent->GetAxis()) {
        case Axis::X: origin[0] = value; break;
        case Axis::Y: origin[1] = value; break;
        case Axis::Z: origin[2] = value; break;
    }
    parent->clipPlane->SetOrigin(value, 0.0, 0.0 /*origin*/);

//    if (parent->userCallback) {
//        parent->userCallback(value); // notify external user if needed
//    }

    if (sliderWidget->GetInteractor()) {
        sliderWidget->GetInteractor()->GetRenderWindow()->Render();
        cout << "rendered through interactor" << endl;
    }
//    else
//    {
//        parent->m_RenderWindow->Render();
//        cout << "rendered using public render window" << endl;
//    }
}
