#pragma once

#include <libsnap/object.h>

class login : public object
{
public:
    virtual const std::wstring getAll() const override;
    json_object* getJsonObject() const;

protected:
    virtual void handleSetAll(const char* data) override;

private:
    unsigned int m_UserId;
    std::string m_SessionKey;
};
