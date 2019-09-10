#include "stdafx.h"
#include <handlers/userhandler.h>

#include <database.h>

extern std::unique_ptr<database> g_database;

void user_handler::onAuthorizedGet(web::http::http_request message, const user& in_user)
{
    user cleanedUser(in_user);
    cleanedUser.setPassword("");
    cleanedUser.setSalt("");

    std::wstring response = cleanedUser.serialize();
    message.reply(web::http::status_codes::OK, response);
}

void user_handler::onUnauthorizedPut(web::http::http_request message)
{
    if (message.request_uri().path() == U("/user/create"))
    {
        std::wstring body = message.extract_string().get();
        
        user user;
        object::deserialize(&user, body);

        if (!user.isValid())
        {

        }
        else if (g_database->userExists(user))
        {

        }
        else if (!g_database->addUser(user))
        {
            message.reply(web::http::status_codes::InternalError);
        }
        else
        {
            message.reply(web::http::status_codes::OK);
        }
    }
}