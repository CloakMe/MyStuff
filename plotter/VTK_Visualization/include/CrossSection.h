#pragma once

namespace visu
{
    enum struct Cross
    {
        Xfixed,
        Yfixed,
        Zfixed,
        Count
    };
    
    struct CrossSection
    {
        Cross cross;
        double value;
    };
}