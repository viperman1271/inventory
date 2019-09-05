#include <stdafx.h>

#include <objectmodel/api.h>

api* api::ms_Instance = nullptr;

const std::wstring api::getAll()
{
    json_object* jobj = json_object_new_object();
    {
        json_object* jarray = json_object_new_array();

        for (const std::wstring& apiEntry : m_listeners)
        {
            std::unique_ptr<char> charArray = std::unique_ptr<char>(new char[apiEntry.size() + 1]);
            memset(charArray.get(), 0, (apiEntry.size() + 1) * sizeof(char));

            wcstombs(charArray.get(), apiEntry.c_str(), apiEntry.size());

            json_object* jstring = json_object_new_string(charArray.get());
            json_object_array_add(jarray, jstring);
        }

        json_object_object_add(jobj, "apis", jarray);
    }

    const char* jsonString = json_object_to_json_string(jobj);
    const size_t length = strlen(jsonString);

    std::unique_ptr<wchar_t> wcharArray = std::unique_ptr<wchar_t>(new wchar_t[length + 1]);
    memset(wcharArray.get(), 0, (length + 1) * sizeof(wchar_t));

    mbstowcs(wcharArray.get(), jsonString, length);
    return std::wstring(wcharArray.get());
}
