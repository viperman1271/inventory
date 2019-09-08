#include <libsnap/user.h>

user::user()
    : m_UserId(-1)
    , m_PasswordHashed(false)
{

}

const std::wstring user::getAll() const
{
    json_object* jobj = getJsonObject();
    return getJsonStr(jobj);
}

void user::handleSetAll(const char* data)
{
    json_object* jobj = json_tokener_parse(data);
    json_object_object_foreach(jobj, key, val)
    {
        json_object* jobjval = json_object_object_get(jobj, key);
        if (strcmp(key, "UserId") == 0)
        {
            m_UserId = json_object_get_int(jobjval);
        }
        else if (strcmp(key, "Username") == 0)
        {
            m_Username = json_object_get_string(jobjval);
        }
        else if (strcmp(key, "Password") == 0)
        {
            m_Password = json_object_get_string(jobjval);
        }
        else if (strcmp(key, "IsHashed") == 0)
        {
            m_PasswordHashed = json_object_get_boolean(jobjval);
        }
        else if (strcmp(key, "Email") == 0)
        {
            m_Email = json_object_get_string(jobjval);
        }
    }
}

json_object* user::getJsonObject() const
{
    json_object* jobj = json_object_new_object();
    {
        json_object_object_add(jobj, "UserId", json_object_new_int(m_UserId));
        json_object_object_add(jobj, "Username", json_object_new_string(m_Username.c_str()));
        json_object_object_add(jobj, "Password", json_object_new_string(m_Password.c_str()));
        json_object_object_add(jobj, "IsHashed", json_object_new_boolean(m_PasswordHashed));
        json_object_object_add(jobj, "Email", json_object_new_string(m_Email.c_str()));
        json_object_object_add(jobj, "Salt", json_object_new_string(m_Salt.c_str()));
    }
    return jobj;
}
