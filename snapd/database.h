#pragma once

#include <libsnap/user.h>

#include <cryptopp/secblock.h>

class database
{
public:
    database();
    ~database();

    bool userExists(const user& in_user) const;
    bool addUser(const user& in_user);
    bool validatePassword(const user& in_user) const;

private:
    void writeUsers();
    void loadUsers();

    std::string hashAndEncodePassword(const std::string& in_plainTextPassword, const CryptoPP::SecByteBlock& in_passwordSalt) const;
    std::string encodeString(const CryptoPP::SecByteBlock& in_passwordSalt) const;
    std::string decodeString(const std::string& in_encodedString) const;

    const user* getStoredUser(const user& in_user) const;

private:
    mutable std::recursive_mutex m_Mutex;
    std::vector<user> m_Users;

    std::ofstream m_UsersFile;
};
