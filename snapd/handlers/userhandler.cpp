#include "stdafx.h"
#include <handlers/userhandler.h>

#include <database.h>

extern std::unique_ptr<database> g_database;

void user_handler::handleGet(web::http::http_request message)
{
    std::wstring response = user().getAll();
    message.reply(web::http::status_codes::OK, response);
}

void user_handler::handlePut(web::http::http_request message)
{
    if (message.request_uri().path() == U("/user/create"))
    {
        std::wstring body = message.extract_string().get();
        
        user user;
        user.setAll(body);

        if (user.isValid() && !g_database->userExists(user))
        {
            g_database->addUser(user);
        }
    }
}