#pragma once

template<class T>
class auto_lock
{
public:
    auto_lock(T& mutex)
        : m_Mutex(mutex)
    {
        m_Mutex.lock();
    }

    ~auto_lock()
    {
        m_Mutex.unlock();
    }

private:
    T& m_Mutex;
};
