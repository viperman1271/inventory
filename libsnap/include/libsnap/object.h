#pragma once

#include <string>
#include <json-c/json.h>

class object
{
public:
    virtual const std::wstring getAll() const = 0;
    inline void setAll(const char* data) { handleSetAll(data); }
    inline void setAll(const std::string& data) { setAll(data.c_str()); }
    inline void setAll(const std::wstring& data) 
    {
        std::unique_ptr<char> pszData(new char[data.size() + 1]);
        wcstombs(pszData.get(), data.c_str(), data.size() + 1);
        setAll(pszData.get());
    }

protected:
    const std::wstring getJsonStr(json_object* jobj) const;
    virtual void handleSetAll(const char* data) {}
};