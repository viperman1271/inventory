#pragma once

#include <libsnap/object.h>

class info : public object
{
public:
    virtual const std::wstring getAll() const override;
};