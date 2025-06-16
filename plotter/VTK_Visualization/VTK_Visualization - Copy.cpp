// VTK_Visualization.cpp : Defines the entry point for the application.
//

#include "VTK_Visualization.h"

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>          // Example geometry source
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkCommand.h>
#include <vtkProperty.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCallbackCommand.h>

// Callback to update the cutter plane position based on slider
class SliderCallbackX : public vtkCommand
{
public:
    static SliderCallbackX* New() { return new SliderCallbackX; }
    void Execute(vtkObject* caller, unsigned long, void*) override
    {
        vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
        double value = static_cast<vtkSliderRepresentation*>(sliderWidget->GetRepresentation())->GetValue();
        this->Plane->SetOrigin(value, 0, 0);
    }
    vtkPlane* Plane = nullptr;
};

class SliderCallbackY : public vtkCommand
{
public:
    static SliderCallbackY* New() { return new SliderCallbackY; }
    void Execute(vtkObject* caller, unsigned long, void*) override
    {
        vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
        double value = static_cast<vtkSliderRepresentation*>(sliderWidget->GetRepresentation())->GetValue();
        this->Plane->SetOrigin(0, value, 0);
    }
    vtkPlane* Plane = nullptr;
};

class SliderCallbackZ : public vtkCommand
{
public:
    static SliderCallbackZ* New() { return new SliderCallbackZ; }
    void Execute(vtkObject* caller, unsigned long, void*) override
    {
        vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
        double value = static_cast<vtkSliderRepresentation*>(sliderWidget->GetRepresentation())->GetValue();
        this->Plane->SetOrigin(0, 0, value);
    }
    vtkPlane* Plane = nullptr;
};

