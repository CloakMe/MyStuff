#include "VelocityVisualization.h"
#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>
#include <vtkPointData.h>

using namespace visu;

VelocityVisualization::VelocityVisualization() : 
    m_visuConfigurator(make_unique<VisualizationConfigurator>(VisuType::Velocity))
{
}

void VelocityVisualization::createActors(vtkDataSet* dataset)
{
    // Set the active vector array to "velocity" in the point data
    dataset->GetPointData()->SetActiveVectors(m_visuConfigurator->getVisuType());
    
    // Create glyphs for velocity vectors
    vtkNew<vtkArrowSource> arrow;
    vtkNew<vtkGlyph3D> glyph;
    glyph->SetInputData(dataset);
    glyph->SetSourceConnection(arrow->GetOutputPort());
    glyph->SetVectorModeToUseVector();
    glyph->SetScaleFactor(0.1);
    glyph->Update();

    mapper->SetInputConnection(glyph->GetOutputPort());
    actor->SetMapper(mapper);
}

void VelocityVisualization::addToRenderer(vtkRenderer* renderer)
{ 
    renderer->AddActor(actor); 
}

void VelocityVisualization::removeFromRenderer(vtkRenderer* renderer)
{ 
    renderer->RemoveActor(actor);
}



