#pragma once

#include <assert.h>

template<class T>
void serializeValue(json_object* jobj, const char* propertyName, const T& value)
{
    assert(false);
}

template<>
void serializeValue(json_object* jobj, const char* propertyName, const int& value)
{
    json_object* intValue = json_object_new_int(value);
    json_object_object_add(jobj, propertyName, intValue);
}

template<>
void serializeValue(json_object* jobj, const char* propertyName, const unsigned int& value)
{
    json_object* intValue = json_object_new_int(value);
    json_object_object_add(jobj, propertyName, intValue);
}

template<>
void serializeValue(json_object* jobj, const char* propertyName, const bool& value)
{
    json_object* boolValue = json_object_new_boolean(value);
    json_object_object_add(jobj, propertyName, boolValue);
}

template<>
void serializeValue(json_object* jobj, const char* propertyName, const std::string& value)
{
    if (!value.empty())
    {
        json_object* strValue = json_object_new_string(value.c_str());
        json_object_object_add(jobj, propertyName, strValue);
    }
}