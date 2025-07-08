#include "JSONConfigParser.h"
#include <fstream>
#include <iostream>
#include <algorithm>

JSONConfigParser& JSONConfigParser::Instance() {
    static JSONConfigParser instance;
    return instance;
}

JSONConfigParser::JSONConfigParser()
    : m_visualizationKey("visualization")
    , m_controlsKey("controls") 
    , m_windowPropertiesKey("windowProperties") 
    {}

JSONConfigParser::~JSONConfigParser() = default;

bool JSONConfigParser::LoadConfigFromString(const std::string& jsonStr) {
    try {
        m_json = json::JSON::Load(jsonStr);
        return true;
    } catch (...) {
        std::cerr << "Failed to parse JSON config." << std::endl;
        return false;
    }
}

bool JSONConfigParser::LoadConfigFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        std::cerr << "Cannot open config file: " << filename << std::endl;
        return false;
    }
    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    return LoadConfigFromString(content);
}

void JSONConfigParser::SetRootKey(const std::string& rootKey) {
    //m_rootKey = rootKey;
}

std::string JSONConfigParser::GetValue(const std::string& subConfigKey, const std::string& key) const 
{
    if (!m_json.hasKey(key)) {
        return "";
    }

    const auto& subConfig = m_json.at(key);

    // Since keys are always lowercase, use exact match
    if (subConfig.hasKey(subConfigKey)) 
    {
        return subConfig.at(subConfigKey).ToString();
    }

    return "";
}

std::string JSONConfigParser::GetPressureValue() const {
    return GetValue("pressure", m_visualizationKey);
}

std::string JSONConfigParser::GetVelocityValue() const {
    return GetValue("velocity", m_visualizationKey);
}

std::string JSONConfigParser::GetMeshValue() const {
    return GetValue("mesh", m_visualizationKey);
}

std::string JSONConfigParser::GetVisualizationValue() const {
    return GetValue("visualization", m_controlsKey);
}

// Returns a string representation of the window title
std::string JSONConfigParser::GetWindowTitle() const {
    return GetValue("title", m_windowPropertiesKey);
}

// Returns the background color as a vector of floats/doubles
std::vector<double> JSONConfigParser::GetBackgroundColor() const {
    return GetArrayValue<double>("background", m_windowPropertiesKey);
}

// Returns the window size as a vector of ints
std::vector<int> JSONConfigParser::GetWindowSize() const {
    return GetArrayValue<int>("size", m_windowPropertiesKey);
}

// Returns the mesh color as a vector of floats/doubles
std::vector<double> JSONConfigParser::GetMeshColor() const {
    return GetArrayValue<double>("meshColor", m_windowPropertiesKey);
}

// Returns the pressure hue as a vector of floats/doubles
std::vector<double> JSONConfigParser::GetPressureHue() const {
    return GetArrayValue<double>("pressureHue", m_windowPropertiesKey);
}

// Returns the glyph scale factor as a double
double JSONConfigParser::GetGlyphScaleFactor() const {
    std::string stringValue = GetValue("glyphScaleFactor", m_windowPropertiesKey);
    try {
        return std::stod(stringValue);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid input: not a valid double\n";
    } catch (const std::out_of_range& e) {
        std::cerr << "Invalid input: out of range\n";
    }
    
    return 0.1;
}

std::string JSONConfigParser::ToLower(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return out;
}
