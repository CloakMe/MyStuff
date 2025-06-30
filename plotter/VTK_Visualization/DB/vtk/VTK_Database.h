#pragma once

#include "AbstractDB.h"
#include "IDB.h"
#include <string>
#include <vtkDataSet.h>
#include <vtkSmartPointer.h>

namespace visu
{
    class VTK_Database : public IDB
    {
    public:
        explicit VTK_Database(const std::string& filepath);
        void Load() override;
        void LoadSpecific(LoadType loadType, std::string value) override;
        std::unique_ptr< AbstractDB > GetAbstractDb() override;  

    private:
        std::string m_filepath;
        vtkSmartPointer<vtkDataSet> m_dataset;
    };
}
