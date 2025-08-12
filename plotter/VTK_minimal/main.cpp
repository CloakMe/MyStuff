#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2); // Explicitly initialize OpenGL2 backend
VTK_MODULE_INIT(vtkInteractionStyle); // Required for interactor

#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTriangle.h>
#include <vtkPolyData.h>
#include <vtkTetra.h>
#include <vtkPyramid.h>
#include <vtkUnstructuredGrid.h>
//#include <vtkNamedColors.h>
#include <vtkProperty.h>



int main2() {
    // Verify OpenGL support
    vtkSmartPointer<vtkRenderWindow> testWindow = vtkSmartPointer<vtkRenderWindow>::New();
    testWindow->Render();
    if (!testWindow->SupportsOpenGL()) {
        std::cerr << "ERROR: OpenGL not supported!" << std::endl;
        return EXIT_FAILURE;
    }

    // Create triangle geometry
    vtkNew<vtkPoints> points;
    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(1.0, 0.0, 0.0);
    points->InsertNextPoint(0.5, 1.0, 0.0);

    vtkNew<vtkTriangle> triangle;
    triangle->GetPointIds()->SetId(0, 0);
    triangle->GetPointIds()->SetId(1, 1);
    triangle->GetPointIds()->SetId(2, 2);

    vtkNew<vtkCellArray> cells;
    cells->InsertNextCell(triangle);

    vtkNew<vtkPolyData> polyData;
    polyData->SetPoints(points);
    polyData->SetPolys(cells);

    // Mapper and actor
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputData(polyData);

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1, 0, 0); // Explicit red color

    // Renderer and window
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->SetBackground(0.2, 0.3, 0.4); // Non-black background

    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(800, 600);
    renderWindow->SetWindowName("Working VTK Example");

    // Interactor
    vtkNew<vtkRenderWindowInteractor> interactor;
    interactor->SetRenderWindow(renderWindow);

    // Diagnostic output
    std::cout << "OpenGL version: " << renderWindow->ReportCapabilities() << std::endl;
    std::cout << "Renderer: " << renderer->GetClassName() << std::endl;

    // Render
    renderWindow->Render();
    interactor->Start();

    return EXIT_SUCCESS;
}


#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkClipDataSet.h>
#include <vtkDataSetMapper.h>
#include <vtkPlane.h>
#include <vtkHexahedron.h>

// Callback to update clipping plane origin on slider interaction
class SliderCallback : public vtkCommand
{
public:
    static SliderCallback* New() {
        return new SliderCallback;
    }
    void Execute(vtkObject* caller, unsigned long, void*) override
    {
        vtkSliderWidget* sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
        double value = static_cast<vtkSliderRepresentation*>(sliderWidget->GetRepresentation())->GetValue();

        // Update the plane origin to move clipping plane at slider value along x-axis
        // Plane normal pointing along +x means clipping everything with x > slider_value
        m_Plane->SetOrigin(value, 0.0, 0.0);

        // Request render window to re-render
        m_RenderWindow->Render();
    }

    vtkPlane* m_Plane = nullptr;
    vtkRenderWindow* m_RenderWindow = nullptr;
};

