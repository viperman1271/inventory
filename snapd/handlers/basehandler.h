#pragma once

#include <handlers/autoregisteringhandler.h>

class base_handler : public auto_registering_handler
{
public:
    base_handler(const std::wstring& url)
        : auto_registering_handler(url)
    {
        init();
    }

    ~base_handler()
    {
        uninit();
    }

protected:
    void handleGet(web::http::http_request message) override
    {
        message.reply(web::http::status_codes::Unauthorized);
    }
};