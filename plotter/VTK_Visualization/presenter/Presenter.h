#pragma once
#include "IPresenter.h"
#include "IDB.h"
#include "IVisualizer.h"
#include "VisuType.h"
#include "CrossSection.h"
#include <memory>

namespace visu
{    
    class Presenter : public IPresenter
    {
    public:
        Presenter(std::unique_ptr<IDB> database, std::unique_ptr<IVisualizer> view);
        void Load() override;// — calls IDB::Load internally.
        void LoadSpecific(LoadType loadType, std::string value) override;
        void SetVisualizationType(VisuType mode) override; // — switch between mesh or vector field.
        void SetCrossSection(const CrossSection& crossSection) override;
        void UpdateView() override; //— triggers the UI to redraw or refresh.
    private:
        std::unique_ptr<IDB> m_database;
        std::unique_ptr<IVisualizer> m_IVisualizer;
        VisuType m_visuType;
    };
}

