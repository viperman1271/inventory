#pragma once

#include <libsnap/object.h>

#include <json-c/json.h>

class user : public object
{
public:
    virtual const std::wstring getAll() const override;
    json_object* getJsonObject() const;

private:
    unsigned int m_UserId;
    std::string m_Email;
    std::string m_Database;
};