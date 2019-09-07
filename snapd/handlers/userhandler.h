#pragma once

#pragma once

#include <handlers/autoregisteringhandler.h>
#include <libsnap/user.h>

class user_handler : public auto_registering_handler
{
public:
    user_handler(const std::wstring& url)
        : auto_registering_handler(url)
    {
        init();
    }

    ~user_handler()
    {
        uninit();
    }

protected:
    void handleGet(web::http::http_request message) override;
    void handlePut(web::http::http_request message) override;
};