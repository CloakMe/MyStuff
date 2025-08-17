#include "SliderWidgetWrapper.h"

#include <vtkSliderWidget.h>
#include <vtkRenderWindow.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkClipDataSet.h>
#include <vtkDataSetMapper.h>
#include <vtkPlane.h>
#include <vtkCommand.h>
#include <vtkActor.h>

#include <iostream>

using namespace std;
using namespace visu;

SliderWidgetWrapper::SliderWidgetWrapper()
{
    m_clipper = vtkSmartPointer<vtkClipDataSet>::New();
	m_clipPlane = vtkSmartPointer<vtkPlane>::New();
    m_sliderWidget = vtkSmartPointer<vtkSliderWidget>::New();
    
    // Setup m_callback
    m_callback = vtkSmartPointer<SliderCallback>::New();
    m_callback->parent = this;
    m_sliderWidget->AddObserver(vtkCommand::InteractionEvent, m_callback);
    
    m_axis = Axis::X;
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
    m_axis = newAxis;
}

Axis SliderWidgetWrapper::GetAxis() const {
    return m_axis;
}

void SliderWidgetWrapper::SetValueChangedCallback(std::function<void(double)> cb) {
    userCallback = cb;
}

void SliderWidgetWrapper::Initialize(
    vtkSmartPointer<vtkDataSet> dataset,
    vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
    // setup vtkClipDataSet
	m_clipper->SetInputData(dataset); // generic vtkDataSet
    SetupClipPlane(dataset, Axis::X);
    m_clipper->SetClipFunction(m_clipPlane);
    m_clipper->InsideOutOn();
    m_clipper->Update();

    // Get bounds to determine slider range (xMin, xMax)
    double bounds[6];
    dataset->GetBounds(bounds);
    double min = bounds[0];
    double max = bounds[1];
    // Create slider representation
    m_sliderRepresentation = vtkSmartPointer<vtkSliderRepresentation2D>::New();
    m_sliderRepresentation->SetTitleText("Cut Axis");
    m_sliderRepresentation->SetMinimumValue(min);
    m_sliderRepresentation->SetMaximumValue(max);
    m_sliderRepresentation->SetValue(max);
    //m_sliderRepresentation->SetAnimationModeToJump();
     
    // Slider position on screen (customize as needed)
    m_sliderRepresentation->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
    m_sliderRepresentation->GetPoint1Coordinate()->SetValue(0.8, 0.1);
    m_sliderRepresentation->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
    m_sliderRepresentation->GetPoint2Coordinate()->SetValue(0.95, 0.1);
        
    // Create slider widget
    m_sliderWidget->SetInteractor(interactor);
    m_sliderWidget->SetRepresentation(m_sliderRepresentation);
    m_sliderWidget->SetAnimationModeToJump();
    m_sliderWidget->EnabledOn();
}

vtkAlgorithmOutput* SliderWidgetWrapper::GetOutputPort()
{
    return m_clipper->GetOutputPort();
}

void SliderWidgetWrapper::SetupClipPlane(
    vtkSmartPointer<vtkDataSet> dataset,
    Axis newAxis)
{
    // Get bounds to determine slider range (xMin, xMax)
    double bounds[6];
    dataset->GetBounds(bounds);
    double min = bounds[0];
    double max = bounds[1];
	switch (newAxis) {
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
    SetAxis(newAxis);
}

void SliderWidgetWrapper::SliderCallback::Execute(vtkObject* caller,
                                                  unsigned long,
                                                  void*)
{
    if (!parent || !parent->m_clipPlane || !parent->m_sliderWidget)
        return;

    double value = static_cast<vtkSliderRepresentation*>(parent->m_sliderWidget->GetRepresentation())->GetValue();

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

    if (parent->m_sliderWidget->GetInteractor()) {
        parent->m_sliderWidget->GetInteractor()->GetRenderWindow()->Render();
        cout << "rendered through interactor" << endl;
    }
//    else
//    {
//        parent->m_RenderWindow->Render();
//        cout << "rendered using public render window" << endl;
//    }
}
