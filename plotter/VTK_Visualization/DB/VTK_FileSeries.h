#pragma once

#include "IDB.h"
#include <string>

namespace visu
{
    class VTK_FileSeries : public IDB
    {
    public:
        VTK_FileSeries(const std::string& fileSeries);
        void Load() override;
        void LoadSpecific(LoadType loadType, std::string value) override;
    private:
        std::string m_fileSeries;
    };
}
