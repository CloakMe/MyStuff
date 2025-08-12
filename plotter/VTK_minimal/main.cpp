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
	auto points = vtkSmartPointer<vtkPoints>::New();

    // Define points (example coordinates, can be adjusted)
    // Bottom square base
    points->InsertNextPoint(0.0, 0.0, 0.0); // 0
    points->InsertNextPoint(1.0, 0.0, 0.0); // 1
    points->InsertNextPoint(1.0, 1.0, 0.0); // 2
    points->InsertNextPoint(0.0, 1.0, 0.0); // 3

    // Points elevated for tetra and pyramid construction
    points->InsertNextPoint(0.5, 0.5, 0.5);  // 4 - center elevated point (for middle layer tetra)
    points->InsertNextPoint(0.5, 0.5, 1.0);  // 5 - top pyramid peak

    // Additional points to form the tetrahedrons with peaks pointing up/down
    points->InsertNextPoint(0.5, 0.0, 0.5);  // 6
    points->InsertNextPoint(1.0, 0.5, 0.5);  // 7
    points->InsertNextPoint(0.5, 1.0, 0.5);  // 8
    points->InsertNextPoint(0.0, 0.5, 0.5);  // 9

    // Create unstructured grid
    auto ugrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    ugrid->SetPoints(points);

    // Define tetrahedrons for bottom layer (4 tetras)
    // Tetra 1: points 0,1,6,4
    auto tetra1 = vtkSmartPointer<vtkTetra>::New();
    tetra1->GetPointIds()->SetId(0, 0);
    tetra1->GetPointIds()->SetId(1, 1);
    tetra1->GetPointIds()->SetId(2, 6);
    tetra1->GetPointIds()->SetId(3, 4);
    ugrid->InsertNextCell(tetra1->GetCellType(), tetra1->GetPointIds());

    // Tetra 2: points 1,2,7,4
    auto tetra2 = vtkSmartPointer<vtkTetra>::New();
    tetra2->GetPointIds()->SetId(0, 1);
    tetra2->GetPointIds()->SetId(1, 2);
    tetra2->GetPointIds()->SetId(2, 7);
    tetra2->GetPointIds()->SetId(3, 4);
    ugrid->InsertNextCell(tetra2->GetCellType(), tetra2->GetPointIds());

    // Tetra 3: points 2,3,8,4
    auto tetra3 = vtkSmartPointer<vtkTetra>::New();
    tetra3->GetPointIds()->SetId(0, 2);
    tetra3->GetPointIds()->SetId(1, 3);
    tetra3->GetPointIds()->SetId(2, 8);
    tetra3->GetPointIds()->SetId(3, 4);
    ugrid->InsertNextCell(tetra3->GetCellType(), tetra3->GetPointIds());

    // Tetra 4: points 3,0,9,4
    auto tetra4 = vtkSmartPointer<vtkTetra>::New();
    tetra4->GetPointIds()->SetId(0, 3);
    tetra4->GetPointIds()->SetId(1, 0);
    tetra4->GetPointIds()->SetId(2, 9);
    tetra4->GetPointIds()->SetId(3, 4);
    ugrid->InsertNextCell(tetra4->GetCellType(), tetra4->GetPointIds());

    // Middle layer tetrahedrons
    // Tetra 5: points 6,7,4,5 (peak upward)
    auto tetra5 = vtkSmartPointer<vtkTetra>::New();
    tetra5->GetPointIds()->SetId(0, 6);
    tetra5->GetPointIds()->SetId(1, 7);
    tetra5->GetPointIds()->SetId(2, 4);
    tetra5->GetPointIds()->SetId(3, 5);
    ugrid->InsertNextCell(tetra5->GetCellType(), tetra5->GetPointIds());

    // Tetra 6: points 7,8,4,5 (peak upward)
    auto tetra6 = vtkSmartPointer<vtkTetra>::New();
    tetra6->GetPointIds()->SetId(0, 7);
    tetra6->GetPointIds()->SetId(1, 8);
    tetra6->GetPointIds()->SetId(2, 4);
    tetra6->GetPointIds()->SetId(3, 5);
    ugrid->InsertNextCell(tetra6->GetCellType(), tetra6->GetPointIds());

    // Tetra 7: points 8,9,4,5 (peak upward)
    auto tetra7 = vtkSmartPointer<vtkTetra>::New();
    tetra7->GetPointIds()->SetId(0, 8);
    tetra7->GetPointIds()->SetId(1, 9);
    tetra7->GetPointIds()->SetId(2, 4);
    tetra7->GetPointIds()->SetId(3, 5);
    ugrid->InsertNextCell(tetra7->GetCellType(), tetra7->GetPointIds());

    // Tetra 8: points 9,6,4,5 (peak "downward" - inverted orientation)
    auto tetra8 = vtkSmartPointer<vtkTetra>::New();
    tetra8->GetPointIds()->SetId(0, 9);
    tetra8->GetPointIds()->SetId(1, 6);
    tetra8->GetPointIds()->SetId(2, 4);
    tetra8->GetPointIds()->SetId(3, 5);
    ugrid->InsertNextCell(tetra8->GetCellType(), tetra8->GetPointIds());

    // Upper layer pyramid (4-point base + apex)
    auto pyramid = vtkSmartPointer<vtkPyramid>::New();
    pyramid->GetPointIds()->SetId(0, 6);
    pyramid->GetPointIds()->SetId(1, 7);
    pyramid->GetPointIds()->SetId(2, 8);
    pyramid->GetPointIds()->SetId(3, 9);
    pyramid->GetPointIds()->SetId(4, 5); // apex pointing upward
    ugrid->InsertNextCell(pyramid->GetCellType(), pyramid->GetPointIds());
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

