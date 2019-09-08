#pragma once

#include <libsnap/object.h>
#include <chrono>

class session : public object
{
public:
    session()
        : m_UserId(-1)
        , m_SessionKey()
        , m_SessionStartTime(getSecondsSinceEpoch())
    {

    }

    session(const unsigned int in_userId);

    virtual const std::wstring serialize() const override;
    virtual void deserialize(json_object* jobj) override;

    json_object* getJsonObject() const;

    bool isValid() const { return m_UserId != -1 && !m_SessionKey.empty(); }

    unsigned int getUserId() const { return m_UserId; }
    std::string getSessionKey() const { return m_SessionKey; }

    static uint64_t getSecondsSinceEpoch() { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count(); }

private:
    unsigned int m_UserId;
    std::string m_SessionKey;
    uint64_t m_SessionStartTime;
};
