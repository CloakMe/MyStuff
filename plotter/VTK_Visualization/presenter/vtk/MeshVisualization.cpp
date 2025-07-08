#include "MeshVisualization.h"
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkDataSet.h>
#include <vtkProperty.h>
#include <vtkDataSetMapper.h>
#include <memory>

using namespace visu;
using namespace std;

MeshVisualization::MeshVisualization(const IVisualizationConfigurator& visualizationConfigurator)
  : m_visualizationConfigurator(visualizationConfigurator)
{}

vtkSmartPointer<vtkActor> MeshVisualization::createActors(vtkSmartPointer<vtkDataSet> dataset)
{
    vtkSmartPointer<vtkDataSetMapper> mapper;
    vtkSmartPointer<vtkActor> actor;
    mapper->SetInputData(dataset);
    actor->SetMapper(mapper);
    actor->GetProperty()->SetRepresentationToWireframe();
    actor->GetProperty()->SetColor(0.5, 0.5, 0.5);
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
