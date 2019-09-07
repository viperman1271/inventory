#include <stdafx.h>

#include <objectmodel/info.h>

const std::wstring info::getAll() const
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

    return getJsonStr(jobj);
}
