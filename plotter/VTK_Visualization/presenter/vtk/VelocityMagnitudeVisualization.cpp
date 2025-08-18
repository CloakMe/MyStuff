#include "VelocityMagnitudeVisualization.h"

namespace visu
{

VelocityMagnitudeVisualization::VelocityMagnitudeVisualization(const IConfigurator& configurator)
  : m_configurator(configurator)
{
}

vtkSmartPointer<vtkActor> VelocityMagnitudeVisualization::createActors(vtkSmartPointer<vtkDataSet> dataset)
{   // Set the active vector array to "velocity" in the point data
    vtkPointData* pointData = dataset->GetPointData();
    vtkCellData* cellData = dataset->GetCellData();
    string velocityVectorName = m_configurator.GetVelocityValue();
    bool pointDataOk = false, 
        cellDataOk = false;
    vtkDataArray* dataArray = nullptr;
    if(pointData && -1 != pointData->SetActiveVectors(velocityVectorName.c_str())) {
        pointDataOk = true;
        dataArray = pointData->GetVectors(velocityVectorName.c_str());
    }
    else if(cellData && -1 != cellData->SetActiveVectors(velocityVectorName.c_str())) {
        cellDataOk = true;
        dataArray = cellData->GetVectors(velocityVectorName.c_str());
    }
    if(!cellDataOk && !pointDataOk)
        return nullptr;

    // Compute velocity magnitude array
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkDoubleArray> magnitudeArray = vtkSmartPointer<vtkDoubleArray>::New();
    magnitudeArray->SetName("VelocityMagnitude");
    
    vtkIdType numTuples = dataArray->GetNumberOfTuples();
    magnitudeArray->SetNumberOfTuples(numTuples);
    
    for(vtkIdType i = 0; i < numTuples; ++i) {
        double vec[3]{0.0, 0.0, 0.0};
        dataArray->GetTuple(i, vec);
        double mag = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
        magnitudeArray->SetTuple1(i, mag);
    }

    // Add magnitude scalar array to the dataset
    if(pointDataOk) {
        pointData->AddArray(magnitudeArray);
        pointData->SetActiveScalars("VelocityMagnitude");
    } else {
        cellData->AddArray(magnitudeArray);
        cellData->SetActiveScalars("VelocityMagnitude");
    }

    // Create mapper and actor to visualize the scalar magnitude
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(dataset);
    mapper->SetScalarRange(magnitudeArray->GetRange());

    actor->SetMapper(mapper);
    return actor;
}

}
