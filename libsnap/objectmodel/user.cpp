#include <libsnap/user.h>
#include <serialization.h>

user::user()
    : m_UserId(-1)
    , m_PasswordHashed(false)
{

}

const std::wstring user::serialize() const
{
    json_object* jobj = getJsonObject();
    return getJsonStr(jobj);
}

void user::deserialize(json_object* jobj)
{
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
        else if (strcmp(key, "Salt") == 0)
        {
            m_Salt = json_object_get_string(jobjval);
        }
    }
}

json_object* user::getJsonObject() const
{
    json_object* jobj = json_object_new_object();
    {
        serializeValue(jobj, "UserId", m_UserId);
        serializeValue(jobj, "Username", m_Username);
        serializeValue(jobj, "Password", m_Password);
        serializeValue(jobj, "IsHashed", m_PasswordHashed);
        serializeValue(jobj, "Email", m_Email);
        serializeValue(jobj, "Salt", m_Salt);
    }
    return jobj;
}
