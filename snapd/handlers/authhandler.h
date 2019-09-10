#pragma once

#include <handlers/autoregisteringhandler.h>

class auth_handler : public auto_registering_handler
{
protected:
    auth_handler(const std::wstring& url)
        : auto_registering_handler(url)
    {
    }

    virtual void onAuthorizedGet(web::http::http_request message, const user& in_user);
    virtual void onUnauthorizedGet(web::http::http_request message);

    virtual void onAuthorizedPut(web::http::http_request message, const user& in_user);
    virtual void onUnauthorizedPut(web::http::http_request message);

private:
    virtual void handleGet(web::http::http_request message) override;
};