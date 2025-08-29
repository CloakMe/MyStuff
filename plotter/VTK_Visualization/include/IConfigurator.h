#ifndef ICONFIGURATOR_H
#define ICONFIGURATOR_H

#include <string>
#include <vector>

class IConfigurator {
public:
    virtual ~IConfigurator() = default;

    // Convenience getters for known keys
    virtual std::string GetPressureValue() const =0;
    virtual std::string GetVelocityValue() const =0;
    virtual std::string GetMeshValue() const =0;

    // Control key for changing the visualization type: Mesh, Pressure, Velo
    virtual std::string GetVisualizationCtrl() const =0;
    
    // Control key for changing the cross-section/cut axis
    virtual std::string GetCutAxisCtrl() const =0;

    // Returns a string representation of the window title
    virtual std::string GetWindowTitle() const =0;

    // Returns the background color as a vector of doubles
    virtual std::vector<double> GetBackgroundColor() const =0;

    // Returns the window size as a vector of ints
    virtual std::vector<int> GetWindowSize() const =0;

    // Returns the mesh color as a vector of doubles
    virtual std::vector<double> GetMeshColor() const =0;

    // Returns the pressure hue as a vector of doubles
    virtual std::vector<double> GetPressureHue() const =0;

    // Returns the glyph scale factor as a double
    virtual double GetGlyphScaleFactor() const =0;
};

#endif // ICONFIGURATOR_H
