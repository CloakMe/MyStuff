#include "PressureVisualization.h"

using namespace visu;
/*
PressureVisualization::PressureVisualization()
{
}*/

void PressureVisualization::createActors(vtkDataSet* dataset)
{
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

