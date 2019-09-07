#pragma once

#include <objectmodel/object.h>

class info : public object
{
public:
    virtual const std::wstring getAll() const override;
};