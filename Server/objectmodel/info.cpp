#include <stdafx.h>

#include <objectmodel/info.h>

const std::wstring info::getAll()
{
    json_object* jobj = json_object_new_object();
    {
        json_object* jversion = json_object_new_object();
        {
            json_object_object_add(jversion, "Major", json_object_new_int(PI_MAJOR_VERSION));
            json_object_object_add(jversion, "Minor", json_object_new_int(PI_MINOR_VERSION));
            json_object_object_add(jversion, "Patch", json_object_new_int(PI_BUILD_VERSION));
            json_object_object_add(jversion, "Build", json_object_new_int(PI_BUILD_VERSION));
        }
        json_object_object_add(jobj, "Version", jversion);
    }

    const char* jsonString = json_object_to_json_string(jobj);
    const size_t length = strlen(jsonString);

    std::unique_ptr<wchar_t> wcharArray = std::unique_ptr<wchar_t>(new wchar_t[length + 1]);
    memset(wcharArray.get(), 0, (length + 1) * sizeof(wchar_t));

    mbstowcs(wcharArray.get(), jsonString, length);
    return std::wstring(wcharArray.get());
}
