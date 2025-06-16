#pragma once
#include "IPresenter.h"
#include "VisuType.h"
#include "CrossSection.h"

namespace visu
{    
    public class VTK_Presenter
    {
    public:
        void Load() override;// — calls IDB::Load internally.
        void LoadSpecific(LoadType loadType, std::string value) override;
        void SetVisualizationType(VisuType mode) override; // — switch between mesh or vector field.
        void SetCrossSection(const CrossSection& crossSection) override;
        void UpdateView() override; //— triggers the UI to redraw or refresh.
    };
}

void VTK_Presenter::Load()