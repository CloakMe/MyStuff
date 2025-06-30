#include "JSONConfigParser.h"
#include <fstream>
#include <iostream>
#include <algorithm>

JSONConfigParser& JSONConfigParser::Instance() {
    static JSONConfigParser instance;
    return instance;
}

JSONConfigParser::JSONConfigParser()
    : m_visualizationKey("visualization"), m_controlsKey("controls") {}

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
    m_visualizationKey = rootKey;
}

std::string JSONConfigParser::GetValue(const std::string& subConfigKey, const std::string& key) {
    if (!m_json.hasKey(key)) {
        return "";
    }

    auto& subConfig = m_json[key];

    // Since keys are always lowercase, use exact match
    if (subConfig.hasKey(subConfigKey)) {
        return subConfig[subConfigKey].ToString();
    }

    return "";
}

std::string JSONConfigParser::GetPressureValue() {
    return GetValue("pressure", m_visualizationKey);
}

std::string JSONConfigParser::GetVelocityValue() {
    return GetValue("velocity", m_visualizationKey);
}

std::string JSONConfigParser::GetMeshValue() {
    return GetValue("mesh", m_visualizationKey);
}

std::string JSONConfigParser::GetVisualizationValue() {
    return GetValue("visualization", m_controlsKey);
}

std::string JSONConfigParser::ToLower(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return out;
}
