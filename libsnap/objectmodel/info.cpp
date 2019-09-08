#include <libsnap/info.h>

#define PI_MAJOR_VERSION 1
#define PI_MINOR_VERSION 0
#define PI_PATCH_VERSION 0
#define PI_BUILD_VERSION 0

const std::wstring info::serialize() const
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
