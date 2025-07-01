#include "PressureVisualization.h"
#include <vtkLookupTable.h>
#include <vtkPointData.h>

using namespace visu;
using namespace std;

PressureVisualization::PressureVisualization(const IVisualizationConfigurator& visualizationConfigurator)
  : m_visualizationConfigurator(visualizationConfigurator)
{
    
}

void PressureVisualization::createActors(vtkDataSet* dataset)
{
    string pressureFieldName = m_visualizationConfigurator.getVisuType(VisuType::Pressure);
    // Set the active vector array to "pressure" in the point data
    dataset->GetPointData()->SetActiveVectors(pressureFieldName.c_str());

    // Set up pressure color mapping
    vtkNew<vtkLookupTable> lut;
    lut->SetHueRange(0.667, 0.0); // Blue to red
    lut->Build();
    
    mapper->SetInputData(dataset);
    mapper->SetScalarModeToUsePointData();
    mapper->SelectColorArray(pressureFieldName.c_str());
    mapper->SetLookupTable(lut);
    vtkDataArray* dataArray = dataset->GetPointData()->GetScalars(pressureFieldName.c_str());
    mapper->SetScalarRange(dataArray->GetRange());
    
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

