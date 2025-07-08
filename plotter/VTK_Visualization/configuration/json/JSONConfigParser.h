#pragma once

#include "IConfigurator.h"
#include "json.h" // Include your simple JSON parser header here

#include <string>

class JSONConfigParser : public IConfigurator
{
public:
    // Get singleton instance
    static JSONConfigParser& Instance();

    // Load JSON config from string or file
    bool LoadConfigFromString(const std::string& jsonStr);
    bool LoadConfigFromFile(const std::string& filename);

    // Set the root key for sub-configuration (e.g. "visualization")
    void SetRootKey(const std::string& rootKey);

    // Get configured value for a key (case-insensitive)
    // Unified GetValue method with subConfigKey parameter
    std::string GetValue(const std::string& subConfigKey, const std::string& key) const;

    // Convenience getters for known keys
    std::string GetPressureValue() const override;
    std::string GetVelocityValue() const override;
    std::string GetMeshValue() const override;
    // Example getter for controls sub-configuration (optional)
    std::string GetVisualizationValue() const override;
    // Returns a string representation of the window title
    std::string GetWindowTitle() const override;
    // Returns the background color as a vector of floats/doubles
    std::vector<double> GetBackgroundColor() const override;
    // Returns the window size as a vector of ints
    std::vector<int> GetWindowSize() const override;
    // Returns the mesh color as a vector of floats/doubles
    std::vector<double> GetMeshColor() const override;
    // Returns the pressure hue as a vector of floats/doubles
    std::vector<double> GetPressureHue() const override;
    // Returns the glyph scale factor as a double
    double GetGlyphScaleFactor() const override;

private:
    JSONConfigParser();
    ~JSONConfigParser();

    // Disable copy and assignment
    JSONConfigParser(const JSONConfigParser&) = delete;
    JSONConfigParser& operator=(const JSONConfigParser&) = delete;

    static std::string ToLower(const std::string& s);
    template <typename T>
    std::vector<T> GetArrayValue(const std::string& key, const std::string& parentKey) const;
    
    json::JSON m_json; // Your JSON object from simple JSON parser

    std::string m_visualizationKey; // e.g. "visualization"
    std::string m_controlsKey;      // e.g. "controls"
    std::string m_windowPropertiesKey;      // e.g. "controls"
};

template <typename T>
std::vector<T> JSONConfigParser::GetArrayValue(const std::string& key, const std::string& parentKey) const {
    std::vector<T> result;

    // Check if parent key exists and is an object
    if (!m_json.hasKey(parentKey)) {
        return result; // empty vector if parent missing
    }

    const json::JSON& parent = m_json.at(parentKey);
    if (parent.JSONType() != json::JSON::Class::Object) {
        return result; // parent not an object
    }

    // Check if key exists and is an array
    if (!parent.hasKey(key)) {
        return result; // key missing
    }

    const json::JSON& arrayJson = parent.at(key);
    if (arrayJson.JSONType() != json::JSON::Class::Array) {
        return result; // not an array
    }

    // Iterate over array elements and convert to T
    for (size_t i = 0; i < arrayJson.size(); ++i) {
        const json::JSON& elem = arrayJson.at(i);

        // Handle numeric conversions if T is double or int
        if constexpr (std::is_same_v<T, double>) {
            if (elem.JSONType() == json::JSON::Class::Floating) {
                result.push_back(elem.ToFloat());
            } else if (elem.JSONType() == json::JSON::Class::Integral) {
                result.push_back(static_cast<double>(elem.ToInt()));
            }
            // else ignore or throw
        }
        else if constexpr (std::is_same_v<T, int>) {
            if (elem.JSONType() == json::JSON::Class::Integral) {
                result.push_back(elem.ToInt());
            }
            else if (elem.JSONType() == json::JSON::Class::Floating) {
                result.push_back(static_cast<int>(elem.ToFloat()));
            }
            // else ignore or throw
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            if (elem.JSONType() == json::JSON::Class::String) {
                result.push_back(elem.ToString());
            }
            // else ignore or throw
        }
        else if constexpr (std::is_same_v<T, bool>) {
            if (elem.JSONType() == json::JSON::Class::Boolean) {
                result.push_back(elem.ToBool());
            }
            // else ignore or throw
        }
        else {
            // else ignore or throw
        }
    }

    return result;
}
