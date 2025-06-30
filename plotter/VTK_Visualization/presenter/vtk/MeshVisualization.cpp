#include "MeshVisualization.h"
#include <vtkProperty.h>
#include <memory>

using namespace visu;

MeshVisualization::MeshVisualization() : 
    m_visuConfigurator(make_unique<VisualizationConfigurator>(VisuType::Mesh))
{
}

void MeshVisualization::createActors(vtkDataSet* dataset)
{
    mapper->SetInputData(dataset);
    actor->SetMapper(mapper);
    actor->GetProperty()->SetRepresentationToWireframe();
    actor->GetProperty()->SetColor(0.5, 0.5, 0.5);
}

void MeshVisualization::addToRenderer(vtkRenderer* renderer) 
{ 
    renderer->AddActor(actor); 
}

void MeshVisualization::removeFromRenderer(vtkRenderer* renderer) 
{ 
    renderer->RemoveActor(actor); 
}
