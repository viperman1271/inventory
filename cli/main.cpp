#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <iostream>

#include <CLI/CLI.hpp>

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

    try 
    {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError& e) 
    {
        return app.exit(e);
    }

    //Create new user
    if (username.size() > 0 && email.size() > 0 && password.size() > 0)
    {

    }

    return 0;
}