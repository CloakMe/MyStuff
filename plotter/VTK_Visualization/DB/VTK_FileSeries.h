#pragma once

#include "VTK_FileLoader.h"
#include <string>
#include <vtkDataSet.h>
#include <vtkSmartPointer.h>

namespace visu
{
    class VTK_FileSeries : public VTK_FileLoader
    {
    public:
        explicit VTK_FileSeries(const std::string& fileSeries);
        void Load() override;
        void LoadSpecific(LoadType loadType, std::string value) override;
        vtkSmartPointer<vtkDataSet> getDataSet() const override;  

    private:
        std::string m_fileSeries;
        vtkSmartPointer<vtkDataSet> m_dataset;
    };
}
