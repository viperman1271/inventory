#include <libsnap/login.h>

const std::wstring login::getAll() const
{
    json_object* jobj = getJsonObject();
    return getJsonStr(jobj);
}

json_object* login::getJsonObject() const
{
    json_object* jobj = json_object_new_object();
    {
        json_object_object_add(jobj, "UserId", json_object_new_int(m_UserId));
        json_object_object_add(jobj, "SessionKey", json_object_new_string(m_SessionKey.c_str()));
    }
    return jobj;
}

void login::handleSetAll(const char* data)
{
    json_object* jobj = json_tokener_parse(data);
    json_object_object_foreach(jobj, key, val)
    {
        json_object* jobjval = json_object_object_get(jobj, key);
        if (strcmp(key, "UserId") == 0)
        {
            m_UserId = json_object_get_int(jobjval);
        }
        else if (strcmp(key, "SessionKey") == 0)
        {
            m_SessionKey = json_object_get_string(jobjval);
        }
    }
}