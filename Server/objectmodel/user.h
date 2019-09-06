#pragma once

#include <objectmodel/object.h>

class user : public object
{
public:
    virtual const std::wstring getAll() const override;

private:
    unsigned int m_UserId;
    std::wstring m_Email;
};