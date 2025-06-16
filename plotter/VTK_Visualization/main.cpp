#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

#include <memory>
#include <vector>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkStructuredGridReader.h>
#include <vtkDataSetReader.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkGlyph3D.h>
#include <vtkArrowSource.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkCallbackCommand.h>

// Abstract base class for visualization strategies
class VisualizationStrategy {
public:
    virtual ~VisualizationStrategy() = default;
    virtual void createActors(const vtkSmartPointer<vtkPolyDataAlgorithm>& filter, 
        vtkSmartPointer<vtkRenderer>& renderer) = 0;
    //virtual void addToRenderer(vtkRenderer* renderer) = 0;
    //virtual void removeFromRenderer(vtkRenderer* renderer) = 0;
};

// Factory for creating visualization strategies
class VisualizationFactory {
public:
    std::unique_ptr<VisualizationStrategy> createStrategy(
        const std::string& mode, vtkDataSet* dataset);
};

// Concrete strategies
class MeshVisualization : public VisualizationStrategy {
public:
    void createActors(const vtkSmartPointer<vtkPolyDataAlgorithm>& filter, vtkSmartPointer<vtkRenderer>& renderer) override
    {
        vtkNew<vtkDataSetMapper> mapper;
        mapper->SetInputConnection(filter->GetOutputPort());

        vtkNew<vtkActor> actor;
        actor->SetMapper(mapper);

        renderer->AddActor(actor);
    }

    //void addToRenderer(vtkRenderer* renderer) override { renderer->AddActor(actor); }
    //void removeFromRenderer(vtkRenderer* renderer) override { renderer->RemoveActor(actor); }

private:
    vtkNew<vtkDataSetMapper> mapper;
    vtkNew<vtkActor> actor;
};

class PressureVisualization : public VisualizationStrategy {
public:
    void createActors(const vtkSmartPointer<vtkPolyDataAlgorithm>& filter, 
        vtkSmartPointer<vtkRenderer>& renderer) override 
    {
        // Set up pressure color mapping
        vtkNew<vtkLookupTable> lut;
        lut->SetHueRange(0.667, 0.0); // Blue to red
        lut->Build();

        vtkNew<vtkDataSetMapper> mapper;
        mapper->SetInputConnection(filter->GetOutputPort());
        mapper->SetLookupTable(lut);

        vtkNew<vtkActor> actor;
        actor->SetMapper(mapper);

        // Customize actor appearance for pressure
        actor->GetProperty()->SetColor(1.0, 0.0, 0.0); // red

        renderer->AddActor(actor);
        //-----
        //mapper->SetInputData(dataset);
        //mapper->SetScalarModeToUsePointData();
        //mapper->SelectColorArray("Pressure");
        //mapper->SetLookupTable(lut);
        //mapper->SetScalarRange(dataset->GetPointData()->GetScalars("Pressure")->GetRange());

        actor->SetMapper(mapper);
    }

    //void addToRenderer(vtkRenderer* renderer) override { renderer->AddActor(actor); }
    //void removeFromRenderer(vtkRenderer* renderer) override { renderer->RemoveActor(actor); }

private:
    vtkNew<vtkDataSetMapper> mapper;
    vtkNew<vtkActor> actor;
};

class VelocityVisualization : public VisualizationStrategy {
public:
    void createActors(const vtkSmartPointer<vtkPolyDataAlgorithm>& filter, vtkSmartPointer<vtkRenderer>& renderer) override {
        // Create glyphs for velocity vectors
        vtkNew<vtkArrowSource> arrow;
        vtkNew<vtkGlyph3D> glyph;
        glyph->SetInputConnection(filter->GetOutputPort());
        glyph->SetSourceConnection(arrow->GetOutputPort());
        glyph->SetVectorModeToUseVector();
        glyph->SetScaleFactor(0.1);
        glyph->Update();

        vtkNew<vtkDataSetMapper> mapper;
        mapper->SetInputConnection(filter->GetOutputPort());
        mapper->SetInputConnection(glyph->GetOutputPort());

        vtkNew<vtkActor> actor;
        actor->SetMapper(mapper);

        // Customize actor appearance for velocity
        actor->GetProperty()->SetColor(0.0, 0.0, 1.0); // blue

        renderer->AddActor(actor);
    }

    //void addToRenderer(vtkRenderer* renderer) override { renderer->AddActor(actor); }
    //void removeFromRenderer(vtkRenderer* renderer) override { renderer->RemoveActor(actor); }

private:
    vtkNew<vtkDataSetMapper> mapper;
    vtkNew<vtkActor> actor;
};

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
        for (const auto& vis : m_visualizations) {
            vis->createActors(m_filter, m_renderer);
        }
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

// Main application class
class CFDVisualizer {
public:
    CFDVisualizer(const char* filename) {
        loadData(filename);
        setupVisualizations();
        setupUI();
    }

    void start() {
        renderWindow->Render();
        interactor->Start();
    }

private:
    void loadData(const char* filename) {
        // Auto-detect file type
        vtkNew<vtkDataSetReader> reader;
        reader->SetFileName(filename);
        reader->Update();
        dataset = reader->GetOutput();
    }

    void setupVisualizations() {
        VisualizationFactory factory;

        manager.addVisualization(
            factory.createStrategy("mesh", dataset));
        manager.addVisualization(
            factory.createStrategy("pressure", dataset));
        manager.addVisualization(
            factory.createStrategy("velocity", dataset));

        manager.showNext(); // Show first visualization
    }

    void setupUI() 
    {
        vtkNew<vtkCallbackCommand> callback;
        callback->SetCallback(CFDVisualizer::KeyPressCallback);
        callback->SetClientData(this);
        interactor->AddObserver(vtkCommand::KeyPressEvent, callback);
    }

    static void KeyPressCallback(vtkObject* caller, unsigned long eid, void* clientdata, void* calldata) {
        CFDVisualizer* self = static_cast<CFDVisualizer*>(clientdata);
        self->OnKeyPress();
    }

    void OnKeyPress() {
        manager.showNext();
        renderWindow->Render();
    }

    //void setupUI() {

    //    interactor->AddObserver(vtkCommand::KeyPressEvent, [this](vtkObject*, unsigned long, void*) {
    //        manager.showNext();
    //        renderWindow->Render();
    //    });
    //}

    vtkNew<vtkRenderWindow> renderWindow;
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkRenderWindowInteractor> interactor;
    VisualizationManager manager{ renderer };
    vtkDataSet* dataset;
};

// Factory implementation
std::unique_ptr<VisualizationStrategy> VisualizationFactory::createStrategy(
    const std::string& mode, vtkDataSet* dataset)
{
    if (!dataset) {
        std::cerr << "vtkDataSet pointer is null!" << std::endl;
        return nullptr;
    }

    if (mode == "mesh") {
        auto strategy = std::make_unique<MeshVisualization>();
        strategy->createActors(dataset);
        return strategy;
    }
    else if (mode == "pressure") {
        auto strategy = std::make_unique<PressureVisualization>();
        strategy->createActors(dataset);
        return strategy;
    }
    else if (mode == "velocity") {
        auto strategy = std::make_unique<VelocityVisualization>();
        strategy->createActors(dataset);
        return strategy;
    }
    throw std::runtime_error("Unknown visualization mode");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.vtk>" << std::endl;
        return EXIT_FAILURE;
    }

    CFDVisualizer visualizer(argv[1]);
    visualizer.start();
    return EXIT_SUCCESS;
}
