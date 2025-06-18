#pragma once
#include "IPresenter.h"
#include "IDB.h"
#include "IUI.h"
#include "VisuType.h"
#include "CrossSection.h"
#include <memory>

namespace visu
{    
    class VTK_Presenter : public IPresenter
    {
    public:
        VTK_Presenter(std::unique_ptr<IDB> database, std::unique_ptr<IUI> userInteface);
        void Load() override;// — calls IDB::Load internally.
        void LoadSpecific(LoadType loadType, std::string value) override;
        void SetVisualizationType(VisuType mode) override; // — switch between mesh or vector field.
        void SetCrossSection(const CrossSection& crossSection) override;
        void UpdateView() override; //— triggers the UI to redraw or refresh.
    private:
        std::unique_ptr<IDB> m_IDB;
        std::unique_ptr<IUI> m_IUI;
    };
}

