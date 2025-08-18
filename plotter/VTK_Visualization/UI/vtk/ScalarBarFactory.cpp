#include "ScalarBarFactory.h"
#include <vtkScalarBarActor.h>

vtkSmartPointer<vtkScalarBarActor> visu::ScalarBarFactory::GetScalarBar(vtkSmartPointer<vtkMapper> mapper)
{
    // Assuming you have already created your dataset mapper and actor as before

    // Create scalar bar actor for the legend
    vtkSmartPointer<vtkScalarBarActor> scalarBar = vtkSmartPointer<vtkScalarBarActor>::New();
    scalarBar->SetLookupTable(mapper->GetLookupTable());  // Use the same lookup table as the mapper
    scalarBar->SetTitle("Velocity Magnitude");             // Title for the legend
    scalarBar->SetNumberOfLabels(6);                       // Number of tick labels to show

    // Customize orientation and position if needed
    scalarBar->SetOrientationToVertical();
    scalarBar->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
    scalarBar->GetPositionCoordinate()->SetValue(0.9, 0.1); // Position in viewport coordinates
    scalarBar->SetWidth(0.08);
    scalarBar->SetHeight(0.7); 

    return scalarBar;
}

