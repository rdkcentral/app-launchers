#include "JsonConfig.h"
#include "rapidjson/document.h"
#include <fstream>
#include <memory>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <sstream>
#include <utility>
#include <vector>

class JsonConfig::Impl {
public:
    explicit Impl(std::string filename)
        : m_filename(std::move(filename))
    {
    }

    bool Parse()
    {
        std::ifstream file(m_filename);
        if (!file.is_open()) {
            return false;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string jsonStr = buffer.str();

        return !m_document.Parse(jsonStr.c_str()).HasParseError();
    }

    bool Contains(const std::string& key) const
    {
        return GetValueByKey(key) != nullptr;
    }

    std::string GetString(const std::string& key)
    {
        const rapidjson::Value* value = GetValueByKey(key);
        if (!value) {
            return "";
        }

        if (value->IsString()) {
            return value->GetString();
        }

        if (value->IsObject()) {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            value->Accept(writer);
            return buffer.GetString();
        }

        return "";
    }

    double GetNumber(const std::string& key)
    {
        const rapidjson::Value* value = GetValueByKey(key);
        if (!value) {
            return 0.0;
        }

        if (value->IsDouble()) {
            return value->GetDouble();
        }
        if (value->IsInt()) {
            return static_cast<double>(value->GetInt());
        }
        return 0.0;
    }

    bool GetBoolean(const std::string& key)
    {
        const rapidjson::Value* value = GetValueByKey(key);
        if (!value || !value->IsBool()) {
            return false;
        }
        return value->GetBool();
    }

private:
    std::vector<std::string> SplitKey(const std::string& key) const
    {
        std::vector<std::string> parts;
        size_t start = 0;
        size_t end = key.find('.');

        while (end != std::string::npos) {
            parts.push_back(key.substr(start, end - start));
            start = end + 1;
            end = key.find('.', start);
        }
        parts.push_back(key.substr(start));

        return parts;
    }

    const rapidjson::Value* GetValueByKey(const std::string& key) const
    {
        const rapidjson::Value* current = &m_document;

        auto keyParts = SplitKey(key);

        for (const auto& keyPart : keyParts) {
            if (!current->IsObject() || !current->HasMember(keyPart.c_str())) {
                return nullptr;
            }
            current = &((*current)[keyPart.c_str()]);
        }

        return current;
    }

    std::string m_filename;
    rapidjson::Document m_document;
};

JsonConfig::JsonConfig(std::string filename)
    : m_impl(new Impl(std::move(filename)))
{
}

JsonConfig::~JsonConfig() = default;

bool JsonConfig::Parse()
{
    return m_impl->Parse();
}
bool JsonConfig::Contains(const std::string& key) const
{
    return m_impl->Contains(key);
}
std::string JsonConfig::GetString(const std::string& key)
{
    return m_impl->GetString(key);
}
double JsonConfig::GetNumber(const std::string& key)
{
    return m_impl->GetNumber(key);
}
bool JsonConfig::GetBoolean(const std::string& key)
{
    return m_impl->GetBoolean(key);
}