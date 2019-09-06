#include "stdafx.h"

#include <objectmodel/object.h>

const std::wstring object::getJsonStr(json_object* jobj) const
{
    const char* jsonString = json_object_to_json_string(jobj);
    const size_t length = strlen(jsonString);

    std::unique_ptr<wchar_t> wcharArray = std::unique_ptr<wchar_t>(new wchar_t[length + 1]);
    memset(wcharArray.get(), 0, (length + 1) * sizeof(wchar_t));

    mbstowcs(wcharArray.get(), jsonString, length);
    return std::wstring(wcharArray.get());
}
