#pragma once
#include "VisuType.h"
#include "CrossSection.h"
#include "IDB.h"

namespace visu
{    
    class IPresenter
    {
    public:
        virtual void Load() = 0;// — calls IDB::Load internally.
        virtual void LoadSpecific(LoadType loadType, std::string value) = 0;
        virtual void SetVisualizationType(VisuType mode) = 0;// — switch between mesh or vector field.
        virtual void SetCrossSection(const CrossSection& crossSection) = 0;
        virtual void UpdateView() = 0; //— triggers the UI to redraw or refresh.
    };
}
