#include "CobaltConfig.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <fstream>
#include <iostream>

CobaltConfig::CobaltConfig(std::string path)
    : m_path(std::move(path))
{
}

bool CobaltConfig::Parse()
{
    std::cout << "Parsing Cobalt config...\n";

    std::ifstream ifs(m_path);
    if (!ifs.is_open()) {
        std::cerr << "Error: Cannot open file: " << m_path << "\n";
        return false;
    }

    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document doc;
    doc.ParseStream(isw);

    if (doc.HasParseError()) {
        std::cerr << "Error: JSON parse error at offset " << doc.GetErrorOffset()
                  << ", error code: " << doc.GetParseError() << "\n";
        return false;
    }

    if (!doc.HasMember("configuration") || !doc["configuration"].IsObject()) {
        std::cerr << "Error: Missing or invalid 'configuration' section\n";
        return false;
    }

    const auto& config = doc["configuration"];

    auto valueToString = [](const auto& val) -> std::string {
        if (val.IsString()) {
            return val.GetString();
        }
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        val.Accept(writer);
        std::string str = buffer.GetString();
        return buffer.GetString();
    };

    for (auto it = config.MemberBegin(); it != config.MemberEnd(); ++it) {
        std::string key = it->name.GetString();
        std::string value = valueToString(it->value);

        m_configuration[key] = value;
        std::cout << "Parsed: " << key << " = " << value << "\n";
    }

    return true;
}

const CobaltConfig::ConfigurationMap& CobaltConfig::GetConfiguration() const
{
    return m_configuration;
}