//int main(int, char* [])
//{
//    // Create example geometry (replace with mesh reader if needed)
//    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
//    sphereSource->SetRadius(5.0);
//    sphereSource->Update();
//
//    vtkSmartPointer<vtkPolyData> polyData = sphereSource->GetOutput();
//
//    // Create a plane for cutting
//    vtkSmartPointer<vtkPlane> cutPlane = vtkSmartPointer<vtkPlane>::New();
//    cutPlane->SetOrigin(0, 0, 0);
//    cutPlane->SetNormal(1, 0, 0); // Initially X direction
//
//    // Cutter to generate cross section
//    vtkSmartPointer<vtkCutter> cutter = vtkSmartPointer<vtkCutter>::New();
//    cutter->SetCutFunction(cutPlane);
//    cutter->SetInputData(polyData);
//    cutter->Update();
//
//    // Mapper and actor for the cut section
//    vtkSmartPointer<vtkPolyDataMapper> cutMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    cutMapper->SetInputConnection(cutter->GetOutputPort());
//
//    vtkSmartPointer<vtkActor> cutActor = vtkSmartPointer<vtkActor>::New();
//    cutActor->SetMapper(cutMapper);
//    cutActor->GetProperty()->SetColor(1, 0, 0); // Red cross section
//
//    // Mapper and actor for original geometry (wireframe)
//    vtkSmartPointer<vtkPolyDataMapper> originalMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    originalMapper->SetInputData(polyData);
//
//    vtkSmartPointer<vtkActor> originalActor = vtkSmartPointer<vtkActor>::New();
//    originalActor->SetMapper(originalMapper);
//    originalActor->GetProperty()->SetRepresentationToWireframe();
//    originalActor->GetProperty()->SetColor(0, 0, 1); // Blue wireframe
//
//    // Renderer, window and interactor
//    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
//    renderer->AddActor(originalActor);
//    renderer->AddActor(cutActor);
//    renderer->SetBackground(0.1, 0.2, 0.3);
//
//    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
//    renWin->AddRenderer(renderer);
//    renWin->SetSize(800, 600);
//
//    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    iren->SetRenderWindow(renWin);
//
//    // Slider setup helper function
//    auto createSlider = [&](double min, double max, double value, double x1, double y1, double x2, double y2) {
//        vtkSmartPointer<vtkSliderRepresentation2D> sliderRep = vtkSmartPointer<vtkSliderRepresentation2D>::New();
//        sliderRep->SetMinimumValue(min);
//        sliderRep->SetMaximumValue(max);
//        sliderRep->SetValue(value);
//        sliderRep->SetTitleText("Slice");
//        sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
//        sliderRep->GetPoint1Coordinate()->SetValue(x1, y1);
//        sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
//        sliderRep->GetPoint2Coordinate()->SetValue(x2, y2);
//        sliderRep->SetSliderLength(0.02);
//        sliderRep->SetSliderWidth(0.03);
//        sliderRep->SetEndCapLength(0.01);
//        sliderRep->SetEndCapWidth(0.03);
//        sliderRep->SetTubeWidth(0.005);
//        sliderRep->SetLabelFormat("%0.2f");
//        sliderRep->SetTitleHeight(0.02);
//        sliderRep->SetLabelHeight(0.02);
//        return sliderRep;
//    };
//
//    // Create sliders for X, Y, Z
//    vtkSmartPointer<vtkSliderRepresentation2D> sliderRepX = createSlider(-5, 5, 0, 0.1, 0.1, 0.4, 0.1);
//    vtkSmartPointer<vtkSliderRepresentation2D> sliderRepY = createSlider(-5, 5, 0, 0.1, 0.2, 0.4, 0.2);
//    vtkSmartPointer<vtkSliderRepresentation2D> sliderRepZ = createSlider(-5, 5, 0, 0.1, 0.3, 0.4, 0.3);
//
//    vtkSmartPointer<vtkSliderWidget> sliderWidgetX = vtkSmartPointer<vtkSliderWidget>::New();
//    sliderWidgetX->SetInteractor(iren);
//    sliderWidgetX->SetRepresentation(sliderRepX);
//    sliderWidgetX->SetAnimationModeToAnimate();
//    sliderWidgetX->EnabledOn();
//
//    vtkSmartPointer<vtkSliderWidget> sliderWidgetY = vtkSmartPointer<vtkSliderWidget>::New();
//    sliderWidgetY->SetInteractor(iren);
//    sliderWidgetY->SetRepresentation(sliderRepY);
//    sliderWidgetY->SetAnimationModeToAnimate();
//    sliderWidgetY->EnabledOff();
//
//    vtkSmartPointer<vtkSliderWidget> sliderWidgetZ = vtkSmartPointer<vtkSliderWidget>::New();
//    sliderWidgetZ->SetInteractor(iren);
//    sliderWidgetZ->SetRepresentation(sliderRepZ);
//    sliderWidgetZ->SetAnimationModeToAnimate();
//    sliderWidgetZ->EnabledOff();
//
//    // Setup callbacks for sliders
//    vtkSmartPointer<SliderCallbackX> callbackX = vtkSmartPointer<SliderCallbackX>::New();
//    callbackX->Plane = cutPlane;
//    sliderWidgetX->AddObserver(vtkCommand::InteractionEvent, callbackX);
//
//    vtkSmartPointer<SliderCallbackY> callbackY = vtkSmartPointer<SliderCallbackY>::New();
//    callbackY->Plane = cutPlane;
//    sliderWidgetY->AddObserver(vtkCommand::InteractionEvent, callbackY);
//
//    vtkSmartPointer<SliderCallbackZ> callbackZ = vtkSmartPointer<SliderCallbackZ>::New();
//    callbackZ->Plane = cutPlane;
//    sliderWidgetZ->AddObserver(vtkCommand::InteractionEvent, callbackZ);
//
//    // Logic to enable only one slider at a time (simple example)
//    // Here we just enable slider X; you can add keypress or GUI buttons to switch active slider
//
//    // Start rendering
//    renWin->Render();
//    iren->Initialize();
//    iren->Start();
//
//    return EXIT_SUCCESS;
//}


