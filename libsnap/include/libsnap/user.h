#pragma once

#include <libsnap/object.h>

#include <json-c/json.h>

class user : public object
{
public:
    user();

    virtual const std::wstring serialize() const override;
    virtual void deserialize(const char* data) override;

    json_object* getJsonObject() const;

    const unsigned int getUserId() const { return m_UserId; }
    const bool getIsPasswordHashed() const { return m_PasswordHashed; }
    const std::string& getUsername() const { return m_Username; }
    const std::string& getEmail() const { return m_Email; }
    const std::string& getDatabase() const { return m_Database; }
    const std::string& getPassword() const { return m_Password; }
    const std::string& getSalt() const { return m_Salt; }

    void setUserId(const unsigned int userId) { m_UserId = userId; }
    void setUsername(const std::string& username) { m_Username = username; }
    void setEmail(const std::string& email) { m_Email = email; }
    void setPassword(const std::string& password) { m_Password = password; m_PasswordHashed = false; }
    void setPasswordHash(const std::string& password) { m_Password = password; m_PasswordHashed = true; }
    void setSalt(const std::string& salt) { m_Salt = salt; }

    bool isValid() const { return !m_Username.empty() && !m_Password.empty(); }

    inline bool operator==(const user& rhs) const
    {
        return isValid() == rhs.isValid() && m_Username == rhs.m_Username;
    }

private:
    unsigned int m_UserId;
    bool m_PasswordHashed;
    std::string m_Username;
    std::string m_Email;
    std::string m_Database;
    std::string m_Password;
    std::string m_Salt;
};