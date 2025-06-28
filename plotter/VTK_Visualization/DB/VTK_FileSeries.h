#pragma once

#include "IDB.h"
#include <string>
#include <vtkDataSet.h>
#include <vtkSmartPointer.h>

namespace visu
{
    class VTK_FileSeries : public IDB
    {
    public:
        explicit VTK_FileSeries(const std::string& fileSeries);
        void Load() override;
        void LoadSpecific(LoadType loadType, std::string value) override;
        std::unique_ptr< AbstractDB > GetAbstractDb() override;  

    private:
        std::string m_fileSeries;
        vtkSmartPointer<vtkDataSet> m_dataset;
    };
}
