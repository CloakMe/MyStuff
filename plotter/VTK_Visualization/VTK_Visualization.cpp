#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
    // Create a simple image data (3x3x2)
    auto imageData = vtkSmartPointer<vtkImageData>::New();
    imageData->SetDimensions(3, 3, 2);
    imageData->SetSpacing(1.0, 1.0, 1.0);
    imageData->SetOrigin(0.0, 0.0, 0.0);

    // Map the image data to graphics primitives
    auto mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(imageData);

    // Create an actor to represent the data
    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // Create a renderer and add the actor
    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(0.1, 0.2, 0.3);

    // Create a render window and add the renderer
    auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(800, 600);
    std::cout << "OpenGL info:" << std::endl;
    std::cout << "  VTK OpenGL version: " << renderWindow->ReportCapabilities() << std::endl;
	
    // Create a render window interactor and link it to the window
    auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    // Render and start interaction
    renderWindow->Render();
    interactor->Initialize();
    interactor->Start();

    return EXIT_SUCCESS;
}
