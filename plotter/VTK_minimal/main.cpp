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
//#include <vtkNamedColors.h>
#include <vtkProperty.h>

int main() {
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
