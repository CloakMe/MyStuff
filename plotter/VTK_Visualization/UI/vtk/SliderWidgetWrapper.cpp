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
                                         Axis initialAxis) :
     currentAxis(initialAxis)
{
	m_clipPlane = vtkSmartPointer<vtkPlane>::New();
    // Create slider representation
    sliderRepresentation = vtkSmartPointer<vtkSliderRepresentation2D>::New();
    sliderRepresentation->SetTitleText("Cut Axis");

    // Slider position on screen (customize as needed)
    sliderRepresentation->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
    sliderRepresentation->GetPoint1Coordinate()->SetValue(0.8, 0.1);
    sliderRepresentation->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
    sliderRepresentation->GetPoint2Coordinate()->SetValue(0.95, 0.1);
    // Create slider widget
    sliderWidget = vtkSmartPointer<vtkSliderWidget>::New();
    sliderWidget->SetInteractor(interactor);
    sliderWidget->SetRepresentation(sliderRepresentation);
    sliderWidget->SetAnimationModeToAnimate();
    sliderWidget->EnabledOn();

    // Setup callback
    callback = vtkSmartPointer<SliderCallback>::New();
    callback->parent = this;
    sliderWidget->AddObserver(vtkCommand::InteractionEvent, callback);
    
    m_clipper = vtkSmartPointer<vtkClipDataSet>::New();
}

void SliderWidgetWrapper::SetAxis(Axis newAxis) {
    // Set plane normal based on axis
    double normal[3] = {0,0,0};
    switch (newAxis) {
        case Axis::X: normal[0] = 1.0; break;
        case Axis::Y: normal[1] = 1.0; break;
        case Axis::Z: normal[2] = 1.0; break;
    }
    m_clipPlane->SetNormal(normal);
}

Axis SliderWidgetWrapper::GetAxis() const {
    return currentAxis;
}

void SliderWidgetWrapper::SetValueChangedCallback(std::function<void(double)> cb) {
    userCallback = cb;
}

void SliderWidgetWrapper::SetupClipPlane(
    vtkSmartPointer<vtkDataSet> dataset, 
    vtkSmartPointer<vtkMapper> mapper, 
    Axis currentAxis)
{
	// Get bounds to determine slider range (xMin, xMax)
	double bounds[6];
    dataset->GetBounds(bounds);
    double min = bounds[0];
    double max = bounds[1];
	switch (currentAxis) {
        case Axis::X:
			m_clipPlane->SetOrigin(max, 0.0, 0.0); 
			break;
        case Axis::Y: 
			min = bounds[2]; max = bounds[3];
			m_clipPlane->SetOrigin(0.0, max, 0.0);
			break;
        case Axis::Z: 
			min = bounds[4]; max = bounds[5];
			m_clipPlane->SetOrigin(0.0, 0.0, max); 
			break;
    }
    // Set plane normal based on axis
    SetAxis(currentAxis);
    
    // setup vtkClipDataSet
	m_clipper->SetInputData(dataset); // generic vtkDataSet
    m_clipper->SetClipFunction(m_clipPlane);
    m_clipper->InsideOutOn();
    m_clipper->Update();
    
    mapper->SetInputConnection(m_clipper->GetOutputPort());
    
    // Create slider representation
    sliderRepresentation->SetMinimumValue(min);
    sliderRepresentation->SetMaximumValue(max);
    sliderRepresentation->SetValue(max);
}

void SliderWidgetWrapper::SliderCallback::Execute(vtkObject* caller,
                                                  unsigned long,
                                                  void*)
{
    vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
    if (!sliderWidget || !parent || !parent->m_clipPlane)
        return;

    double value = static_cast<vtkSliderRepresentation*>(sliderWidget->GetRepresentation())->GetValue();

    // Update plane origin based on current axis
    double origin[3] = {0.0, 0.0, 0.0};
    switch (parent->GetAxis()) {
        case Axis::X: origin[0] = value; break;
        case Axis::Y: origin[1] = value; break;
        case Axis::Z: origin[2] = value; break;
    }
    parent->m_clipPlane->SetOrigin(origin);

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
