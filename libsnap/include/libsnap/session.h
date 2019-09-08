#pragma once

#include <libsnap/object.h>

class session : public object
{
public:
    virtual const std::wstring serialize() const override;
    json_object* getJsonObject() const;

protected:
    virtual void deserialize(const char* data) override;

private:
    unsigned int m_UserId;
    std::string m_SessionKey;
};
