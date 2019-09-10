#pragma once

#pragma once

#include <handlers/authhandler.h>
#include <libsnap/user.h>

class user_handler : public auth_handler
{
public:
    user_handler(const std::wstring& url)
        : auth_handler(url)
    {
        init();
    }

    ~user_handler()
    {
        uninit();
    }

protected:
    void onAuthorizedGet(web::http::http_request message, const user& in_user) override;
    void onUnauthorizedPut(web::http::http_request message) override;
};