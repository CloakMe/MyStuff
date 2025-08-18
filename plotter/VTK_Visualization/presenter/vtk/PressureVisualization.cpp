#include "PressureVisualization.h"
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include <vtkLookupTable.h>
#include <vtkDataArray.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkDataSetAttributes.h>
#include <vtkDataSetMapper.h>

 
using namespace visu;
using namespace std;

PressureVisualization::PressureVisualization(const IConfigurator& configurator)
  : m_configurator(configurator)
{
    
}

vtkSmartPointer<vtkActor> PressureVisualization::createActors(vtkSmartPointer<vtkDataSet> dataset)
{   // Set the active vector array to "pressure" in the point/cell data
    vtkPointData* pointData = dataset->GetPointData();
    vtkCellData* cellData = dataset->GetCellData();
    string pressureFieldName = m_configurator.GetPressureValue();
    bool pointDataOk = false,
        cellDataOk = false;
    vtkDataArray* dataArray = nullptr;
    if(pointData && -1 != pointData->SetActiveScalars(pressureFieldName.c_str())) {
        pointDataOk = true;
        dataArray = pointData->GetScalars(pressureFieldName.c_str());
    }
    else if(cellData && -1 != cellData->SetActiveScalars(pressureFieldName.c_str())) {
        cellDataOk = true;
        dataArray = cellData->GetScalars(pressureFieldName.c_str());
    }
    if(!cellDataOk && !pointDataOk)
        return nullptr;
 
    // Set up pressure color mapping
    vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
    vector<double> hue = m_configurator.GetPressureHue();
    if(hue.size() == 2)
        lut->SetHueRange(hue[0], hue[1]); // Blue to red
    lut->Build();

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetScalarModeToUseCellData();
    mapper->SetInputData(dataset);
    mapper->SelectColorArray(pressureFieldName.c_str());
    mapper->SetLookupTable(lut);
    mapper->SetScalarRange(dataArray->GetRange());
    // You cannot easily clip glyphs already generated; 
    // clipping needs to happen at the dataset level before glyphing.
    // mapper->SetInputConnection(glyph->GetOutputPort());

    actor->SetMapper(mapper);
    return actor;
}

//void PressureVisualization::addToRenderer(vtkRenderer* renderer)
//{ 
//    renderer->AddActor(actor); 
//}
//
//void PressureVisualization::removeFromRenderer(vtkRenderer* renderer)
//{ 
//    renderer->RemoveActor(actor); 
//}

