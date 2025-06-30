#include "PressureVisualization.h"
#include <vtkLookupTable.h>
#include <vtkPointData.h>

using namespace visu;
using namespace std;

PressureVisualization::PressureVisualization() : 
    m_visuConfigurator(make_unique<VisualizationConfigurator>(VisuType::Pressure))
{
}

void PressureVisualization::createActors(vtkDataSet* dataset)
{
    string pressureField = m_visuConfigurator->getVisuType();
    // Set the active vector array to "pressure" in the point data
    dataset->GetPointData()->SetActiveVectors(pressureField);

    // Set up pressure color mapping
    vtkNew<vtkLookupTable> lut;
    lut->SetHueRange(0.667, 0.0); // Blue to red
    lut->Build();
    
    mapper->SetInputData(dataset);
    mapper->SetScalarModeToUsePointData();
    mapper->SelectColorArray(pressureField);
    mapper->SetLookupTable(lut);
    mapper->SetScalarRange(dataset->GetPointData()->GetScalars(pressureField)->GetRange());
    
    actor->SetMapper(mapper);
}

void PressureVisualization::addToRenderer(vtkRenderer* renderer)
{ 
    renderer->AddActor(actor); 
}

void PressureVisualization::removeFromRenderer(vtkRenderer* renderer)
{ 
    renderer->RemoveActor(actor); 
}

