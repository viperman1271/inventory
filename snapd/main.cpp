#include <stdafx.h>

#include "handlers/apihandler.h"
#include "handlers/basehandler.h"
#include "handlers/infohandler.h"
#include "handlers/loginhandler.h"
#include "handlers/userhandler.h"

#include "managers/usermanager.h"

#include <libsnap/api.h>

#include "database.h"

std::vector<std::unique_ptr<auto_registering_handler>> g_handlers;
std::unique_ptr<api> g_api;
std::unique_ptr<user_manager> g_userManager;
std::unique_ptr<database> g_database;

template<class T>
void createHandler(const std::wstring& address, const std::wstring& path)
{
    web::uri_builder uri(address);
    uri.set_path(path);
    std::wstring addr = uri.to_uri().to_string();

    g_handlers.push_back(std::unique_ptr<auto_registering_handler>(new T(addr)));
    g_handlers.back()->open().wait();
}

void onInitialize(const std::wstring& address)
{
    g_api.reset(new api());
    g_userManager.reset(new user_manager());
    g_database.reset(new database());

    createHandler<base_handler>(address, U(""));
    createHandler<api_handler>(address, U("/api/v1"));
    createHandler<info_handler>(address, U("/info"));
    createHandler<user_handler>(address, U("/user"));
    createHandler<login_handler>(address, U("/login"));
}

void onShutdown()
{
    for (std::unique_ptr<auto_registering_handler>& handler : g_handlers)
    {
        assert(handler != nullptr);
        handler->close().wait();
    }
}

int main()
{
    std::wstring address = U("http://127.0.0.1");

    onInitialize(address);
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    onShutdown();

    return 0;
}