#pragma once

#include <string>
#include "json.h"  // Include your simple JSON parser header here

class JSONConfigParser {
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
    std::string GetValue(const std::string& subConfigKey, const std::string& key);


    // Convenience getters for known keys
    std::string GetPressureValue();
    std::string GetVelocityValue();
    std::string GetMeshValue();
    // Example getter for controls sub-configuration (optional)
    std::string GetVisualizationValue();
private:
    JSONConfigParser();
    ~JSONConfigParser();

    // Disable copy and assignment
    JSONConfigParser(const JSONConfigParser&) = delete;
    JSONConfigParser& operator=(const JSONConfigParser&) = delete;

    static std::string ToLower(const std::string& s);

    json::JSON m_json;  // Your JSON object from simple JSON parser
    
    std::string m_visualizationKey;  // e.g. "visualization"
    std::string m_controlsKey;   // e.g. "controls"
};
