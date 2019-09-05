#include <stdafx.h>

#include "handlers/basehandler.h"
#include "handlers/apihandler.h"
#include "handlers/infohandler.h"

#include "objectmodel/api.h"

std::vector<std::unique_ptr<auto_registering_handler>> g_handlers;
std::unique_ptr<api> g_api;

void onInitialize(const std::wstring& address)
{
    g_api = std::unique_ptr<api>(new api());
    {
        web::uri_builder uri(address);
        std::wstring addr = uri.to_uri().to_string();

        g_handlers.push_back(std::unique_ptr<auto_registering_handler>(new base_handler(addr)));
        g_handlers.back()->open().wait();
    }

    {
        web::uri_builder uri(address);
        uri.set_path(U("/api/v1"));

        std::wstring addr = uri.to_uri().to_string();
        g_handlers.push_back(std::unique_ptr<auto_registering_handler>(new api_handler(addr)));
        g_handlers.back()->open().wait();
    }

    {
        web::uri_builder uri(address);
        uri.set_path(U("/info"));

        std::wstring addr = uri.to_uri().to_string();
        g_handlers.push_back(std::unique_ptr<auto_registering_handler>(new info_handler(addr)));
        g_handlers.back()->open().wait();
    }
}

// void onInitialize2(const std::wstring& address)
// {
//     web::uri_builder uri(address);
// 
//     uri.set_path(U("/api/v1"));
// 
//     auto addr = uri.to_uri().to_string();
//     g_apiHttpHandler = std::unique_ptr<rest_handler>(new rest_handler(addr));
//     g_apiHttpHandler->open().wait();
// 
//     std::wcout << std::wstring(U("Listening for requests at: ")) << addr << std::endl;
// 
//     g_api.reset();
// 
//     return;
// }

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