#pragma once

#include <objectmodel/user.h>

class database
{
public:
    database();
    ~database();

    const bool userExists(const std::string& username) const;
    void addUser(const std::string& username);

private:
    void writeUsers();

private:
    std::mutex m_Mutex;
    std::vector<user> m_Users;

    std::ofstream m_UsersFile;
};
