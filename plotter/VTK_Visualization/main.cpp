#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

#include "presenter/vtk/MeshVisualization.h"
#include "presenter/vtk/VisualizationStrategy.h"
#include "UI/vtk/VTK_CFDVisualizer.h"
#include "configuration/json/JSONConfigParser.h"
#include "VTK_Database.h"
#include "Presenter.h"
#include "VisualizationFactory.h"
#include <vtkPolyDataAlgorithm.h>
#include <vtkRenderer.h>
#include <memory>

using namespace visu;
using namespace std;


int main(int argc, char* argv[]) 
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input.vtk>" << std::endl;
        return EXIT_FAILURE;
    }
    
    JSONConfigParser& config = JSONConfigParser::Instance();
    config.LoadConfigFromFile("configuration.json");
    auto visuFactory = make_unique<VisualizationFactory>(config);
    unique_ptr<IVisualizer> view = make_unique<VTK_CFDVisualizer>(config, move(visuFactory));
    unique_ptr<IDB> vtkDatabase = make_unique<VTK_Database>(argv[1]);
    Presenter presenter(move(vtkDatabase), move(view));
    presenter.Load();
    presenter.UpdateView();

    _CrtDumpMemoryLeaks();
    return EXIT_SUCCESS;
}
