#include "stdafx.h"

#include <objectmodel/user.h>

const std::wstring user::getAll() const
{
    json_object* jobj = json_object_new_object();
    {
        json_object_object_add(jobj, "UserId", json_object_new_int(m_UserId));
        json_object_object_add(jobj, "Email", json_object_new_int(m_UserId));
    }

    return getJsonStr(jobj);
}