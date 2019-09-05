#pragma once

class auto_registering_handler
{
public:
    pplx::task<void> open() 
    { 
        auto ret = m_listener.open();
        std::wcout << std::wstring(U("Listening for requests at: ")) << getListener().uri().to_string() << std::endl;
        return ret; 
    }
    pplx::task<void> close() { return m_listener.close(); }

    virtual void handleGet(web::http::http_request message) = 0;

protected:
    auto_registering_handler(const std::wstring& url)
        : m_listener(url)
    {
        m_listener.support(web::http::methods::GET, std::bind(&auto_registering_handler::handleGet, this, std::placeholders::_1));
    }

    void init();
    void uninit();

    virtual const std::wstring& getApi() const 
    {
        return m_listener.uri().path();
    }

    web::http::experimental::listener::http_listener& getListener() { return m_listener; }

private:
    web::http::experimental::listener::http_listener m_listener;
};