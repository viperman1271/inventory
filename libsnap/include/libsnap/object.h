#pragma once

class object
{
public:
    virtual const std::wstring getAll() const = 0;

protected:
    const std::wstring getJsonStr(json_object* jobj) const;
};