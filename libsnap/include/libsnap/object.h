#pragma once

#include <string>
#include <json-c/json.h>

class object
{
public:
    virtual const std::wstring serialize() const = 0;

    static void deserialize(object* instance, const char* data) { instance->deserialize(data); }
    static inline void deserialize(object* instance, const std::string& data) { deserialize(instance, data.c_str()); }
    static inline void deserialize(object* instance, const std::wstring& data)
    {
        std::unique_ptr<char> pszData(new char[data.size() + 1]);
        wcstombs(pszData.get(), data.c_str(), data.size() + 1);
        instance->deserialize(pszData.get());
    }

protected:
    const std::wstring getJsonStr(json_object* jobj) const;
    virtual void deserialize(const char* data) {}
};