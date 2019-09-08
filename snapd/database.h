#pragma once

#include <libsnap/session.h>
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
    bool validateSession(const session& in_session) const;

    session createSession(const user& in_user);

private:
    void writeUsers();
    void writeSessions();

    void loadUsers();
    void loadSessions();

    std::string hashAndEncodePassword(const std::string& in_plainTextPassword, const CryptoPP::SecByteBlock& in_passwordSalt) const;
    std::string encodeString(const CryptoPP::SecByteBlock& in_passwordSalt) const;
    std::string decodeString(const std::string& in_encodedString) const;

    const user* getStoredUser(const user& in_user) const;

private:
    mutable std::recursive_mutex m_Mutex;
    std::vector<user> m_Users;
    std::vector<session> m_Sessions;

    std::ofstream m_UsersFile;
};