// Callback for slider to move the plane
class SliderCallback : public vtkCommand {
public:
    static SliderCallback* New() { return new SliderCallback; }
    void Execute(vtkObject* caller, unsigned long, void*) override {
        vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
        double value = static_cast<vtkSliderRepresentation*>(sliderWidget->GetRepresentation())->GetValue();
        if (Axis == 0)
            Plane->SetOrigin(value, Plane->GetOrigin()[1], Plane->GetOrigin()[2]);
        else if (Axis == 1)
            Plane->SetOrigin(Plane->GetOrigin()[0], value, Plane->GetOrigin()[2]);
        else
            Plane->SetOrigin(Plane->GetOrigin()[0], Plane->GetOrigin()[1], value);
    }
    vtkPlane* Plane = nullptr;
    int Axis = 0; // 0=X, 1=Y, 2=Z
};

// Custom interactor style to switch modes
class CustomInteractorStyle : public vtkInteractorStyleTrackballCamera {
public:
    static CustomInteractorStyle* New() { return new CustomInteractorStyle; }

    vtkRenderer* Renderer = nullptr;
    vtkActor* SphereActor = nullptr;
    vtkActor* CutActor = nullptr;
    vtkActor* WireActor = nullptr;
    vtkSliderWidget* SliderX = nullptr;
    vtkSliderWidget* SliderY = nullptr;
    vtkSliderWidget* SliderZ = nullptr;

    bool ShowSliders = false;

    void OnKeyPress() override {
        std::string key = this->GetInteractor()->GetKeySym();
        if (key == "s") {
            // Show only the sphere
            ShowSliders = false;
            Renderer->RemoveAllViewProps();
            Renderer->AddActor(SphereActor);
            if (SliderX) SliderX->EnabledOff();
            if (SliderY) SliderY->EnabledOff();
            if (SliderZ) SliderZ->EnabledOff();
            this->GetInteractor()->GetRenderWindow()->Render();
        }
        else if (key == "c") {
            // Show cut and sliders
            ShowSliders = true;
            Renderer->RemoveAllViewProps();
            Renderer->AddActor(WireActor);
            Renderer->AddActor(CutActor);
            if (SliderX) SliderX->EnabledOn();
            if (SliderY) SliderY->EnabledOn();
            if (SliderZ) SliderZ->EnabledOn();
            this->GetInteractor()->GetRenderWindow()->Render();
        }
        // Call parent
        vtkInteractorStyleTrackballCamera::OnKeyPress();
    }
};

