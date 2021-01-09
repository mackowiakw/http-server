#pragma once

#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include "config.hpp"
#include "stringHelper.cpp"

namespace own
{
    auto GET(std::string const& URL)
    {
        auto headers = own::getBasicHeaders();

        if (std::filesystem::is_directory(URL))
        {
            std::string body;
            body += own::findAndReplaceAll(URL, ROOT_FOLDER, "");
            body += " is not a file, it's a directory";

            headers << "Content-Type: text;\n";
            headers << "Content-Length: " << body.size() << "\n\n";

            return "HTTP/1.1 302 Found\n" + headers.str() + body;
        }

        if (std::filesystem::exists(URL))
        {
            headers << "Content-Type: text;\n";
            headers << "Content-Length: " << std::filesystem::file_size(URL) << "\n\n";

            std::stringstream body;
            body << std::ifstream(URL).rdbuf();

            return "HTTP/1.1 200 OK\n" + headers.str() + body.str();
        }

        return "HTTP/1.1 404 Not Found\n" + headers.str();
    }


    auto HEAD(std::string const& URL)
    {
        return own::getHttpRequestHeaders(own::GET(URL)) + "\n";
    }


    auto PUT(std::string const& URL, std::string const& body)
    {
        auto headers = own::getBasicHeaders();

        if (std::filesystem::exists(URL))
        {
            return "HTTP/1.1 304 Not Modified\n" + headers.str();
        }

        // create folder if URL doesn't conaint a '.' (dot) character
        if (URL.find(".") == std::string::npos)
        {
            try {
                std::filesystem::create_directory(URL);
            }
            catch(...) {
                // Possible when it's tried to create 2 folders in one time
                return "HTTP/1.1 300 Multiple Choices\n" + headers.str();
            } 

            return "HTTP/1.1 201 Created\n" + headers.str();
        }

        if (std::ofstream fout(URL); fout)
        {
            fout << body;
            fout.close();

            headers << "Content-Location: " << own::findAndReplaceAll(URL, ROOT_FOLDER, "") << "\n";

            return "HTTP/1.1 201 Created\n" + headers.str() + "\n";
        }

        // When it's tried to create a file in non existing folder
        return "HTTP/1.1 400 Bad Request\n" + headers.str();
    }


    auto DELETE(std::string const& URL)
    {
        auto headers = own::getBasicHeaders();
        
        try
        {
            if (std::filesystem::remove(URL))
            {
                return "HTTP/1.1 200 OK\n" + headers.str();
            }
        }
        catch (...)
        {
            // When directory is not empty
            return "HTTP/1.1 304 Not Modified\n" + headers.str();
        }

        return "HTTP/1.1 204 No Content\n" + headers.str();
    }

} // namespace own
