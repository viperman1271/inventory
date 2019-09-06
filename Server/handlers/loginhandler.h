#pragma once

#include <handlers/autoregisteringhandler.h>

class login_handler : public auto_registering_handler
{
public:
    login_handler(const std::wstring& url)
        : auto_registering_handler(url)
    {
        init();
    }

    ~login_handler()
    {
        uninit();
    }

protected:
    virtual void handleGet(web::http::http_request message) override;
};