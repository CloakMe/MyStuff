#include "PressureVisualization.h"
#include <vtkLookupTable.h>
#include <vtkDataArray.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkDataSetAttributes.h>
 
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
    
    vtkPointData* pointData = dataset->GetPointData();
    vtkCellData* cellData = dataset->GetCellData();
    vtkDataSetAttributes* dataSetAttr = cellData != nullptr ? cellData : nullptr;
    dataSetAttr = pointData != nullptr ? pointData : dataSetAttr;
    if(!dataSetAttr)
        return;
    
    // Set up pressure color mapping
    vtkNew<vtkLookupTable> lut;
    lut->SetHueRange(0.667, 0.0); // Blue to red
    lut->Build();
    
    mapper->SetScalarModeToUseCellData();
    mapper->SetInputData(dataset); 
    mapper->SelectColorArray(pressureFieldName.c_str());
    mapper->SetLookupTable(lut);
    int result = dataSetAttr->SetActiveScalars(pressureFieldName.c_str());
    if(result != -1)
    {
        vtkDataArray* dataArray = dataSetAttr->GetScalars(pressureFieldName.c_str());
        mapper->SetScalarRange(dataArray->GetRange());
    }
    
    
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

