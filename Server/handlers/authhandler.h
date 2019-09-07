#pragma once

#include <handlers/autoregisteringhandler.h>

class auth_handler : public auto_registering_handler
{
public:

protected:
    virtual void handleAuthenticatedGet(web::http::http_request message) = 0;

private:
    virtual void handleGet(web::http::http_request message) override;
};