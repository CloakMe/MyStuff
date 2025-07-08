#include "MeshVisualization.h"
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkDataSet.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <memory>

using namespace visu;
using namespace std;

MeshVisualization::MeshVisualization(const IConfigurator& configurator)
  : m_configurator(configurator)
{}

vtkSmartPointer<vtkActor> MeshVisualization::createActors(vtkSmartPointer<vtkDataSet> dataset)
{
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    mapper->SetInputData(dataset);
    actor->SetMapper(mapper);
    actor->GetProperty()->SetRepresentationToWireframe();
    vector<double> rgb_color = m_configurator.GetMeshColor();
    if(rgb_color.size() == 3)
        actor->GetProperty()->SetColor(rgb_color[0], rgb_color[1], rgb_color[2]);
    return actor;
}

//void MeshVisualization::addToRenderer(vtkRenderer* renderer) 
//{ 
//    renderer->AddActor(actor); 
//}
//
//void MeshVisualization::removeFromRenderer(vtkRenderer* renderer) 
//{ 
//    renderer->RemoveActor(actor); 
//}
