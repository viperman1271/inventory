#pragma once

#include <libsnap/object.h>

class session : public object
{
public:
    session()
        : m_UserId(-1)
        , m_SessionKey()
    {

    }

    session(const unsigned int in_userId, const std::string& in_sessionKey)
        : m_UserId(in_userId)
        , m_SessionKey(in_sessionKey)
    {

    }

    virtual const std::wstring serialize() const override;
    json_object* getJsonObject() const;

    bool isValid() const { return m_UserId != -1 && !m_SessionKey.empty(); }

    unsigned int getUserId() const { return m_UserId; }
    std::string getSessionKey() const { return m_SessionKey; }

protected:
    virtual void deserialize(json_object* jobj) override;

private:
    unsigned int m_UserId;
    std::string m_SessionKey;
};
