#pragma once

#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>

namespace own
{
    std::string GET(std::string const& URL)
    {
        std::stringstream headers { "Server: SK inf1412(54|69)\n" };
        
        std::time_t t = std::time(nullptr);
        headers << "Date: " << std::put_time(std::gmtime(&t), "%c %Z") << "\n";
        
        if (std::ifstream in(URL, std::ios::in); in)
        {
            std::stringstream buffer;
            buffer << in.rdbuf();

            headers << "Content-Type: text;\n";
            headers << "Content-Length: " << buffer.str().size() << "\n\n";

            return "HTTP/1.1 200 OK\n" + headers.str() + buffer.str();
        }
        else
        {
            return "HTTP/1.1 404 Not Found\n" + headers.str();
        }
    }

} // namespace own
