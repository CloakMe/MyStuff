#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

#include "presenter/vtk/MeshVisualization.h"
#include "presenter/vtk/VisualizationStrategy.h"
#include "UI/vtk/VTK_CFDVisualizer.h"
#include "VTK_Database.h"
#include "Presenter.h"
#include "JSONConfigParser.h"
#include <vtkPolyDataAlgorithm.h>
#include <vtkRenderer.h>
#include <memory>

using namespace visu;
using namespace std;


int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.vtk>" << std::endl;
         return EXIT_FAILURE;
    }
    
    JSONConfigParser& config = JSONConfigParser::Instance();
    config.LoadConfigFromFile("configuration.json");
    config.SetRootKey("visualization");

    std::string pressureKey = config.GetPressureValue();  // looks under "visualization"

    cout << "pressure = " << pressureKey << endl;
    
    unique_ptr<IVisualizer> view = make_unique<VTK_CFDVisualizer>();
    unique_ptr<IDB> vtkDatabase = make_unique<VTK_Database>(argv[1]);
    Presenter presenter(move(vtkDatabase), move(view));
    presenter.Load();
    presenter.UpdateView();
    return EXIT_SUCCESS;
}
