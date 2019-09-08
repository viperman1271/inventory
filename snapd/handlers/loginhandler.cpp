#include "stdafx.h"

#include <handlers/loginhandler.h>
#include <libsnap/user.h>

#include <database.h>

extern std::unique_ptr<database> g_database;

void login_handler::handleGet(web::http::http_request message)
{
    std::wstring response = user().serialize();
    message.reply(web::http::status_codes::OK, response);
}

void login_handler::handlePut(web::http::http_request message)
{
    std::wstring body = message.extract_string().get();

    user _user;
    object::deserialize(&_user, body);

    if (!g_database->validatePassword(_user))
    {
        message.reply(web::http::status_codes::Unauthorized);
    }
    else
    {
        session session = g_database->createSession(_user);
        message.reply(web::http::status_codes::OK, session.serialize());
    }
}
