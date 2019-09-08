#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <iostream>

#include <CLI/CLI.hpp>
#include <libsnap/user.h>

int main(int argc, char** argv)
{
    CLI::App app{"Personal inventory command line application"};

    CLI::App* userCommand = app.add_subcommand("user", "handles user management");
    CLI::App* createCommand = userCommand->add_subcommand("create", "creates a new user");

    std::string username;
    std::string email;
    std::string password;
    createCommand->add_option("--name", username, "create a new user with the given name");
    createCommand->add_option("--email", email, "create a new user with the given name");
    createCommand->add_option("--password", password, "create a new user with the given name");

    CLI::App* loginCommand = userCommand->add_subcommand("login", "logs into the server using provided password");
    loginCommand->add_option("--name", username, "username to use for login");
    loginCommand->add_option("--password", password, "password for the user");

    try 
    {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError& e) 
    {
        return app.exit(e);
    }

    if (createCommand->parsed())
    {
        if(username.size() > 0 && email.size() > 0 && password.size() > 0)
        {
            user user;
            user.setUsername(username);
            user.setEmail(email);
            user.setPassword(password);

            json_object* jobj = user.getJsonObject();
            const char* jsonString = json_object_to_json_string(jobj);

            web::uri_builder uri(U("http://localhost"));
            std::wstring addr = uri.to_uri().to_string();
            web::http::client::http_client client(addr);

            web::http::http_request msg(web::http::methods::PUT);
            msg.set_body(jsonString);

            web::uri_builder builder(U("/user/create"));
            msg.set_request_uri(builder.to_uri());

            auto resp = client.request(msg).get();
        }
    }
    else if (loginCommand->parsed())
    {
        if (username.size() > 0 && password.size() > 0)
        {
            user user;
            user.setUsername(username);
            user.setPassword(password);
            
            json_object* jobj = user.getJsonObject();
            const char* jsonString = json_object_to_json_string(jobj);

            web::uri_builder uri(U("http://localhost"));
            const std::wstring addr = uri.to_uri().to_string();

            web::http::http_request msg(web::http::methods::PUT);
            msg.set_body(jsonString);

            web::uri_builder builder(U("/login"));
            msg.set_request_uri(builder.to_uri());

            web::http::client::http_client client(addr);
            web::http::http_response response = client.request(msg).get();

            if (response.status_code() == web::http::status_codes::OK)
            {
                auto fileStream = std::make_shared<concurrency::streams::ostream>();
                pplx::task<void> requestTask = concurrency::streams::fstream::open_ostream(U("session.json")).then([=](concurrency::streams::ostream outFile)
                {
                    *fileStream = outFile;
                    return response.body().read_to_end(fileStream->streambuf());
                })
                .then([=](size_t)
                {
                    return fileStream->close();
                });
                
                requestTask.wait();
            }
        }
    }

    return 0;
}