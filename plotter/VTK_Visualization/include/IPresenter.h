#pragma once
#include "VisuType.h"
#include "CrossSection.h"

namespace visu
{    
    public class IPresenter
    {
    public:
        void Load();// — calls IDB::Load internally.
        void SelectVisualizationType(VisuType mode);// — switch between mesh or vector field.
        void SetCrossSection(const CrossSection& crossSection);
        void UpdateView(); //— triggers the UI to redraw or refresh.
    };
}
