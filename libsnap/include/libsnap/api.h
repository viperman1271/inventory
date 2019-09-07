#pragma once

#include <libsnap/object.h>

#include <cassert>
#include <string>
#include <vector>

class api : public object
{
public:
    api() 
    { 
        assert(ms_Instance == nullptr); 
        ms_Instance = this; 
    }

    ~api() 
    { 
        assert(ms_Instance == this);
        ms_Instance = nullptr; 
    }

    virtual const std::wstring getAll() const override;

    void addListener(const std::wstring& in_listener) { m_listeners.push_back(in_listener); }
    void removeListener(const std::wstring& in_listener) 
    { 
        std::vector<std::wstring>::iterator iter = m_listeners.begin();
        while (iter != m_listeners.end())
        {
            if (*iter == in_listener)
            {
                break;
            }
            ++iter;
        }
        if (iter != m_listeners.end())
        {
            m_listeners.erase(iter);
        }
    }

    static api* getInstance() { return ms_Instance; }

private:
    std::vector<std::wstring> m_listeners;

    static api* ms_Instance;
};
