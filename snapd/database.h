#pragma once

#include <libsnap/user.h>

class database
{
public:
    database();
    ~database();

    bool userExists(const user& user) const;
    void addUser(const user& user);

private:
    void writeUsers();

private:
    mutable std::recursive_mutex m_Mutex;
    std::vector<user> m_Users;

    std::ofstream m_UsersFile;
};
