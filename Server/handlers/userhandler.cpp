#include "stdafx.h"
#include <handlers/userhandler.h>

void user_handler::handleGet(web::http::http_request message)
{
    std::wstring response = user().getAll();
    message.reply(web::http::status_codes::OK, response);
}
