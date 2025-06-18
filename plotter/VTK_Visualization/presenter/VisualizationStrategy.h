#ifndef VISUALIZATIONSTRATEGY_H
#define VISUALIZATIONSTRATEGY_H

namespace visu
{

    class VisualizationStrategy 
    {
    public:
        virtual ~VisualizationStrategy() = default;
        virtual void createActors(vtkDataSet* dataset) = 0;
        virtual void addToRenderer(vtkRenderer* renderer) = 0;
        virtual void removeFromRenderer(vtkRenderer* renderer) = 0;
    };

}

#endif // VISUALIZATIONSTRATEGY_H
