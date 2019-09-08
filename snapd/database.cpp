#include "stdafx.h"
#include "database.h"

#include <utilities/fileutilities.h>
#include <utilities/mutexutilities.h>

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

bool database::userExists(const user& in_User) const
{
    auto_lock<std::recursive_mutex> lock(m_Mutex);

    for (const user& _user : m_Users)
    {
        if (_user == in_User)
        {
            return true;
        }
    }

    return false;
}

void database::addUser(const user& in_user)
{
    auto_lock<std::recursive_mutex> lock(m_Mutex);

    user _user(in_user);

    if (m_Users.empty())
    {
        _user.setUserId(1);
    }
    else
    {
        const unsigned int lastUserId = m_Users.back().getUserId();
        _user.setUserId(lastUserId + 1);
    }
    
    m_Users.push_back(_user);

    writeUsers();
}

void database::writeUsers()
{
    auto_lock<std::recursive_mutex> lock(m_Mutex);

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