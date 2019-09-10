#pragma once

#include <string>
#include <fstream>
#include <json-c/json.h>

class object
{
public:
    virtual const std::wstring serialize() const = 0;

    static void deserialize(object* instance, const char* data) { instance->deserialize(data); }
    static inline void deserialize(object* instance, const std::string& data) { deserialize(instance, data.c_str()); }
    static void deserialize(object* instance, const std::wstring& data);

    static bool deserializeFromFile(object* instance, const std::string& file);

protected:
    const std::wstring getJsonStr(json_object* jobj) const;
    void deserialize(const char* data) { json_object* jobj = json_tokener_parse(data); deserialize(jobj); }
    virtual void deserialize(json_object* jobj) { }
};