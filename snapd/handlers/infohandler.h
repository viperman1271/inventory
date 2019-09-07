#pragma once

#include <handlers/autoregisteringhandler.h>
#include <libsnap/info.h>

class info_handler : public auto_registering_handler
{
public:
    info_handler(const std::wstring& url)
        : auto_registering_handler(url)
    {
        init();
    }

    ~info_handler()
    {
        uninit();
    }

protected:
    void handleGet(web::http::http_request message) override
    {
        std::wstring response = info().getAll();
        message.reply(web::http::status_codes::OK, response);
    }
};