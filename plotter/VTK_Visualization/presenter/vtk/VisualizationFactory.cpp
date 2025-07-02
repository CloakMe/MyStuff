#include "VisualizationFactory.h"
#include "MeshVisualization.h"
#include "PressureVisualization.h"
#include "VelocityVisualization.h"
#include "VisuType.h"
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkCellData.h>

using namespace visu;
using namespace std;

// Factory implementation
VisualizationFactory::VisualizationFactory(std::unique_ptr<IVisualizationConfigurator> visualizationConfigurator)
{
    m_visualizationConfigurator = move(visualizationConfigurator);
}

std::unique_ptr<VisualizationStrategy> VisualizationFactory::createStrategy(
    VisuType visuType, vtkSmartPointer<vtkDataSet> dataset)
{
    if (!dataset) {
        cerr << "vtkDataSet pointer is null!" << endl;
        return nullptr;
    }
/*    unique_ptr<VTK_DBWrapper> vtk_database = move(database);
    vtkDataSet* dataset = *((*vtk_database)());*/
    unique_ptr<VisualizationStrategy> strategy = nullptr;
    if (visuType == VisuType::Mesh) 
    {
        strategy = make_unique<MeshVisualization>(*m_visualizationConfigurator);
        strategy->createActors(dataset);
        return strategy;
    }
    else if (visuType == VisuType::Pressure) 
    {
        vtkPointData* pointData = nullptr;
        vtkCellData* cellData = nullptr;//;
        string pressureFieldName = m_visualizationConfigurator->getVisuType(VisuType::Pressure);
        if( pointData = dataset->GetPointData() )
        {            
            if(-1 != pointData->SetActiveScalars(pressureFieldName.c_str())  )
                return strategy;
        }
        else if(cellData = dataset->GetCellData())
        {
            if(-1 != cellData->SetActiveScalars(pressureFieldName.c_str())  )
                return strategy;
        }        
        
        
 /*           

        std::cout << "Available arrays in PointData:" << std::endl;
        for (int i = 0; i < numArrays; ++i) 
        {
            vtkDataArray* array = pointData->GetArray(i);
            if (array) {
                std::cout << "Array " << i << ": " << array->GetName() << std::endl;
            }
        }
        if(result == -1)
        {
            cerr << "Could not set Pressure Active scalars!" << endl;
            return strategy;
        }
        */
        strategy = make_unique<PressureVisualization>(*m_visualizationConfigurator);
        strategy->createActors(dataset);
        return strategy;
    }
    else if (visuType == VisuType::Velocity) 
    {
        // Set the active vector array to "velocity" in the point data
        string velocityVectorName = m_visualizationConfigurator->getVisuType(VisuType::Velocity);
        if( -1 == dataset->GetPointData()->SetActiveVectors(velocityVectorName.c_str()) )
            return strategy;
        
        strategy = make_unique<VelocityVisualization>(*m_visualizationConfigurator);
        strategy->createActors(dataset);
        return strategy;
    }
    cerr << "Unknown visualization mode!" << endl;
    return nullptr;
}
