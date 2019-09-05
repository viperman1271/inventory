#pragma once

#include <handlers/autoregisteringhandler.h>
#include <objectmodel/api.h>

class api_handler : public auto_registering_handler
{
public:
    api_handler(const std::wstring& url)
        : auto_registering_handler(url)
    {
        init();
    }

    ~api_handler()
    {
        uninit();
    }

protected:
    void handleGet(web::http::http_request message) override
    {
        std::wstring response = api::getInstance()->getAll();
        message.reply(web::http::status_codes::OK, response);
    }
};