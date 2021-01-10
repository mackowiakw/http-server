#pragma once

#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>

#include "config.hpp"
#include "httpRequest.cpp"
#include "httpResponse.cpp"
#include "stringHelper.cpp"

namespace own
{

    auto GET(std::string const &URL)
    {
        if (std::string body; std::filesystem::is_directory(URL))
        {
            body += findAndReplaceAll(URL, ROOT_FOLDER, "");
            body += " is not a file, it's a directory";

            std::stringstream headers;
            headers << "Content-Type: text;\n";
            headers << "Content-Length: " << body.size() << "\n\n";

            return response(302) + headers.str() + body;
        }

        if (std::stringstream headers; std::filesystem::exists(URL))
        {
            headers << "Content-Type: text;\n";
            headers << "Content-Length: " << std::filesystem::file_size(URL) << "\n\n";

            std::stringstream body;
            body << std::ifstream(URL).rdbuf();

            return response(200) + headers.str() + body.str();
        }

        return response(404);
    }

    auto HEAD(std::string const &URL)
    {
        return getHttpRequestHeaders(GET(URL)) + "\n";
    }

    auto PUT(std::string const &URL, std::string const &body)
    {
        if (std::filesystem::exists(URL))
        {
            return response(304);
        }

        // create folder if URL doesn't contain a '.' (dot) character
        if (URL.find(".") == std::string::npos)
        {
            try
            {
                std::filesystem::create_directory(URL);
            }
            catch (...)
            {
                // When it's tried to create many folders in one time
                return response(300);
            }

            // When success
            return response(201);
        }

        if (std::ofstream fout(URL); fout)
        {
            fout << body;
            fout.close();

            std::stringstream headers;
            headers << "Content-Location: " << findAndReplaceAll(URL, ROOT_FOLDER, "") << "\n";

            return response(201) + headers.str();
        }

        // When it's tried to create a file in non existing folder
        return response(400);
    }

    auto DELETE(std::string const &URL)
    {
        try
        {
            if (std::filesystem::remove(URL))
            {
                return response(200);
            }
        }
        catch (...)
        {
            // When directory is not empty
            return response(304);
        }

        // When there is no such file to delete
        return response(204);
    }

} // namespace own
