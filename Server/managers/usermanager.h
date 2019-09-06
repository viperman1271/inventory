#pragma once

class user_manager
{
public:
    user_manager()
    {
        assert(ms_Instance == nullptr);
        ms_Instance = this;
    }

    ~user_manager()
    {
        assert(ms_Instance == this);
        ms_Instance = nullptr;
    }

private:
    static user_manager* ms_Instance;
};