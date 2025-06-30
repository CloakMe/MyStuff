#include "PressureVisualization.h"
#include <vtkLookupTable.h>
#include <vtkPointData.h>

using namespace visu;
/*
PressureVisualization::PressureVisualization()
{
}*/

void PressureVisualization::createActors(vtkDataSet* dataset)
{
    // Set the active vector array to "pressure" in the point data
    dataset->GetPointData()->SetActiveVectors("pressure");

    // Set up pressure color mapping
    vtkNew<vtkLookupTable> lut;
    lut->SetHueRange(0.667, 0.0); // Blue to red
    lut->Build();
    
    mapper->SetInputData(dataset);
    mapper->SetScalarModeToUsePointData();
    mapper->SelectColorArray("Pressure");
    mapper->SetLookupTable(lut);
    mapper->SetScalarRange(dataset->GetPointData()->GetScalars("Pressure")->GetRange());
    
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

