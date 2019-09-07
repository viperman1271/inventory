#include "stdafx.h"

#include <handlers/loginhandler.h>
#include <objectmodel/user.h>

void login_handler::handleGet(web::http::http_request message)
{
    std::wstring response = user().getAll();
    message.reply(web::http::status_codes::OK, response);
}