int main()
{
	// Create points for two connected parallelepipeds
    auto points = vtkSmartPointer<vtkPoints>::New();

    // Coordinates of 12 points for two hexahedrons sharing a face along the x-axis
    points->InsertNextPoint(0.0, 0.0, 0.0);  // 0
    points->InsertNextPoint(1.0, 0.0, 0.0);  // 1
    points->InsertNextPoint(1.0, 1.0, 0.0);  // 2
    points->InsertNextPoint(0.0, 1.0, 0.0);  // 3
    points->InsertNextPoint(0.0, 0.0, 1.0);  // 4
    points->InsertNextPoint(1.0, 0.0, 1.0);  // 5
    points->InsertNextPoint(1.0, 1.0, 1.0);  // 6
    points->InsertNextPoint(0.0, 1.0, 1.0);  // 7

    // Second hexahedron points, shifted by 1 along x-axis sharing one face with first hexahedron
    points->InsertNextPoint(1.0, 0.0, 0.0);  // 8 (same as 1)
    points->InsertNextPoint(2.0, 0.0, 0.0);  // 9
    points->InsertNextPoint(2.0, 1.0, 0.0);  // 10
    points->InsertNextPoint(1.0, 1.0, 0.0);  // 11 (same as 2)
    points->InsertNextPoint(1.0, 0.0, 1.0);  // 12 (same as 5)
    points->InsertNextPoint(2.0, 0.0, 1.0);  // 13
    points->InsertNextPoint(2.0, 1.0, 1.0);  // 14
    points->InsertNextPoint(1.0, 1.0, 1.0);  // 15 (same as 6)

    // Create the unstructured grid
    auto ugrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    ugrid->SetPoints(points);

    // First hexahedron
    auto hex1 = vtkSmartPointer<vtkHexahedron>::New();
    hex1->GetPointIds()->SetId(0, 0);
    hex1->GetPointIds()->SetId(1, 1);
    hex1->GetPointIds()->SetId(2, 2);
    hex1->GetPointIds()->SetId(3, 3);
    hex1->GetPointIds()->SetId(4, 4);
    hex1->GetPointIds()->SetId(5, 5);
    hex1->GetPointIds()->SetId(6, 6);
    hex1->GetPointIds()->SetId(7, 7);

    ugrid->InsertNextCell(hex1->GetCellType(), hex1->GetPointIds());

    // Second hexahedron
    auto hex2 = vtkSmartPointer<vtkHexahedron>::New();
    // Note: points 8,11,12,15 are duplicated versions of points 1,2,5,6
    hex2->GetPointIds()->SetId(0, 8);
    hex2->GetPointIds()->SetId(1, 9);
    hex2->GetPointIds()->SetId(2,10);
    hex2->GetPointIds()->SetId(3,11);
    hex2->GetPointIds()->SetId(4,12);
    hex2->GetPointIds()->SetId(5,13);
    hex2->GetPointIds()->SetId(6,14);
    hex2->GetPointIds()->SetId(7,15);

    ugrid->InsertNextCell(hex2->GetCellType(), hex2->GetPointIds());

    // Now ugrid contains the two hexahedron cells forming a parallelepiped split in two parts.

    // (Optional) You can write or visualize this grid using VTK rendering pipeline
	
    // Assume you have some vtkPolyData* inputData representing the object
    vtkSmartPointer<vtkDataSet> inputData = ugrid; // Your 3D object

    // Get bounds to determine slider range (xMin, xMax)
    double bounds[6];
    inputData->GetBounds(bounds);
    double xMin = bounds[0];
    double xMax = bounds[1];

    // Create clipping plane with normal along +X axis
    vtkSmartPointer<vtkPlane> clipPlane = vtkSmartPointer<vtkPlane>::New();
	clipPlane->SetNormal(1.0, 0.0, 0.0);
	clipPlane->SetOrigin(xMin, 0.0, 0.0);

	vtkSmartPointer<vtkClipDataSet> clipper = vtkSmartPointer<vtkClipDataSet>::New();
	clipper->SetInputData(inputData); // generic vtkDataSet
	clipper->SetClipFunction(clipPlane);
	clipper->InsideOutOn();
	clipper->Update();

	// Use vtkDataSetMapper for generic dataset
	vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(clipper->GetOutputPort());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

    // Renderer, render window and interactor
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0.2, 0.3, 0.4);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(800, 600);

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    // Create slider representation
    vtkSmartPointer<vtkSliderRepresentation2D> sliderRep = vtkSmartPointer<vtkSliderRepresentation2D>::New();
    sliderRep->SetMinimumValue(xMin);
    sliderRep->SetMaximumValue(xMax);
    sliderRep->SetValue(xMin);
    sliderRep->SetTitleText("Cut X");

    // Position slider on screen (bottom right corner)
    sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
    sliderRep->GetPoint1Coordinate()->SetValue(0.8, 0.1);
    sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
    sliderRep->GetPoint2Coordinate()->SetValue(0.95, 0.1);

    sliderRep->SetSliderLength(0.02);
    sliderRep->SetSliderWidth(0.03);
    sliderRep->SetEndCapLength(0.01);
    sliderRep->SetEndCapWidth(0.03);
    sliderRep->SetTubeWidth(0.005);
    sliderRep->SetLabelFormat("%0.2f");
    sliderRep->SetTitleHeight(0.02);
    sliderRep->SetLabelHeight(0.02);

    // Create slider widget
    vtkSmartPointer<vtkSliderWidget> sliderWidget = vtkSmartPointer<vtkSliderWidget>::New();
    sliderWidget->SetInteractor(interactor);
    sliderWidget->SetRepresentation(sliderRep);
    sliderWidget->SetAnimationModeToAnimate();
    sliderWidget->EnabledOn();

    // Setup callback to update clipping plane when slider moves
    vtkSmartPointer<SliderCallback> callback = vtkSmartPointer<SliderCallback>::New();
    callback->m_Plane = clipPlane;
    callback->m_RenderWindow = renderWindow;
    sliderWidget->AddObserver(vtkCommand::InteractionEvent, callback);

    // Initialize and start
    renderWindow->Render();
    interactor->Initialize();
    interactor->Start();
	
	return EXIT_SUCCESS;

}

