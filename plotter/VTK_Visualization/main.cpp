#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

#include "presenter/MeshVisualization.h"
#include "presenter/VisualizationStrategy.h"
#include "UI/VTK_CFDVisualizer.h"
#include <vtkPolyDataAlgorithm.h>
#include <vtkRenderer.h>
using namespace visu;


class VisualizationManager {
public:
    VisualizationManager(
        const vtkSmartPointer<vtkPolyDataAlgorithm>& sharedFilter,
        vtkSmartPointer<vtkRenderer>& renderer) :
            m_filter(sharedFilter),
            m_renderer(renderer),
            m_currentVisualization(nullptr),
            m_currentIndex(-1) // Start before first
    {}

    // Add a visualization strategy to manage
    void AddVisualization(std::unique_ptr<VisualizationStrategy> visualization)
    {
        m_visualizations.push_back(std::move(visualization));
    }

    // Create actors for all visualizations and add them to the renderer
    void CreateAllActors() 
    {
/*        for (const auto& vis : m_visualizations) {
            vis->createActors(m_filter, m_renderer);
        }*/
    }

    void showNext() {
        if (m_visualizations.empty()) return;

        // Hide current visualization if any
        //if (m_currentVisualization) {
        //    m_currentVisualization->setVisibility(false);
        //}

        // Advance index cyclically
        m_currentIndex = (m_currentIndex + 1) % m_visualizations.size();
        m_currentVisualization = m_visualizations[m_currentIndex].get();

        // Show the new current visualization
        //m_currentVisualization->setVisibility(true);

        // Request render update if needed
        if (m_renderer) {
            m_renderer->GetRenderWindow()->Render();
        }
    }

private:
    vtkSmartPointer<vtkPolyDataAlgorithm> m_filter;
    vtkSmartPointer<vtkRenderer> m_renderer;
    std::vector<std::unique_ptr<VisualizationStrategy>> m_visualizations;

    vtkSmartPointer<VisualizationStrategy> m_currentVisualization;
    size_t m_currentIndex; 
};


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.vtk>" << std::endl;
        return EXIT_FAILURE;
    }

    VTK_CFDVisualizer visualizer(argv[1]);
    visualizer.start();
    return EXIT_SUCCESS;
}
