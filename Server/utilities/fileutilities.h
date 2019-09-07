#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace file
{
    class utils
    {
    public:
        static bool fileExists(const std::string& path)
        {
            std::ifstream file(path);
            return file.is_open();
        }
    };
}