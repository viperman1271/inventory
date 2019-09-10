#include "stdafx.h"

#include <handlers/authhandler.h>
#include <database.h>

#include <libsnap/user.h>

extern std::unique_ptr<database> g_database;

void auth_handler::onAuthorizedGet(web::http::http_request message, const user& in_user)
{
    message.reply(web::http::status_codes::OK);
}

void auth_handler::onUnauthorizedGet(web::http::http_request message)
{
    message.reply(web::http::status_codes::Unauthorized);
}

void auth_handler::onAuthorizedPut(web::http::http_request message, const user& in_user)
{
    message.reply(web::http::status_codes::OK);
}

void auth_handler::onUnauthorizedPut(web::http::http_request message)
{
    message.reply(web::http::status_codes::Unauthorized);
}

void auth_handler::handleGet(web::http::http_request message)
{
    if (message.headers().has(U("SessionHash")))
    {
        auto iter = message.headers().find(U("SessionHash"));
        const std::wstring& sessionHash = iter->second;
        if (const user* _user = g_database->validateSession(sessionHash))
        {
            onAuthorizedGet(message, *_user);
        }
        else
        {
            onUnauthorizedGet(message);
        }
    }
    else
    {
        onUnauthorizedGet(message);
    }
}
