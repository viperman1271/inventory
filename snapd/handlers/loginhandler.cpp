#include "stdafx.h"

#include <handlers/loginhandler.h>
#include <libsnap/user.h>

void login_handler::handleGet(web::http::http_request message)
{
    std::wstring response = user().serialize();
    message.reply(web::http::status_codes::OK, response);
}