//int main(int, char* []) {
//    // Sphere source
//    auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
//    sphereSource->SetRadius(5.0);
//    sphereSource->Update();
//
//    // Wireframe actor (for 'cut' mode)
//    auto wireMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    wireMapper->SetInputConnection(sphereSource->GetOutputPort());
//    auto wireActor = vtkSmartPointer<vtkActor>::New();
//    wireActor->SetMapper(wireMapper);
//    wireActor->GetProperty()->SetRepresentationToWireframe();
//    wireActor->GetProperty()->SetColor(0, 0, 1);
//
//    // Solid sphere actor (for 'simple' mode)
//    auto sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
//    auto sphereActor = vtkSmartPointer<vtkActor>::New();
//    sphereActor->SetMapper(sphereMapper);
//    sphereActor->GetProperty()->SetColor(0.2, 0.8, 0.3);
//
//    // Cutter setup (for 'cut' mode)
//    auto plane = vtkSmartPointer<vtkPlane>::New();
//    plane->SetOrigin(0, 0, 0);
//    plane->SetNormal(1, 0, 0);
//
//    auto cutter = vtkSmartPointer<vtkCutter>::New();
//    cutter->SetCutFunction(plane);
//    cutter->SetInputConnection(sphereSource->GetOutputPort());
//    cutter->Update();
//
//    auto cutMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    cutMapper->SetInputConnection(cutter->GetOutputPort());
//    auto cutActor = vtkSmartPointer<vtkActor>::New();
//    cutActor->SetMapper(cutMapper);
//    cutActor->GetProperty()->SetColor(1, 0, 0);
//
//    // Renderer, window, interactor
//    auto renderer = vtkSmartPointer<vtkRenderer>::New();
//    renderer->AddActor(sphereActor); // Start with simple sphere
//    renderer->SetBackground(0.1, 0.2, 0.3);
//
//    auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renderWindow->AddRenderer(renderer);
//    renderWindow->SetSize(800, 600);
//
//    auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    interactor->SetRenderWindow(renderWindow);
//
//    // Sliders (for 'cut' mode)
//    auto createSlider = [&](int axis, double min, double max, double value, double x1, double y1, double x2, double y2) {
//        auto sliderRep = vtkSmartPointer<vtkSliderRepresentation2D>::New();
//        sliderRep->SetMinimumValue(min);
//        sliderRep->SetMaximumValue(max);
//        sliderRep->SetValue(value);
//        sliderRep->SetTitleText(axis == 0 ? "X" : axis == 1 ? "Y" : "Z");
//        sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
//        sliderRep->GetPoint1Coordinate()->SetValue(x1, y1);
//        sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
//        sliderRep->GetPoint2Coordinate()->SetValue(x2, y2);
//        sliderRep->SetSliderLength(0.02);
//        sliderRep->SetSliderWidth(0.03);
//        sliderRep->SetEndCapLength(0.01);
//        sliderRep->SetEndCapWidth(0.03);
//        sliderRep->SetTubeWidth(0.005);
//        sliderRep->SetLabelFormat("%0.2f");
//        sliderRep->SetTitleHeight(0.02);
//        sliderRep->SetLabelHeight(0.02);
//
//        auto sliderWidget = vtkSmartPointer<vtkSliderWidget>::New();
//        sliderWidget->SetInteractor(interactor);
//        sliderWidget->SetRepresentation(sliderRep);
//        sliderWidget->SetAnimationModeToAnimate();
//        sliderWidget->EnabledOff();
//
//        auto callback = vtkSmartPointer<SliderCallback>::New();
//        callback->Plane = plane;
//        callback->Axis = axis;
//        sliderWidget->AddObserver(vtkCommand::InteractionEvent, callback);
//
//        return sliderWidget;
//    };
//
//    auto sliderX = createSlider(0, -5, 5, 0, 0.1, 0.1, 0.4, 0.1);
//    auto sliderY = createSlider(1, -5, 5, 0, 0.1, 0.2, 0.4, 0.2);
//    auto sliderZ = createSlider(2, -5, 5, 0, 0.1, 0.3, 0.4, 0.3);
//
//    // Custom interactor style
//    auto style = vtkSmartPointer<CustomInteractorStyle>::New();
//    style->Renderer = renderer;
//    style->SphereActor = sphereActor;
//    style->CutActor = cutActor;
//    style->WireActor = wireActor;
//    style->SliderX = sliderX;
//    style->SliderY = sliderY;
//    style->SliderZ = sliderZ;
//
//    interactor->SetInteractorStyle(style);
//
//    // Instructions
//    std::cout << "Press 's' for simple sphere, 'c' for sphere with cut and sliders." << std::endl;
//
//    renderWindow->Render();
//    interactor->Initialize();
//    interactor->Start();
//
//    return 0;
//}


int main() {
    auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetRadius(5.0);
    sphereSource->Update();

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0.1, 0.2, 0.3);
    renderer->ResetCamera();

    auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(800, 600);

    auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    renderWindow->Render();
    std::cout << "OpenGL info:" << std::endl;
    std::cout << "  VTK OpenGL version: " << renderWindow->ReportCapabilities() << std::endl;
    interactor->Initialize();
    interactor->Start();

    return 0;
}
