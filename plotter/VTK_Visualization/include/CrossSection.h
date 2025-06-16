#pragma once

namespace visu
{
    enum Cross
    {
        Xfixed,
        Yfixed,
        Zfixed,
        Count
    };
    
    public struct CrossSection
    {
        Cross cross;
        double value;
    };
}