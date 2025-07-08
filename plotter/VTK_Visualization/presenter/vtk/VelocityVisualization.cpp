#include "VelocityVisualization.h"
#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkDataSetMapper.h>


using namespace visu;
using namespace std;

VelocityVisualization::VelocityVisualization(const IConfigurator& configurator)
  : m_configurator(configurator)
{
}

vtkSmartPointer<vtkActor> VelocityVisualization::createActors(vtkSmartPointer<vtkDataSet> dataset)
{
    // Set the active vector array to "velocity" in the point data
    string velocityVectorName = m_configurator.GetVelocityValue();

    vtkPointData* pointData = dataset->GetPointData();
    vtkCellData* cellData = dataset->GetCellData(); //;
    bool pointDataOk = false, cellDataOk = false;
    vtkDataArray* dataArray = nullptr;
    if(pointData && -1 != pointData->SetActiveVectors(velocityVectorName.c_str())) {
        pointDataOk = true;
        dataArray = pointData->GetVectors(velocityVectorName.c_str());
    } else if(cellData && -1 != cellData->SetActiveVectors(velocityVectorName.c_str())) {
        cellDataOk = true;
        dataArray = cellData->GetVectors(velocityVectorName.c_str());
    }
    if(!cellDataOk && !pointDataOk)
        return nullptr;

    // Create glyphs for velocity vectors
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkArrowSource> arrow = vtkSmartPointer<vtkArrowSource>::New();
    vtkSmartPointer<vtkGlyph3D> glyph = vtkSmartPointer<vtkGlyph3D>::New();
    glyph->SetInputData(dataset);
    glyph->SetSourceConnection(arrow->GetOutputPort());
    glyph->SetVectorModeToUseVector();
    glyph->SetScaleFactor(m_configurator.GetGlyphScaleFactor());
    glyph->Update();

    mapper->SetInputConnection(glyph->GetOutputPort());
    actor->SetMapper(mapper);
    return actor;
}

//void VelocityVisualization::addToRenderer(vtkRenderer* renderer)
//{ 
//    renderer->AddActor(actor); 
//}
//
//void VelocityVisualization::removeFromRenderer(vtkRenderer* renderer)
//{ 
//    renderer->RemoveActor(actor);
//}



