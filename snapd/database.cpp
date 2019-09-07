#include "stdafx.h"
#include "database.h"

#include <utilities/fileutilities.h>

#include <libsnap/user.h>

database::database()
{
    if (!file::utils::fileExists("users.json"))
    {
        writeUsers();
    }
}

database::~database()
{

}

void database::writeUsers()
{
    json_object* jobj = json_object_new_object();
    json_object* jarray = json_object_new_array();
    {
        for (const user& _user : m_Users)
        {
            json_object_array_add(jarray, _user.getJsonObject());
        }
    }
    json_object_object_add(jobj, "Users", jarray);

    const char* jsonString = json_object_to_json_string(jobj);

    m_UsersFile = std::ofstream("users.json");
    m_UsersFile.write(jsonString, strlen(jsonString));
    m_UsersFile.close();
}