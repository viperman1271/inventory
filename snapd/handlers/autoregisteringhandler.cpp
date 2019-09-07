#include <stdafx.h>

#include <handlers/autoregisteringhandler.h>
#include <libsnap/api.h>

void auto_registering_handler::init()
{
    const std::wstring& api = this->getApi();
    api::getInstance()->addListener(api);
}

void auto_registering_handler::uninit()
{
    const std::wstring& api = getApi();
    api::getInstance()->removeListener(api);
}
