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
    int idx = static_cast<int>(newAxis);
    normal[idx] = 1.0;
    m_clipPlane->SetNormal(normal);
    m_axis = newAxis;
}

Axis SliderWidgetWrapper::GetAxis() const {
    return m_axis;
}

void SliderWidgetWrapper::SetValueChangedCallback(std::function<void(double)> cb) {
    userCallback = cb;
}

void SliderWidgetWrapper::Update(
    vtkSmartPointer<vtkDataSet> dataset,
    vtkSmartPointer<vtkRenderWindowInteractor> interactor,
    Axis axis)
{
    // setup vtkClipDataSet
    m_clipper->SetInputData(dataset); // generic vtkDataSet
    SetupClipPlane(dataset, axis);
    m_clipper->SetClipFunction(m_clipPlane);
    m_clipper->InsideOutOn();
    m_clipper->Update();
    
    // Get bounds to determine slider range (xMin, xMax)
    double bounds[6];
    dataset->GetBounds(bounds);
    
    // Maps axis to bounds indices for min and max
    int minIndex[] = {0, 2, 4};
    int maxIndex[] = {1, 3, 5};
    std::string axisLabels = "XYZ";

    int idx = static_cast<int>(axis);
    double min = bounds[minIndex[idx]];
    double max = bounds[maxIndex[idx]];

    std::string sliderLabel = "Cut Axis: ";
    sliderLabel += axisLabels[idx];

    // Create slider representation
    m_sliderRepresentation = vtkSmartPointer<vtkSliderRepresentation2D>::New();
    m_sliderRepresentation->SetTitleText(sliderLabel.c_str());
    m_sliderRepresentation->SetMinimumValue(min);
    m_sliderRepresentation->SetMaximumValue(max);
    m_sliderRepresentation->SetValue(max);

    m_sliderRepresentation->SetTubeWidth(0.025 /*percentage*/);
    m_sliderRepresentation->SetSliderWidth(0.05 /*percentage*/);
     
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
    // Maps axis to bounds indices for min and max
    int minIndex[] = {0, 2, 4};
    int maxIndex[] = {1, 3, 5};

    int idx = static_cast<int>(newAxis);
    double min = bounds[minIndex[idx]];
    double max = bounds[maxIndex[idx]];
    // Maps axis to origin max
    double origin[3] = {0.0, 0.0, 0.0};
    origin[idx] = max;
    m_clipPlane->SetOrigin(origin);
    
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
    int idx = static_cast<int>(parent->GetAxis());
    origin[idx] = value;
    parent->m_clipPlane->SetOrigin(origin);

//    if (parent->userCallback) {
//        parent->userCallback(value); // notify external user if needed
//    }

    if (parent->m_sliderWidget->GetInteractor()) {
        parent->m_sliderWidget->GetInteractor()->GetRenderWindow()->Render();
        cout << "rendered through interactor" << endl;
    }
    else
    {
        cout << "SliderWidgetWrapper: Interactor not set or not currently present!" << endl;
    }
}
